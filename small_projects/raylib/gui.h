#ifndef GUI_H
#define GUI_H

#include <stdbool.h>
#include "raylib.h"
#include "tictactoe.h"


/* CONSTANTS */
#define WINDOW_WIDTH   540
#define WINDOW_HEIGHT  700
#define WINDOW_TITLE   "tic tac toe"
#define TARGET_FPS     60

/* board layout (all sizes are in pixels) */
#define CELL_SIZE         150
#define BOARD_PIXEL_SIZE  (CELL_SIZE * BOARD_SIZE)
#define BOARD_LEFT        ((WINDOW_WIDTH - BOARD_PIXEL_SIZE) / 2)
#define BOARD_TOP         130

/* drawing sizes */
#define GRID_LINE_THICKNESS      6
#define MARK_PADDING             38
#define MARK_THICKNESS           12
#define WINNING_LINE_THICKNESS   10

/* button sizes */
#define BUTTON_WIDTH         260
#define BUTTON_HEIGHT        60
#define BUTTON_SPACING       30
#define BUTTON_FONT_SIZE     24
#define PLAY_AGAIN_WIDTH     200
#define PLAY_AGAIN_HEIGHT    44

/* how long the computer waits before playing, so the move feels natural */
#define AI_THINK_DELAY_SECONDS  0.6f

/* colors */
#define COLOR_BACKGROUND    ((Color){24, 28, 38, 255})
#define COLOR_BOARD         ((Color){36, 42, 56, 255})
#define COLOR_GRID          ((Color){70, 80, 100, 255})
#define COLOR_CELL_HOVER    ((Color){50, 58, 76, 255})
#define COLOR_TEXT          ((Color){235, 238, 245, 255})
#define COLOR_TEXT_DIM      ((Color){140, 150, 170, 255})
#define COLOR_HUMAN         ((Color){80, 200, 230, 255})
#define COLOR_AI            ((Color){245, 160, 70, 255})
#define COLOR_WINNING_LINE  ((Color){120, 230, 140, 255})
#define COLOR_BUTTON        ((Color){60, 110, 200, 255})
#define COLOR_BUTTON_HOVER  ((Color){80, 135, 230, 255})


/* DATA TYPES */
/* the screen that is currently shown to the user */
typedef enum {
    SCREEN_MENU,
    SCREEN_PLAYING,
    SCREEN_GAME_OVER
} GameScreen;

/* holds everything that changes while the game runs */
typedef struct {
    Board board;
    char current_mark;
    int game_status;
    GameScreen screen;
    float ai_wait_time;
    int human_wins;
    int ai_wins;
    int draws;
} GameState;


/* 1. GAME STATE */
/* sets the scoreboard to zero and shows the menu screen */
void init_game_state(GameState *game_state);

/* clears the board and starts a round where first_mark plays first */
void start_new_round(GameState *game_state, char first_mark);

/* adds the finished game to the scoreboard */
void update_scores(GameState *game_state);

/* places the current player's mark, then either switches turn or ends the game */
void apply_move(GameState *game_state, Move move);


/* 2. GEOMETRY (POSITIONS ON THE SCREEN) */
/* returns the pixel rectangle of one board cell */
Rectangle get_cell_rectangle(int row, int column);

/* returns the pixel center of one board cell */
Vector2 get_cell_center(int row, int column);

/* returns the cell under the given pixel position, or row and column -1 if there is none */
Move get_cell_at_position(Vector2 position);

/* returns the rectangle of a menu button (0 = you first, 1 = computer first) */
Rectangle get_menu_button_rectangle(int button_index);

/* returns the rectangle of the play again button */
Rectangle get_play_again_button_rectangle(void);


/* 3. MOUSE INPUT */
/* returns true if the mouse is inside the rectangle */
bool is_mouse_over(Rectangle area);

/* returns true if the left mouse button was pressed on the button this frame */
bool is_button_clicked(Rectangle button);


/* 4. WINNING LINE */
/* returns true if every cell on the line holds the mark.
 * the line starts at the start cell and moves by the row and column step */
bool is_line_complete(const Board *board, int start_row, int start_column, int row_step, int column_step, char player_mark);

/* finds the winning line of the mark and gives back its first and last cell.
 * returns false if the mark has no winning line */
bool find_winning_line(const Board *board, char player_mark, Move *line_start, Move *line_end);


/* 5. UPDATE (RUNS ONCE PER FRAME, NO DRAWING HERE) */
/* menu: clicking a button starts a round */
void update_menu_screen(GameState *game_state);

/* human turn: clicking a free cell plays the move */
void update_human_turn(GameState *game_state);

/* computer turn: waits a short time, then plays the best move found by minimax */
void update_ai_turn(GameState *game_state);

/* picks the human or the computer turn */
void update_playing_screen(GameState *game_state);

/* game over: clicking play again goes back to the menu */
void update_game_over_screen(GameState *game_state);

/* updates the screen that is currently shown */
void update_game(GameState *game_state);


/* 6. DRAWING HELPERS */
/* draws text horizontally centered around center_x */
void draw_centered_text(const char *text, int center_x, int top_y, int font_size, Color color);

/* draws a button, it gets lighter when the mouse is over it */
void draw_button(Rectangle button, const char *label);

/* returns the color of a mark (HUMAN_MARK or AI_MARK) */
Color get_mark_color(char player_mark);

/* draws an X or an O inside the given cell */
void draw_mark(int row, int column, char player_mark, Color color);

/* returns the text that tells the user what is going on */
const char *get_status_message(const GameState *game_state);


/* 7. DRAWING PARTS OF THE SCREEN */
/* draws the board background and the grid lines */
void draw_grid(void);

/* draws every mark that is on the board */
void draw_marks(const Board *board);

/* shows a faded mark in the free cell under the mouse during the human turn */
void draw_hover_preview(const GameState *game_state);

/* draws a line through the three winning cells */
void draw_winning_line(const GameState *game_state);

/* draws the game title */
void draw_title(void);

/* draws the win, draw and loss counters */
void draw_scoreboard(const GameState *game_state);

/* draws the status message below the board */
void draw_status_message(const GameState *game_state);


/* 8. DRAWING SCREENS */
void draw_menu_screen(void);
void draw_playing_screen(const GameState *game_state);
void draw_game_over_screen(const GameState *game_state);

/* draws one complete frame */
void draw_game(const GameState *game_state);

#endif /* GUI_H */
