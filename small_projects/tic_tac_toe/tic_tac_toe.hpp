#pragma once
#include <vector>

/* UTILITIES */
std::vector<std::vector<char>> initialize_board();
/* the baord initialized with empty cells '-' */
void print_board(const std::vector<std::vector<char>>& board);


/* INPUT HANDLING */
void get_human_move(const std::vector<std::vector<char>>& board, int &row, int &column, const char& current_player);
/* get row and column from human player with validation */
void clear_input_buffer();
/* Clears cin's fail state and flushes bad input if the user types something non-numeric */


/* INPUT VALIDATION / CONSTRAINTS */
bool is_within_bounds(const int& row, const int& column);
/* return true if row and column is within the grid boundaries */
bool is_cell_empty(const std::vector<std::vector<char>>& board, const int& row, const int& column);
/* return true if cell contains '-' */
bool is_valid_move(const std::vector<std::vector<char>>& board, const int& row, const int& column);
/* check if cell is within bounds and empty */


/* BOARD UPDATE & TURN MANAGEMENT */
void update_board(std::vector<std::vector<char>>& board, const int& row, const int& column, const char& symbol);
/* place current player symbol after valid move is confirmed */
char switch_player(const char& current_player);
/* return other player symbol, alternating turns */


/* WIN CHECKING */
bool check_row_win(const std::vector<std::vector<char>>& board, const char& symbol);
bool check_column_win(const std::vector<std::vector<char>>& board, const char& symbol);
bool check_diagonal_win(const std::vector<std::vector<char>>& board, const char& symbol);
bool check_win(const std::vector<std::vector<char>>& board, const char& symbol);
/* check_win calls the three above; true if any of them find 3-in-a-row for that symbol */


/* DRAW CHECKING */
bool check_draw(const std::vector<std::vector<char>>& board);
/* return true if board is completely full */


/* RESULT DISPLAY */
void announce_winner(const char& symbol);
void announce_draw();


/* GAME FLOW */
void play_game();
/* Orchestrates everything: setup -> alternate turns -> check win/draw -> announce result */
