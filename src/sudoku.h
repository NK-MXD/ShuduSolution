
#ifndef SRC_SUDOKU_H_
#define SRC_SUDOKU_H_

#include <array>
#include <string>
#include <vector>

// 定义数独棋盘数据结构
typedef std::vector<std::vector<int>> SudokuBoard;
// 打印数独棋盘
void printSudokuBoard(const SudokuBoard &board);
// 从文件中读取数独棋盘
std::vector<SudokuBoard> readSudokuBoardFromFile(const std::string &filename);
// 将数独棋盘写入文件
void writeSudokuBoardToFile(const std::string &filename, const std::vector<SudokuBoard> &boards);
// 生成数独游戏
std::vector<SudokuBoard> generateGameSudoku(int count, int mode, std::pair<int, int> range, bool unique);
// 解决数独游戏
SudokuBoard solveSudoku(SudokuBoard board);
// 生成基础数独终局
SudokuBoard generateBaseSudokuBoard();
// 根据基础数独终局生成所有不重复的数独终局
std::vector<SudokuBoard> generateAllSudokuBoards(int numSolutions);
// 生成数独游戏
std::vector<SudokuBoard> generateGameSudoku(int count, int mode, std::pair<int, int> range, bool unique);
// 生成数独游戏实现
SudokuBoard generateGameSudokuImpl(const SudokuBoard &finalBoard, int mode, std::pair<int, int> range, bool unique);
// 挖空数独终局生成数独
SudokuBoard digBoard(SudokuBoard finalBoard, int digNum);
// 求解所有解的个数
void solveSudoku(int i, int j, SudokuBoard &board, int solutionCount);
int genRand();

#endif