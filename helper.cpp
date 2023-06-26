#include "helper.h"
#include<fstream>
#include <string.h>
#include <stdio.h>

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
void writeBoard(const Board& board, std::ostream& out){
    for(auto row : board){
        for(auto num : row){
            if(num!=0) out<<num<<" ";
            else out<<"$ ";
        }
        out << std::endl;
    }
    out << std::endl;
}
bool readBoard(Board& board, std::istream& in){
    for(auto& row : board){
        for(auto& num : row){
            char c;
            in>>c;
            if(!c) return false;
            if(c=='$') num=0;
            else num=c-'0';
        }
    }
    return true;
}

bool isValidSudoku(const Board& board, const int size = 9) {
    // 检查数组是否是size * size的矩阵
    if (board.size() != size || board[0].size() != size) {
        return false;
    }

    // 检查0的个数是否在20到55之间
    int zeroCount = 0;
    for (const auto& row : board) {
        for (const auto& num : row) {
            if (num == 0) {
                zeroCount++;
            }
        }
    }
    if (zeroCount < 20 || zeroCount > 55) {
        return false;
    }

    return true;
}

std::string args_checker(int &final_boards_cnt, std::string &problem_input_path, int &games_cnt, int &game_level, int &min_empty, int &max_empty, bool &unique)
{
    std::string error_msg;
    //if no arg specified, print usage
    if(!final_boards_cnt && !games_cnt && problem_input_path=="" && !game_level && !min_empty && !max_empty && !unique){
        error_msg = "Usage: ./sudoku -c final_boards_cnt -s problem_input_path -n games_cnt -m game_level -r min_empty~max_empty -u unique";
        return error_msg;
    }
    if(!games_cnt && (game_level | min_empty | max_empty | unique)){
        error_msg = "Error: -n must be specified when -m, -r or -u is specified";
        return error_msg;
    }
    if(games_cnt){
        //default values:
        if(!game_level) game_level = 2;
        if(!min_empty) min_empty = 20;
        if(!max_empty) max_empty = 55;
    }
    //arg range check
    if(min_empty&&min_empty<20 || max_empty&&max_empty>55){
        error_msg = "Error: number of empty cells must be between 20~55";
        return error_msg;
    }
    if(min_empty&&max_empty&&min_empty>max_empty){
        error_msg = "Error: min_empty must be smaller than max_empty";
        return error_msg;
    }
    if (final_boards_cnt&&(final_boards_cnt<1 || final_boards_cnt>1000000)){
        error_msg = "Error: number of final boards must be between 1~1000000";
        return error_msg;
    }
    if(problem_input_path!=""){
        std::ifstream in(problem_input_path);
        if(!in){
            error_msg = "Error: problem input file does not exist";
            return error_msg;
        }
    }
    if (games_cnt&&(games_cnt<1 || games_cnt>10000)){
        error_msg = "Error: number of games must be between 1~10000";
        return error_msg;
    }
    if(game_level&&(game_level<1 || game_level>3)){
        error_msg = "Error: game level must be between 1~3";
        return error_msg;
    }
    return error_msg;
}

