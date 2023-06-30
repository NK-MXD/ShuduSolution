#include <stdio.h>
#include <getopt.h>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <regex>
#include "sudoku.h"
extern int optind, opterr, optopt;
extern char *optargi;
// 定义长选项
static struct option long_options[] =
    {
        {"count", required_argument, NULL, 'c'},
        {"solve", required_argument, NULL, 's'},
        {"number", required_argument, NULL, 'n'},
        {"mode", required_argument, NULL, 'm'},
        {"range", required_argument, NULL, 'r'},
        {"unique", no_argument, NULL, 'u'},
        {"help", no_argument, NULL, 'h'}};

int main(int argc, char *argv[])
{
    int index = 0;
    int c = 0;                 // 用于接收选项
    int count = 0;             // 用来保存count
    int number = 0;            // 用来保存number
    std::pair<int, int> range; // 用来保存range
    int mode = 1;              // 用来保存mode
    bool unique = false;       // 用来保存unqiue
    std::string filename;      // 用来保存解决文件
    /*循环处理参数*/
    while (EOF != (c = getopt_long_only(argc, argv, "huc:s:n:m:r:", long_options, &index)))
    {
        switch (c)
        {
        case 'h':
            std::cout << "Options:\n"
                      << "  -c, --count <number>    Needs number of sudoku puzzles (1-1000000)\n"
                      << "  -s, --solve <file>      Needs path to sudoku puzzle file\n"
                      << "  -n, --number <number>   Needs number of games (1-10000)\n"
                      << "  -m, --mode <number>     Generates game difficulty (1-3)\n"
                      << "  -r, --range <range>     Generates game with number range (20~55)\n"
                      << "  -u, --unique <bool>    Generates game with unique solution(default false)\n"
                      << "  -h, --help              Displays this help information\n";
            break;
        case 'c':
            try
            {
                count = std::stoi(optarg); // 将参数转换为整数
                // 检查范围
                if (count < 1 || count > 1000000)
                {
                    std::cerr << "Count argument is out of range (1-1000000): " << count << std::endl;
                    return 1;
                }
            }
            catch (const std::invalid_argument &e)
            {
                std::cerr << "Invalid count argument: " << optarg << std::endl;
                return 1;
            }
            catch (const std::out_of_range &e)
            {
                std::cerr << "Count argument out of range: " << optarg << std::endl;
                return 1;
            }
            // 生成终盘
            std::cout << "Generate the final board" << std::endl;
            std::cout << "The number of sudoku: " << count << std::endl;
            break;
        case 's':
            filename = std::string(optarg); // 将参数值转换为std::string类型
            std::cout << "Sovle sudoku" << std::endl;
            std::cout << "Sudoku file" << filename << std::endl;
            break;
        case 'n':
            try
            {
                number = std::stoi(optarg); // 将参数转换为整数
                // 检查范围
                if (number < 1 || number > 10000)
                {
                    std::cerr << "Count argument is out of range (1-1000000): " << number << std::endl;
                    return 1;
                }
            }
            catch (const std::invalid_argument &e)
            {
                std::cerr << "Invalid count argument: " << optarg << std::endl;
                return 1;
            }
            catch (const std::out_of_range &e)
            {
                std::cerr << "Count argument out of range: " << optarg << std::endl;
                return 1;
            }
            break;
        case 'm':
            try
            {
                if (number == 0)
                {
                    std::cerr << "Option -n is required." << std::endl;
                    return 1;
                }
                mode = std::stoi(optarg);
                if (mode < 1 || mode > 3)
                {
                    std::cerr << "Mode argument is out of range (1-3): " << mode << std::endl;
                    return 1;
                }
            }
            catch (const std::invalid_argument &e)
            {
                std::cerr << "Invalid mode argument: " << optarg << std::endl;
                return 1;
            }
            catch (const std::out_of_range &e)
            {
                std::cerr << "Mode argument out of range: " << optarg << std::endl;
                return 1;
            }
            break;
        case 'r':
            try
            {
                if (number == 0)
                {
                    std::cerr << "Option -n is required." << std::endl;
                    return 1;
                }
                std::smatch m;
                std::string s(optarg);
                if (!std::regex_match(s, m, std::regex(R"(^(\d+)~(\d+)$)")))
                {
                    std::cout << "Fomat error, just like 20~55" << std::endl;
                    return 1;
                }
                range = {std::stoi(m[1]), std::stoi(m[2])};
                if (range.first < 22 || range.second > 55 || range.first > range.second)
                {
                    std::cerr << "Range argument is out of range (20~55): " << range.first << "~" << range.second << std::endl;
                    return 1;
                }
            }
            catch (const std::invalid_argument &e)
            {
                std::cerr << "Invalid range argument: " << optarg << std::endl;
                return 1;
            }
            catch (const std::out_of_range &e)
            {
                std::cerr << "Range argument out of range: " << optarg << std::endl;
                return 1;
            }
            break;
        case 'u':
            // 检查其他参数是否与 -n 一起使用
            if (number == 0)
            {
                std::cerr << "Option -n is required." << std::endl;
                return 1;
            }
            unique = true;
            break;
        case '?':
            printf("unknow option:%c\n", optopt);
            break;
        default:
            break;
        }
    }

    // 根据具体来分析
    if (count != 0)
    {
        std::vector<SudokuBoard> boards = generateAllSudokuBoards(count);
        int i = 1;
        for (const SudokuBoard &board : boards)
        {
            // 打印终局
            std::cout << "Generate the " << i++ << "final board" << std::endl;
            printSudokuBoard(board);
        }
        writeSudokuBoardToFile("finalBoard.txt", boards);
    }
    else if (filename != "")
    {
        // 求解数独
        std::vector<SudokuBoard> boards = readSudokuBoardFromFile(filename);
        for (SudokuBoard &board : boards)
        {
            board = solveSudoku(board);
            std::cout << "the result: " << std::endl;
            printSudokuBoard(board);
        }
        writeSudokuBoardToFile("solveBoard.txt", boards);
    }
    else if (number != 0)
    {
        std::cout << "Generate Game..." << std::endl;
        std::cout << "The number of game: " << number << std::endl;
        std::cout << "The diffculty of game: " << mode << std::endl;
        std::cout << "The range of game: " << range.first << " ~ " << range.second
                  << std::endl;
        std::cout << "Unique: " << (unique ? "True" : "No") << std::endl;

        std::vector<SudokuBoard> boards = generateGameSudoku(number, mode, range, unique);
        int i = 1;
        for (const SudokuBoard &board : boards)
        {
            // 打印游戏
            std::cout << "Generate the " << i++ << " game board." << std::endl;
            printSudokuBoard(board);
        }
        writeSudokuBoardToFile("gameBoard.txt", boards);
    }

    return 0;
}