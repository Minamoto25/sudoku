#ifndef SUDOKU_H
#define SUDOKU_H
#include<vector>
#include<random>
#include<string>
#include<iostream>
#include<unordered_map>
typedef std::vector<std::vector<int>> Board;
std::random_device rd;
std::mt19937 gen = std::mt19937(rd());    

class Generator{
private:
    unsigned size; //generally, size should be 9, but you can try other sizes of square
    std::unordered_map<std::string,int> board_history;
    bool isValid(const Board& board, int row, int col, int num);
    std::vector<int> genRow();
    bool genOne(Board& board, int row, int col);
public:
    Generator(unsigned n) : size(n) {
        //TODO: raise exception if n is not a square number
    }
    std::vector<Board> generate(unsigned cnt);
};

void printBoard(const Board& board);

class ProblemMaker{
public:
    int level;
    int min_empty, max_empty;
    int total;
    ProblemMaker(int level, int min_empty, int max_empty, int total) :
     level(level), min_empty(min_empty), max_empty(max_empty), total(total) {}
    std::vector<Board> makeProblems(const std::vector<Board>& boards);
};
#endif