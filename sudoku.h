#ifndef SUDOKU_H
#define SUDOKU_H
#include<vector>
#include<random>
#include<string>
#include<iostream>
#include<unordered_map>
typedef std::vector<std::vector<int>> Board;

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
void writeBoard(const Board& board, std::ostream& os);
bool readBoard(Board& board, std::istream& is);

class ProblemMaker{
    std::unordered_map<std::string,int> board_history;
    const std::vector<Board>& boards;
public:
    int min_empty, max_empty;
    ProblemMaker(int min_empty, int max_empty, const std::vector<Board>& boards) :
    min_empty(min_empty), max_empty(max_empty), boards(boards) {}
    Board makeProblem();
};

class Solver{
private:
    Board board;
    unsigned long long try_sum=0;
    std::vector<Board> solutions;
    bool dfs(int row, int col);
    bool isValid(const Board& board, int row, int col, int num);
public:
    Solver(const Board& board) : board(board) {};
    void solve();
    //TODO: return the level of the game
    int getLevel() const {return 2;}//return try_sum*solutions.size();}
    const std::vector<Board>& getSolutions() const {return solutions;}
};
#endif