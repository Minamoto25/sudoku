/*Copyright 2023 Ma Jiangyuan & FengChaopeng*/
#ifndef INCLUDE_HELPER_H_
#define INCLUDE_HELPER_H_
#include <string>
#include <vector>

#include "./sudoku.h"

typedef struct {
  int final_boards_cnt, games_cnt, game_level, min_empty, max_empty;
  std::string problem_input_path;
  bool unique;
} Args;

std::string args_checker(const Args& args);
bool isValid(const Board& board, int row, int col, int num);
std::string board_to_string(const Board& board);

struct BoardDumper {
  std::ofstream& os;
  explicit BoardDumper(std::ofstream& os) : os(os) {}
  void operator()(const Board& board);
};

struct BoardReader {
  std::ifstream& is;
  Board board;
  explicit BoardReader(std::ifstream& is) : is(is) {
    board = Board(9, std::vector<int>(9, 0));
  }
  bool operator()();
};

bool checkRange(std::string str);
void printBoard(const Board& board);
bool isValidSudoku(const Board& board, int size);
#endif  // INCLUDE_HELPER_H_
