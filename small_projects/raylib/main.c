#include "gui.h"

int main(void) {
    GameState game_state;

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(TARGET_FPS);
    init_game_state(&game_state);

    while (!WindowShouldClose()) {
        update_game(&game_state);
        draw_game(&game_state);
    }

    CloseWindow();
    return 0;
}
