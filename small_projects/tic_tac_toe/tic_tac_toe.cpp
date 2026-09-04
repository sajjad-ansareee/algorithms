#include "tic_tac_toe.hpp"
#include <iostream>
#include <vector>

using namespace std;

vector<vector<char>> initialize_board() {
	vector<vector<char>> board(3, vector<char>(3, '-'));
	return board;
}

void print_board(const vector<vector<char>>& board) {
	for (const auto& row : board) {
		for (char cell : row) {
			cout << cell << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void get_human_move(const vector<vector<char>>& board, int& row, int& column, const char& current_player) {
	cout << "player " << current_player << ", enter your move..." << endl;
	cout << "row: "; cin >> row;
	cout << "column: "; cin >> column;
	while (is_valid_move(board, row, column)==false) {
		cout << "invalid move. try again." << endl;
		cout << "row: "; cin >> row;
		cout << "column: "; cin >> column;
	}
}

bool is_within_bounds(const int& row, const int& column) {
	return (row >= 1 && row <= 3) && (column >= 1 && column <= 3);
}

bool is_cell_empty(const vector<vector<char>>& board, const int& row, const int& column) {
	return board[row - 1][column - 1] == '-';
}

bool is_valid_move(const vector<vector<char>>& board, const int& row, const int& column) {
	return is_within_bounds(row, column) && is_cell_empty(board, row, column);
}

void update_board(vector<vector<char>>& board, const int& row, const int& column, const char& symbol) {
	board[row - 1][column - 1] = symbol;
}

char switch_player(const char& current_player) {
	return (current_player == 'X') ? 'O' : 'X';
}

bool check_row_win(const vector<vector<char>>& board, const char& symbol) {
	for (const auto& row : board) {
		bool win = true;
		for (char cell : row) {
			if (cell != symbol) {
				win = false;
				break;
			}
		}
		if (win==true) {
			return true;
		}
	}
	return false;
}

bool check_column_win(const vector<vector<char>>& board, const char& symbol) {
	for (int column = 0; column < 3; ++column) {
		bool win = true;
		for (int row = 0; row < 3; ++row) {
			if (board[row][column] != symbol) {
				win = false;
				break;
			}
		}
		if (win==true) {
			return true;
		}
	}
	return false;
}

bool check_diagonal_win(const vector<vector<char>>& board, const char& symbol) {
	/* check main diagonal */
	bool win = true;
	for (int i = 0; i < 3; ++i) {
		if (board[i][i] != symbol) {
			win = false;
			break;
		}
	}
	if (win==true) {
		return true;
	}
	/* check secondary diagonal */
	win = true;
	for (int i = 0; i < 3; ++i) {
		if (board[i][2-i] != symbol) {
			win = false;
			break;
		}
	}
	return win;
}

bool check_win(const vector<vector<char>>& board, const char& symbol) {
	return check_row_win(board, symbol) || check_column_win(board, symbol) || check_diagonal_win(board, symbol);
}

bool check_draw(const vector<vector<char>> &board) {
	for (const auto& row : board) {
		for (char cell : row) {
			if (cell == '-') {
				return false;
			}
		}
	}
	return true;
}

void announce_winner(const char& symbol) {
	cout << "player " << symbol << " won!" << endl;
}

void announce_draw() {
	cout << "the game has been drawn..." << endl;
}

void play_game() {
	vector<vector<char>> board(3, vector<char>(3, '-'));
	char current_player = 'X';
	while (true) {
		int row, column;
		get_human_move(board, row, column, current_player);
		update_board(board, row, column, current_player);
		print_board(board);
		if (check_win(board, current_player)) {
			announce_winner(current_player);
			break;
		}
		if (check_draw(board)) {
			announce_draw();
			break;
		}
		current_player = switch_player(current_player);
	}
}

int main() {
	play_game();
	return 0;
}
