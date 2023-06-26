#ifndef HELPER_H
#define HELPER_H
#include "sudoku.h"
void printBoard(const Board& board);
void writeBoard(const Board& board, std::ostream& os);
bool readBoard(Board& board, std::istream& is);
bool isValidSudoku(const Board& board, int size);
std::string args_checker(int& final_boards_cnt,
 std::string& problem_input_path, int& games_cnt, int& game_level, int& min_empty,
  int& max_empty, bool& unique);
#endif