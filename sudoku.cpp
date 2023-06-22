#include<algorithm>
#include "sudoku.h"
void printBoard(const Board& board){
    for(auto row : board){
        for(auto num : row){
            if(num!=0) std::cout<<num<<" ";
            else std::cout<<"$ ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

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

std::vector<Board> ProblemMaker::makeProblems(const std::vector<Board> &boards)
{
    size_t size = boards[0][0].size();
    std::vector<Board> problems;
    for(auto board : boards){
        std::vector<int> empty_pos;
        for(size_t i=0; i<size; i++){
            for(size_t j=0; j<size; j++){
                empty_pos.push_back(i*size+j);
            }
        }
        std::shuffle(empty_pos.begin(), empty_pos.end(), gen);
        int empty_cnt = min_empty + gen()%(max_empty-min_empty+1);
        for(size_t i=0; i<empty_cnt; i++){
            int pos = empty_pos[i];
            board[pos/size][pos%size] = 0;
        }
        problems.push_back(board);
    }
    return problems;
}
