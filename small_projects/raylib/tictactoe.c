#include <stdio.h>
#include "tictactoe.h"


/* STATIC HELPERS (ONLY USED INSIDE THIS FILE) */
static void print_separator_line(void);
static void discard_input_line(void);
static int read_number_in_range(const char *prompt);


/* 1. BOARD SETUP AND DISPLAY */
void init_board(Board *board) {
    int row;
    int column;

    for (row = 0; row < BOARD_SIZE; row++) {
        for (column = 0; column < BOARD_SIZE; column++) {
            board->cells[row][column] = EMPTY_CELL;
        }
    }
}

static void print_separator_line(void) {
    int column;

    printf("    ");
    for (column = 0; column < BOARD_SIZE; column++) {
        printf("+---");
    }
    printf("+\n");
}

void display_board(const Board *board) {
    int row;
    int column;

    printf("\n    ");
    for (column = 1; column <= BOARD_SIZE; column++) {
        printf("  %d ", column);
    }
    printf("\n");

    print_separator_line();
    for (row = 0; row < BOARD_SIZE; row++) {
        printf("  %d ", row + 1);
        for (column = 0; column < BOARD_SIZE; column++) {
            printf("| %c ", board->cells[row][column]);
        }
        printf("|\n");
        print_separator_line();
    }
    printf("\n");
}


/* 2. BOARD QUERIES */
bool is_position_in_range(int row, int column) {
    return row >= 0
        && row < BOARD_SIZE
        && column >= 0
        && column < BOARD_SIZE;
}

bool is_cell_empty(const Board *board, int row, int column) {
    return board->cells[row][column] == EMPTY_CELL;
}

bool is_valid_move(const Board *board, int row, int column) {
    /* range is checked first so the cell is never read outside the array */
    return is_position_in_range(row, column)
        && is_cell_empty(board, row, column);
}

bool is_board_full(const Board *board) {
    int row;
    int column;

    for (row = 0; row < BOARD_SIZE; row++) {
        for (column = 0; column < BOARD_SIZE; column++) {
            if (is_cell_empty(board, row, column)) {
                return false;
            }
        }
    }
    return true;
}


/* 3. BOARD MODIFICATION */
void place_mark(Board *board, int row, int column, char player_mark) {
    board->cells[row][column] = player_mark;
}

void remove_mark(Board *board, int row, int column) {
    board->cells[row][column] = EMPTY_CELL;
}


/* 4. WIN CHECKING */
bool has_row_win(const Board *board, char player_mark) {
    int row;
    int column;
    bool is_row_complete;

    for (row = 0; row < BOARD_SIZE; row++) {
        is_row_complete = true;
        for (column = 0; column < BOARD_SIZE; column++) {
            if (board->cells[row][column] != player_mark) {
                is_row_complete = false;
            }
        }
        if (is_row_complete) {
            return true;
        }
    }
    return false;
}

bool has_column_win(const Board *board, char player_mark) {
    int row;
    int column;
    bool is_column_complete;

    for (column = 0; column < BOARD_SIZE; column++) {
        is_column_complete = true;
        for (row = 0; row < BOARD_SIZE; row++) {
            if (board->cells[row][column] != player_mark) {
                is_column_complete = false;
            }
        }
        if (is_column_complete) {
            return true;
        }
    }
    return false;
}

bool has_diagonal_win(const Board *board, char player_mark) {
    int index;
    bool is_main_diagonal_complete = true;
    bool is_anti_diagonal_complete = true;

    for (index = 0; index < BOARD_SIZE; index++) {
        /* main diagonal goes top-left to bottom-right */
        if (board->cells[index][index] != player_mark) {
            is_main_diagonal_complete = false;
        }
        /* anti diagonal goes top-right to bottom-left */
        if (board->cells[index][BOARD_SIZE - 1 - index] != player_mark) {
            is_anti_diagonal_complete = false;
        }
    }
    return is_main_diagonal_complete
        || is_anti_diagonal_complete;
}

bool has_won(const Board *board, char player_mark) {
    return has_row_win(board, player_mark)
        || has_column_win(board, player_mark)
        || has_diagonal_win(board, player_mark);
}


/* 5. GAME STATE */
int get_game_status(const Board *board) {
    if (has_won(board, HUMAN_MARK)) {
        return STATUS_HUMAN_WIN;
    }
    if (has_won(board, AI_MARK)) {
        return STATUS_AI_WIN;
    }
    if (is_board_full(board)) {
        return STATUS_DRAW;
    }
    return STATUS_ONGOING;
}

bool is_game_over(const Board *board) {
    return get_game_status(board) != STATUS_ONGOING;
}

char get_opponent_mark(char player_mark) {
    if (player_mark == HUMAN_MARK) {
        return AI_MARK;
    }
    return HUMAN_MARK;
}


/* 6. MINIMAX AI */
int evaluate_board(const Board *board, int depth) {
    int game_status = get_game_status(board);

    /* depth is added or subtracted so the AI WINS FASTER and LOSES SLOWER */
    if (game_status == STATUS_AI_WIN) {
        return SCORE_AI_WIN - depth;
    }
    if (game_status == STATUS_HUMAN_WIN) {
        return SCORE_HUMAN_WIN + depth;
    }
    return SCORE_DRAW;
}

int get_maximum(int first_number, int second_number) {
    if (first_number > second_number) {
        return first_number;
    }
    return second_number;
}

int get_minimum(int first_number, int second_number) {
    if (first_number < second_number) {
        return first_number;
    }
    return second_number;
}

int minimax(Board *board, int depth, bool is_ai_turn) {
    int row;
    int column;
    int score;
    int best_score;
    char player_mark;

    /* BASE CASE: the game is finished, so the board gets a score */
    if (is_game_over(board)) {
        return evaluate_board(board, depth);
    }

    if (is_ai_turn) {
        best_score = -SCORE_INFINITY;
        player_mark = AI_MARK;
    } else {
        best_score = SCORE_INFINITY;
        player_mark = HUMAN_MARK;
    }

    for (row = 0; row < BOARD_SIZE; row++) {
        for (column = 0; column < BOARD_SIZE; column++) {
            if (!is_cell_empty(board, row, column)) {
                continue;
            }

            /* try the move, score it with the opponent playing next, then UNDO IT */
            place_mark(board, row, column, player_mark);
            score = minimax(board, depth + 1, !is_ai_turn);
            remove_mark(board, row, column);

            if (is_ai_turn) {
                best_score = get_maximum(best_score, score);
            } else {
                best_score = get_minimum(best_score, score);
            }
        }
    }
    return best_score;
}

Move find_best_move(Board *board) {
    int row;
    int column;
    int score;
    int best_score = -SCORE_INFINITY;
    Move best_move = {-1, -1};

    for (row = 0; row < BOARD_SIZE; row++) {
        for (column = 0; column < BOARD_SIZE; column++) {
            if (!is_cell_empty(board, row, column)) {
                continue;
            }

            /* depth starts at 1 because the AI move itself is already one step */
            place_mark(board, row, column, AI_MARK);
            score = minimax(board, 1, false);
            remove_mark(board, row, column);

            if (score > best_score) {
                best_score = score;
                best_move.row = row;
                best_move.column = column;
            }
        }
    }
    return best_move;
}


/* 7. INPUT HANDLING */
static void discard_input_line(void) {
    int character = getchar();

    while (
        character != '\n'
        && character != EOF
    ) {
        character = getchar();
    }
}

static int read_number_in_range(const char *prompt) {
    int number;

    while (true) {
        printf("%s (1-%d): ", prompt, BOARD_SIZE);

        if (
            scanf("%d", &number) == 1
            && number >= 1
            && number <= BOARD_SIZE
        ) {
            return number;
        }

        /* invalid input must be thrown away or scanf will fail forever on it */
        discard_input_line();
        printf("invalid number, try again.\n");
    }
}

int read_row_number(void) {
    return read_number_in_range("enter row");
}

int read_column_number(void) {
    return read_number_in_range("enter column");
}

int convert_number_to_index(int user_number) {
    return user_number - 1;
}

Move get_human_move(const Board *board) {
    Move move;

    while (true) {
        move.row = convert_number_to_index(read_row_number());
        move.column = convert_number_to_index(read_column_number());

        if (is_valid_move(board, move.row, move.column)) {
            return move;
        }
        printf("that cell is already taken, try again.\n");
    }
}


/* 8. TURN HANDLING */
void play_human_turn(Board *board) {
    Move move = get_human_move(board);

    place_mark(board, move.row, move.column, HUMAN_MARK);
}

void play_ai_turn(Board *board) {
    Move move = find_best_move(board);

    place_mark(board, move.row, move.column, AI_MARK);
    printf("computer played row %d, column %d\n", move.row + 1, move.column + 1);
}

char switch_turn(char current_mark) {
    return get_opponent_mark(current_mark);
}


/* 9. USER INTERFACE MESSAGES */
void show_welcome(void) {
    printf("TIC TAC TOE: YOU (%c) vs COMPUTER (%c)\n", HUMAN_MARK, AI_MARK);
}

void show_row_column_guide(void) {
    printf("rows go from top to bottom and columns go from left to right.\n");
    printf("example: row 1, column 3 is the top right cell.\n");
}

void show_result(int game_status) {
    if (game_status == STATUS_HUMAN_WIN) {
        printf("you won!\n");
    } else if (game_status == STATUS_AI_WIN) {
        printf("computer won!\n");
    } else {
        printf("it is a draw!\n");
    }
}

bool ask_play_again(void) {
    char answer;

    printf("play again? (y/n): ");
    scanf(" %c", &answer);

    return answer == 'y'
        || answer == 'Y';
}


/* 10. GAME FLOW */
char choose_first_player(void) {
    int choice;

    while (true) {
        printf("who plays first? 1 = you, 2 = computer: ");

        if (scanf("%d", &choice) == 1) {
            if (choice == 1) {
                return HUMAN_MARK;
            }
            if (choice == 2) {
                return AI_MARK;
            }
        }

        discard_input_line();
        printf("please enter 1 or 2.\n");
    }
}

void play_game(void) {
    Board board;
    char current_mark;

    init_board(&board);
    show_row_column_guide();
    current_mark = choose_first_player();

    while (!is_game_over(&board)) {
        display_board(&board);

        if (current_mark == HUMAN_MARK) {
            play_human_turn(&board);
        } else {
            play_ai_turn(&board);
        }
        current_mark = switch_turn(current_mark);
    }

    display_board(&board);
    show_result(get_game_status(&board));
}
