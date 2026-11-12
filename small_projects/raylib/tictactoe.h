#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <stdbool.h>


/* CONSTANTS */
#define BOARD_SIZE			3

#define EMPTY_CELL			' '
#define HUMAN_MARK			'X'
#define AI_MARK				'O'

/* scores used by minimax (AI IS THE MAXIMIZER, HUMAN IS THE MINIMIZER) */
#define SCORE_AI_WIN		10
#define SCORE_HUMAN_WIN		-10
#define SCORE_DRAW			0

/* larger than any real score, used as the starting value when searching for best or worst score */
#define SCORE_INFINITY		1000

/* game status values */
#define STATUS_ONGOING		0
#define STATUS_HUMAN_WIN	1
#define STATUS_AI_WIN		2
#define STATUS_DRAW			3


/* DATA TYPES */
/* holds the position of one move on the board (0-based indexes) */
typedef struct {
	int row;
	int column;
} Move;

/* holds the whole tic tac toe board.
 * IMPORTANT: functions that change the board take a Board pointer (Board *),
 * functions that only read the board take a const Board pointer (const Board *) */
typedef struct {
	char cells[BOARD_SIZE][BOARD_SIZE];
} Board;


/* 1. BOARD SETUP AND DISPLAY */
/* fills every cell of the board with EMPTY_CELL */
void init_board(Board *board);

/* prints the board on the screen */
void display_board(const Board *board);


/* 2. BOARD QUERIES (READ-ONLY HELPERS) */
/* returns true if row and column are inside the board */
bool is_position_in_range(int row, int column);

/* returns true if the given cell is empty */
bool is_cell_empty(const Board *board, int row, int column);

/* returns true if the position is in range AND the cell is empty */
bool is_valid_move(const Board *board, int row, int column);

/* returns true if no empty cells are left */
bool is_board_full(const Board *board);


/* 3. BOARD MODIFICATION */
/* puts a mark on the board at the given row and column */
void place_mark(Board *board, int row, int column, char player_mark);

/* clears the cell at the given row and column.
 * IMPORTANT: used to undo a move inside minimax */
void remove_mark(Board *board, int row, int column);


/* 4. WIN CHECKING */
/* returns true if the mark fills any complete row */
bool has_row_win(const Board *board, char player_mark);

/* returns true if the mark fills any complete column */
bool has_column_win(const Board *board, char player_mark);

/* returns true if the mark fills either diagonal */
bool has_diagonal_win(const Board *board, char player_mark);

/* returns true if the mark has won in any way (row, column or diagonal) */
bool has_won(const Board *board, char player_mark);


/* 5. GAME STATE */
/* returns one of the STATUS_ values for the current board */
int get_game_status(const Board *board);

/* returns true if the game has ended (win or draw) */
bool is_game_over(const Board *board);

/* returns the opposite mark (HUMAN_MARK <-> AI_MARK) */
char get_opponent_mark(char player_mark);


/* 6. MINIMAX AI */
/* gives a score to a finished board:
 * SCORE_AI_WIN, SCORE_HUMAN_WIN or SCORE_DRAW.
 * depth is used so faster wins are preferred */
int evaluate_board(const Board *board, int depth);

/* returns the larger of two integers */
int get_maximum(int first_number, int second_number);

/* returns the smaller of two integers */
int get_minimum(int first_number, int second_number);

/* THE RECURSIVE MINIMAX ALGORITHM.
 * returns the best score reachable from this board.
 * is_ai_turn = true -> maximizing, false -> minimizing.
 * board is not const because moves are placed and then undone on it */
int minimax(Board *board, int depth, bool is_ai_turn);

/* tries every empty cell, runs minimax on each,
 * and returns the move with the best score for the AI.
 * board is not const because minimax places and undoes moves on it */
Move find_best_move(Board *board);


/* 7. INPUT HANDLING */
/* reads the row number from the user (1 to BOARD_SIZE) */
int read_row_number(void);

/* reads the column number from the user (1 to BOARD_SIZE) */
int read_column_number(void);

/* converts a user number (1 to BOARD_SIZE) into an array index (0 to BOARD_SIZE - 1) */
int convert_number_to_index(int user_number);

/* keeps asking for row and column until the human enters a valid, empty cell.
 * returns that move */
Move get_human_move(const Board *board);


/* 8. TURN HANDLING */
/* gets the human's move and places it on the board */
void play_human_turn(Board *board);

/* finds the AI's best move and places it on the board */
void play_ai_turn(Board *board);

/* returns whose turn comes next (swaps HUMAN_MARK / AI_MARK) */
char switch_turn(char current_mark);


/* 9. USER INTERFACE MESSAGES */
/* prints the welcome message and game instructions */
void show_welcome(void);

/* prints the row and column layout so the user knows what to enter */
void show_row_column_guide(void);

/* prints the final result based on the STATUS_ value */
void show_result(int game_status);

/* asks if the user wants to play again, returns true for yes */
bool ask_play_again(void);


/* 10. GAME FLOW */
/* asks who should play first, returns HUMAN_MARK or AI_MARK */
char choose_first_player(void);

/* runs one complete game from start to finish */
void play_game(void);

#endif /* TICTACTOE_H */
