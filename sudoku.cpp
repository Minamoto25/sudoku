#include<algorithm>
#include "sudoku.h"
#include "helper.h"
std::random_device rd;
std::mt19937 gen = std::mt19937(rd());

bool Generator::isValid(const Board &board, int row, int col, int num)
{
    // check row
    for (size_t i = 0; i < size; i++)
    {
        if (board[row][i] == num)
        {
            return false;
        }
    }
    // check col
    for (size_t i = 0; i < size; i++)
    {
        if (board[i][col] == num)
        {
            return false;
        }
    }
    // check block
    int block_size = sqrt(size);
    int block_row = row / block_size;
    int block_col = col / block_size;
    for (size_t i = block_row * block_size; i < (block_row + 1) * block_size; i++)
    {
        for (size_t j = block_col * block_size; j < (block_col + 1) * block_size; j++)
        {
            if (board[i][j] == num)
            {
                return false;
            }
        }
    }
    return true;
}

std::vector<int> Generator::genRow()
{
    std::vector<int> row;
    for(size_t i=0; i<size; i++){
        row.push_back(i+1);
    }
    std::string row_string;
    std::shuffle(row.begin(), row.end(), gen);
    return row;
}

bool Generator::genOne(Board& board, int row, int col)
{
    if(row == size){
        return true;
    }
    if(col == size){
        return genOne(board, row+1, 0);
    }
    std::vector<int> nums;
    for(size_t i=1; i<=size; i++){
        nums.push_back(i);
    }
    std::shuffle(nums.begin(), nums.end(), gen);
    for(auto num : nums){
        if(isValid(board, row, col, num)){
            board[row][col] = num;
            if(genOne(board, row, col+1)){
                return true;
            }
            board[row][col] = 0;
        }
    }
    return false;
}

std::vector<Board> Generator::generate(unsigned cnt)
{
    std::vector<Board> boards;
    while(true){
        std::vector<int> row = genRow();
        Board board(size, std::vector<int>(size, 0));
        board[0] = row;
        while(!genOne(board, 1, 0));
        std::string board_string;
        for(auto row : board){
            for(auto num : row){
                board_string += std::to_string(num)+"";
            }
        }
        if(board_history.find(board_string) != board_history.end()){
            continue;
        }
        boards.push_back(board);
        cnt--;
        if(!cnt) break;
    }
    return boards;
}

Board ProblemMaker::makeProblem()
{
    size_t size = boards[0][0].size();
    int board_index = std::uniform_int_distribution<int>(0, boards.size()-1)(gen);
    Board board = boards[board_index];
    std::vector<int> row_index(size*size);
    for(size_t i=0; i<size*size; i++){
        row_index[i] = i;
    }
    std::shuffle(row_index.begin(), row_index.end(), gen);
    int empty_cnt = std::uniform_int_distribution<int>(min_empty, max_empty)(gen);
    for(int i=0; i<empty_cnt; i++){
        int row = row_index[i] / size;
        int col = row_index[i] % size;
        board[row][col] = 0;
    }
    std::string board_string;
    for(auto row : board){
        for(auto num : row){
            board_string += std::to_string(num)+" ";
        }
    }
    return board;
}

bool Solver::dfs(int row, int col)
{
    if(row == board.size()){
        solutions.push_back(board);
        return true;
    }
    if(col == board.size()){
        return dfs(row+1, 0);
    }
    if(board[row][col] != 0){
        return dfs(row, col+1);
    }
    for(size_t i=1; i<=board.size(); i++){
        if(isValid(board, row, col, i)){
            board[row][col] = i;
            bool res = dfs(row, col+1);
            if(!res) try_sum+=i;
            board[row][col] = 0;
        }
    }
    return false;
}

bool Solver::isValid(const Board &board, int row, int col, int num)
{
    // check row
    for (size_t i = 0; i < board.size(); i++)
    {
        if (board[row][i] == num)
        {
            return false;
        }
    }
    // check col
    for (size_t i = 0; i < board.size(); i++)
    {
        if (board[i][col] == num)
        {
            return false;
        }
    }
    // check block
    int block_size = sqrt(board.size());
    int block_row = row / block_size;
    int block_col = col / block_size;
    for (size_t i = block_row * block_size; i < (block_row + 1) * block_size; i++)
    {
        for (size_t j = block_col * block_size; j < (block_col + 1) * block_size; j++)
        {
            if (board[i][j] == num)
            {
                return false;
            }
        }
    }
    return true;
}

void Solver::solve()
{
    dfs(0,0);
}
