#include "sudoku.h"

#include<fstream>
#include<string.h>
#include<getopt.h>

int main(int argc, char* args[]){
    //parse arguments
    int final_boards_cnt=0, games_cnt=0, game_level=0, min_empty=0, max_empty=0;
    std::string problem_input_path;
    bool unique = false;
    int opt;
    //TODO: check illegal arguments
    
    while((opt = getopt(argc,args,"c:s:n:m:r:u:"))!=-1){
        switch(opt){
            case 'c':
                final_boards_cnt = std::stoi(optarg);
                break;
            case 's':
                problem_input_path = optarg;
                break;
            case 'n':
                games_cnt = std::stoi(optarg);
                break;
            case 'm':
                game_level = std::stoi(optarg);
                break;
            case 'r':
                //range of empty cells, of form "min~max"
                min_empty = std::stoi(optarg);
                max_empty = std::stoi(strchr(optarg,'~')+1);
                break;
            case 'u':
                unique = std::stoi(optarg);
                break;
            default:
                std::cout<<"bad arguments"<<std::endl;
        }
    }
    //generate final boards
    if(final_boards_cnt){
        Generator generator(9);
        auto boards = generator.generate(final_boards_cnt);
        std::ofstream of("final_boards.txt",std::ios::out);
        for(auto board : boards){
            writeBoard(board,of);
        }
        of.close();
    }
    //generate problems
    games_cnt =5, min_empty=30, max_empty=50, game_level=2;
    if(games_cnt){
        std::ifstream in("final_boards.txt");
        std::cout<<&in<<std::endl;
        std::vector<Board> boards;
        Board board(9,std::vector<int>(9,0));
        // while(!in.eof()){ not work, keep returning 0 when hit eof
        while(readBoard(board,in)){
            boards.push_back(board);
            printBoard(board);
        }
        in.close();
        ProblemMaker pro(min_empty, max_empty, boards);
        std::vector<Board> final_problems;
        while(true){
            Board problem = pro.makeProblem();
            Solver solv(problem);
            if(unique && solv.getSolutions().size()!=1){
                std::cout<<"not unique\n";
                continue;
            }
            if(game_level && solv.getLevel()!=game_level){
                std::cout<<"not match level\n";
                continue;
            }
            final_problems.push_back(problem);
            if(final_problems.size()==games_cnt){
                break;
            }   
        }
        std::ofstream of("problems.txt",std::ios::out);
        for(auto problem : final_problems){
            writeBoard(problem,of);
        }
    }
    //solve problems
    if(problem_input_path!=""){
        std::ifstream in(problem_input_path,std::ios::in);
        std::vector<Board> problems;
        Board problem;
        while(!in.eof()){
            readBoard(problem,in);
            problems.push_back(problem);
        }
        in.close();
        std::ofstream of("solutions.txt",std::ios::out);
        for(auto problem : problems){
            Solver solv(problem);
            solv.solve();
            auto solutions = solv.getSolutions();
            for(auto solution : solutions){
                writeBoard(solution,of);
            }
        }
    }



}

// int main(){
//     Generator generator(9);
//     auto boards = generator.generate(5);
//     for(auto board : boards){
//         printBoard(board);
//     }
//     ProblemMaker pro(30, 50, 5, boards);
//     auto problems = pro.makeProblems();
//     for(auto problem : problems){
//         printBoard(problem);
//         Solver solv(problem);
//         solv.solve();
//         auto solutions = solv.getSolutions();
//         std::cout << "level: " << solv.getLevel() << std::endl;
//         for(auto solution : solutions){
//             printBoard(solution);
//         }
//     }
//     return 0;
// }