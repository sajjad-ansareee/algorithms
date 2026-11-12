#include "gui.h"


/* 1. GAME STATE */
void init_game_state(GameState *game_state) {
    init_board(&game_state->board);
    game_state->current_mark = HUMAN_MARK;
    game_state->game_status = STATUS_ONGOING;
    game_state->screen = SCREEN_MENU;
    game_state->ai_wait_time = 0.0f;
    game_state->human_wins = 0;
    game_state->ai_wins = 0;
    game_state->draws = 0;
}

void start_new_round(GameState *game_state, char first_mark) {
    init_board(&game_state->board);
    game_state->current_mark = first_mark;
    game_state->game_status = STATUS_ONGOING;
    game_state->screen = SCREEN_PLAYING;
    game_state->ai_wait_time = 0.0f;
}

void update_scores(GameState *game_state) {
    if (game_state->game_status == STATUS_HUMAN_WIN) {
        game_state->human_wins++;
    } else if (game_state->game_status == STATUS_AI_WIN) {
        game_state->ai_wins++;
    } else if (game_state->game_status == STATUS_DRAW) {
        game_state->draws++;
    }
}

void apply_move(GameState *game_state, Move move) {
    place_mark(&game_state->board, move.row, move.column, game_state->current_mark);
    game_state->game_status = get_game_status(&game_state->board);

    /* the computer must wait its full delay again after every move */
    game_state->ai_wait_time = 0.0f;

    if (game_state->game_status == STATUS_ONGOING) {
        game_state->current_mark = switch_turn(game_state->current_mark);
        return;
    }

    update_scores(game_state);
    game_state->screen = SCREEN_GAME_OVER;
}


/* 2. GEOMETRY */
Rectangle get_cell_rectangle(int row, int column) {
    Rectangle cell = {
        BOARD_LEFT + column * CELL_SIZE,
        BOARD_TOP + row * CELL_SIZE,
        CELL_SIZE,
        CELL_SIZE
    };

    return cell;
}

Vector2 get_cell_center(int row, int column) {
    Rectangle cell = get_cell_rectangle(row, column);
    Vector2 center = {
        cell.x + cell.width / 2,
        cell.y + cell.height / 2
    };

    return center;
}

Move get_cell_at_position(Vector2 position) {
    Move no_cell = {-1, -1};
    Move cell;
    int relative_x = (int)position.x - BOARD_LEFT;
    int relative_y = (int)position.y - BOARD_TOP;

    /* checked first because dividing a small negative number gives 0, not -1 */
    if (
        relative_x < 0
        || relative_y < 0
    ) {
        return no_cell;
    }

    cell.row = relative_y / CELL_SIZE;
    cell.column = relative_x / CELL_SIZE;

    if (!is_position_in_range(cell.row, cell.column)) {
        return no_cell;
    }
    return cell;
}

Rectangle get_menu_button_rectangle(int button_index) {
    Rectangle button = {
        (WINDOW_WIDTH - BUTTON_WIDTH) / 2,
        270 + button_index * (BUTTON_HEIGHT + BUTTON_SPACING),
        BUTTON_WIDTH,
        BUTTON_HEIGHT
    };

    return button;
}

Rectangle get_play_again_button_rectangle(void) {
    Rectangle button = {
        (WINDOW_WIDTH - PLAY_AGAIN_WIDTH) / 2,
        640,
        PLAY_AGAIN_WIDTH,
        PLAY_AGAIN_HEIGHT
    };

    return button;
}


/* 3. MOUSE INPUT */
bool is_mouse_over(Rectangle area) {
    return CheckCollisionPointRec(GetMousePosition(), area);
}

bool is_button_clicked(Rectangle button) {
    return is_mouse_over(button)
        && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}


/* 4. WINNING LINE */
bool is_line_complete(const Board *board, int start_row, int start_column, int row_step, int column_step, char player_mark) {
    int step;
    int row;
    int column;

    for (step = 0; step < BOARD_SIZE; step++) {
        row = start_row + step * row_step;
        column = start_column + step * column_step;

        if (board->cells[row][column] != player_mark) {
            return false;
        }
    }
    return true;
}

bool find_winning_line(const Board *board, char player_mark, Move *line_start, Move *line_end) {
    int index;
    int last_index = BOARD_SIZE - 1;

    for (index = 0; index < BOARD_SIZE; index++) {
        if (is_line_complete(board, index, 0, 0, 1, player_mark)) {
            *line_start = (Move){index, 0};
            *line_end = (Move){index, last_index};
            return true;
        }
        if (is_line_complete(board, 0, index, 1, 0, player_mark)) {
            *line_start = (Move){0, index};
            *line_end = (Move){last_index, index};
            return true;
        }
    }

    if (is_line_complete(board, 0, 0, 1, 1, player_mark)) {
        *line_start = (Move){0, 0};
        *line_end = (Move){last_index, last_index};
        return true;
    }
    if (is_line_complete(board, 0, last_index, 1, -1, player_mark)) {
        *line_start = (Move){0, last_index};
        *line_end = (Move){last_index, 0};
        return true;
    }
    return false;
}


/* 5. UPDATE */
void update_menu_screen(GameState *game_state) {
    if (is_button_clicked(get_menu_button_rectangle(0))) {
        start_new_round(game_state, HUMAN_MARK);
    } else if (is_button_clicked(get_menu_button_rectangle(1))) {
        start_new_round(game_state, AI_MARK);
    }
}

void update_human_turn(GameState *game_state) {
    Move cell;

    if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        return;
    }

    cell = get_cell_at_position(GetMousePosition());
    if (is_valid_move(&game_state->board, cell.row, cell.column)) {
        apply_move(game_state, cell);
    }
}

void update_ai_turn(GameState *game_state) {
    Move move;

    game_state->ai_wait_time += GetFrameTime();
    if (game_state->ai_wait_time < AI_THINK_DELAY_SECONDS) {
        return;
    }

    move = find_best_move(&game_state->board);
    apply_move(game_state, move);
}

void update_playing_screen(GameState *game_state) {
    if (game_state->current_mark == HUMAN_MARK) {
        update_human_turn(game_state);
    } else {
        update_ai_turn(game_state);
    }
}

void update_game_over_screen(GameState *game_state) {
    if (is_button_clicked(get_play_again_button_rectangle())) {
        game_state->screen = SCREEN_MENU;
    }
}

void update_game(GameState *game_state) {
    if (game_state->screen == SCREEN_MENU) {
        update_menu_screen(game_state);
    } else if (game_state->screen == SCREEN_PLAYING) {
        update_playing_screen(game_state);
    } else {
        update_game_over_screen(game_state);
    }
}


/* 6. DRAWING HELPERS */
void draw_centered_text(const char *text, int center_x, int top_y, int font_size, Color color) {
    int text_width = MeasureText(text, font_size);

    DrawText(text, center_x - text_width / 2, top_y, font_size, color);
}

void draw_button(Rectangle button, const char *label) {
    Color button_color = COLOR_BUTTON;
    int text_top = (int)(button.y + (button.height - BUTTON_FONT_SIZE) / 2);
    int text_center = (int)(button.x + button.width / 2);

    if (is_mouse_over(button)) {
        button_color = COLOR_BUTTON_HOVER;
    }

    DrawRectangleRounded(button, 0.3f, 8, button_color);
    draw_centered_text(label, text_center, text_top, BUTTON_FONT_SIZE, COLOR_TEXT);
}

Color get_mark_color(char player_mark) {
    if (player_mark == HUMAN_MARK) {
        return COLOR_HUMAN;
    }
    return COLOR_AI;
}

void draw_mark(int row, int column, char player_mark, Color color) {
    Rectangle cell = get_cell_rectangle(row, column);
    Vector2 center = get_cell_center(row, column);
    float left = cell.x + MARK_PADDING;
    float right = cell.x + cell.width - MARK_PADDING;
    float top = cell.y + MARK_PADDING;
    float bottom = cell.y + cell.height - MARK_PADDING;
    float outer_radius = CELL_SIZE / 2.0f - MARK_PADDING;

    if (player_mark == HUMAN_MARK) {
        DrawLineEx((Vector2){left, top}, (Vector2){right, bottom}, MARK_THICKNESS, color);
        DrawLineEx((Vector2){right, top}, (Vector2){left, bottom}, MARK_THICKNESS, color);
    } else {
        DrawRing(center, outer_radius - MARK_THICKNESS, outer_radius, 0.0f, 360.0f, 64, color);
    }
}

const char *get_status_message(const GameState *game_state) {
    if (game_state->screen == SCREEN_GAME_OVER) {
        if (game_state->game_status == STATUS_HUMAN_WIN) {
            return "you win!";
        }
        if (game_state->game_status == STATUS_AI_WIN) {
            return "computer wins!";
        }
        return "it is a draw!";
    }

    if (game_state->current_mark == HUMAN_MARK) {
        return "your turn";
    }
    return "computer is thinking...";
}


/* 7. DRAWING PARTS OF THE SCREEN */
void draw_grid(void) {
    int line_index;
    int line_position;

    DrawRectangle(BOARD_LEFT, BOARD_TOP, BOARD_PIXEL_SIZE, BOARD_PIXEL_SIZE, COLOR_BOARD);

    for (line_index = 1; line_index < BOARD_SIZE; line_index++) {
        line_position = line_index * CELL_SIZE - GRID_LINE_THICKNESS / 2;

        /* vertical line */
        DrawRectangle(BOARD_LEFT + line_position, BOARD_TOP, GRID_LINE_THICKNESS, BOARD_PIXEL_SIZE, COLOR_GRID);
        /* horizontal line */
        DrawRectangle(BOARD_LEFT, BOARD_TOP + line_position, BOARD_PIXEL_SIZE, GRID_LINE_THICKNESS, COLOR_GRID);
    }
}

void draw_marks(const Board *board) {
    int row;
    int column;
    char player_mark;

    for (row = 0; row < BOARD_SIZE; row++) {
        for (column = 0; column < BOARD_SIZE; column++) {
            player_mark = board->cells[row][column];

            if (player_mark != EMPTY_CELL) {
                draw_mark(row, column, player_mark, get_mark_color(player_mark));
            }
        }
    }
}

void draw_hover_preview(const GameState *game_state) {
    Move cell;

    if (
        game_state->screen != SCREEN_PLAYING
        || game_state->current_mark != HUMAN_MARK
    ) {
        return;
    }

    cell = get_cell_at_position(GetMousePosition());
    if (!is_valid_move(&game_state->board, cell.row, cell.column)) {
        return;
    }

    DrawRectangleRec(get_cell_rectangle(cell.row, cell.column), COLOR_CELL_HOVER);
    draw_mark(cell.row, cell.column, HUMAN_MARK, Fade(COLOR_HUMAN, 0.35f));
}

void draw_winning_line(const GameState *game_state) {
    Move line_start;
    Move line_end;
    char winner_mark = EMPTY_CELL;

    if (game_state->game_status == STATUS_HUMAN_WIN) {
        winner_mark = HUMAN_MARK;
    } else if (game_state->game_status == STATUS_AI_WIN) {
        winner_mark = AI_MARK;
    }

    /* a draw has no winner, so there is no line to draw */
    if (winner_mark == EMPTY_CELL) {
        return;
    }

    if (find_winning_line(&game_state->board, winner_mark, &line_start, &line_end)) {
        DrawLineEx(
            get_cell_center(line_start.row, line_start.column),
            get_cell_center(line_end.row, line_end.column),
            WINNING_LINE_THICKNESS,
            COLOR_WINNING_LINE
        );
    }
}

void draw_title(void) {
    draw_centered_text("TIC TAC TOE", WINDOW_WIDTH / 2, 20, 44, COLOR_TEXT);
}

void draw_scoreboard(const GameState *game_state) {
    const char *score_text = TextFormat(
        "you %d     draws %d     computer %d",
        game_state->human_wins,
        game_state->draws,
        game_state->ai_wins
    );

    draw_centered_text(score_text, WINDOW_WIDTH / 2, 80, 20, COLOR_TEXT_DIM);
}

void draw_status_message(const GameState *game_state) {
    draw_centered_text(get_status_message(game_state), WINDOW_WIDTH / 2, 598, 30, COLOR_TEXT);
}


/* 8. DRAWING SCREENS */
void draw_menu_screen(void) {
    draw_centered_text("who plays first?", WINDOW_WIDTH / 2, 200, 32, COLOR_TEXT);
    draw_button(get_menu_button_rectangle(0), "you go first");
    draw_button(get_menu_button_rectangle(1), "computer goes first");
    draw_centered_text("you are X, the computer is O", WINDOW_WIDTH / 2, 480, 20, COLOR_TEXT_DIM);
}

void draw_playing_screen(const GameState *game_state) {
    draw_grid();
    draw_hover_preview(game_state);
    draw_marks(&game_state->board);
    draw_status_message(game_state);
}

void draw_game_over_screen(const GameState *game_state) {
    draw_grid();
    draw_marks(&game_state->board);
    draw_winning_line(game_state);
    draw_status_message(game_state);
    draw_button(get_play_again_button_rectangle(), "play again");
}

void draw_game(const GameState *game_state) {
    BeginDrawing();
    ClearBackground(COLOR_BACKGROUND);

    draw_title();
    draw_scoreboard(game_state);

    if (game_state->screen == SCREEN_MENU) {
        draw_menu_screen();
    } else if (game_state->screen == SCREEN_PLAYING) {
        draw_playing_screen(game_state);
    } else {
        draw_game_over_screen(game_state);
    }

    EndDrawing();
}
