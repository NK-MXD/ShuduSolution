#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <algorithm>
#include <string>
#include <vector>
#include "sudoku.h"

const int N = 9;
int resCount = 0;

int genRand()
{
    static std::mt19937 gen(std::random_device{}());
    static std::uniform_int_distribution<> dis;
    return dis(gen);
}

bool isSafe(SudokuBoard board, int row, int col, int num)
{
    // 检查行中是否存在相同数字
    for (int i = 0; i < N; i++)
    {
        if (board[row][i] == num)
        {
            return false;
        }
    }

    // 检查列中是否存在相同数字
    for (int i = 0; i < N; i++)
    {
        if (board[i][col] == num)
        {
            return false;
        }
    }

    // 检查3x3方格中是否存在相同数字
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i + startRow][j + startCol] == num)
            {
                return false;
            }
        }
    }

    return true;
}

// 求解所有解的个数
void solveSudoku(int i, int j, SudokuBoard &board, int solutionCount)
{
    if (j == 9)
    {
        i++;
        j = 0;
    }
    if (i == 9)
    {
        resCount++;
        return;
    }

    // 查看此位置是否为空
    if (board[i][j] == 0)
    {
        for (int num = 1; num <= N; num++)
        {
            if (isSafe(board, i, j, num))
            {
                board[i][j] = num;

                // 递归解决剩余的数独
                solveSudoku(i, j + 1, board, solutionCount);
                if (resCount == solutionCount)
                {
                    return; // 及时返回
                }
                // 回溯
                board[i][j] = 0;
            }
        }
    }
    else
    {
        solveSudoku(i, j + 1, board, solutionCount);
    }
}

// 只生成一个结果
SudokuBoard solveSudoku(SudokuBoard board)
{
    resCount = 0;
    SudokuBoard res;
    res = board;
    solveSudoku(0, 0, res, 1);
    return res;
}

// 生成基础数独终局
SudokuBoard generateBaseSudokuBoard()
{
    SudokuBoard board(N, std::vector<int>(N, 0));
    // 随机数引擎
    std::random_device rd;
    std::mt19937 gen(rd());

    // 填充主对角线
    for (int i = 0; i < 9; i += 3)
    {
        std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        std::shuffle(nums.begin(), nums.end(), gen);

        for (int j = 0; j < 3; ++j)
        {
            board[i + j][i + j] = nums[j];
        }
    }

    // 使用回溯算法生成数独终局
    board = solveSudoku(board);
    return board;
}

// 根据基础数独终局生成所有不重复的数独终局
std::vector<SudokuBoard> generateAllSudokuBoards(int numSolutions)
{
    // 初始化数独棋盘，所有单元格都为0
    SudokuBoard board = generateBaseSudokuBoard();
    std::vector<SudokuBoard> allBoards;
    allBoards.push_back(board);

    // 随机行列交换
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 2);

    // 生成变换后的数独终局
    while (allBoards.size() < numSolutions)
    {
        SudokuBoard newBoard = allBoards[0]; // 使用第一个数独终局作为基础
        // 随机交换行
        int rowGroup1 = dis(gen) * 3;
        int rowGroup2 = dis(gen) * 3;
        std::swap(newBoard[rowGroup1], newBoard[rowGroup2]);

        // 随机交换列
        int colGroup1 = dis(gen) * 3;
        int colGroup2 = dis(gen) * 3;
        for (int i = 0; i < 9; ++i)
        {
            std::swap(newBoard[i][colGroup1], newBoard[i][colGroup2]);
        }

        // 将数独终局添加到结果中
        allBoards.push_back(newBoard);
    }

    return allBoards;
}

void printSudokuBoard(const SudokuBoard &board)
{
    for (int i = 0; i < N; i++)
    {
        if (i % 3 == 0)
        {
            std::cout << "+-------+-------+-------+" << std::endl;
        }
        for (int j = 0; j < N; j++)
        {
            if (j % 3 == 0)
            {
                std::cout << "| ";
            }
            std::cout << static_cast<char>(board[i][j] == 0 ? ' ' : board[i][j] + '0')
                      << " ";
        }
        std::cout << "|" << std::endl;
    }
    std::cout << "+-------+-------+-------+" << std::endl;
}

void writeSudokuBoardToFile(const std::string &filename, const std::vector<SudokuBoard> &boards)
{
    std::ofstream fout(filename);
    for (const SudokuBoard &board : boards)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                char v = board[i][j] == 0 ? '$' : board[i][j] + '0';
                fout << v;
            }
        }
        fout << std::endl;
    }
    fout.close();
}

// 从文件中读取数独棋盘
std::vector<SudokuBoard> readSudokuBoardFromFile(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file)
    {
        throw std::runtime_error("Fail not exist!");
    }

    std::vector<SudokuBoard> boards;
    std::string line;

    while (std::getline(file, line) && !line.empty())
    {
        std::stringstream linein(line);

        SudokuBoard board;
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                char v{};
                linein >> v;
                if (!(v >= '1' && v <= '9' || v == '$'))
                {
                    throw std::runtime_error("File format error!");
                }
                if (v == '$')
                {
                    v = '0';
                }
                board[i][j] = v - '0';
            }
        }
        boards.emplace_back(board);
    }

    file.close();
    return boards;
}

// 挖空数独终局生成数独
SudokuBoard digBoard(SudokuBoard finalBoard, int digNum)
{
    // 挖空每个3*3中的两个位置
    int b_i = 0, b_j = 0;
    while (b_i != 9)
    {
        int hole[2];
        hole[0] = genRand() % 9;
        hole[1] = genRand() % 9;

        // 防止重复
        while (hole[0] == hole[1])
        {
            hole[1] = genRand() % 9;
        }

        for (int k = 0; k < 2; ++k)
        {
            int i = hole[k] / 3;
            int j = hole[k] % 3;
            finalBoard[b_i + i][b_j + j] = 0;
        }
        b_j += 3;
        if (b_j == 9)
        {
            b_j = 0;
            b_i += 3;
        }
    }

    // 挖剩下的空
    digNum -= 18;
    while (digNum > 0)
    {
        int i = genRand() % 9;
        int j = genRand() % 9;

        if (finalBoard[i][j] != 0)
        {
            finalBoard[i][j] = 0;
            --digNum;
        }
    }
    return finalBoard;
}

// 生成数独游戏实现
SudokuBoard generateGameSudokuImpl(const SudokuBoard &finalBoard, int mode, std::pair<int, int> range, bool unique)
{
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dist;
    // 这里难度和范围一起决定挖空的个数，将范围按难度分为3个档
    int digNum = 0;
    int choice = (range.second - range.first + 1) % 3;
    if (choice == 0)
    {
        int num = (range.second - range.first + 1) / 3;
        digNum = range.first + (mode - 1) * num + dist(gen) % num;
    }
    else if (choice == 1)
    {
        int num[3] = {(range.second - range.first + 1) / 3, (range.second - range.first + 1) / 3, (range.second - range.first + 1) / 3 + 1};
        digNum = range.first + (mode - 1) * num[0] + dist(gen) % num[mode - 1];
    }
    else if (choice == 2)
    {
        int num[3] = {(range.second - range.first + 1) / 3, (range.second - range.first + 1) / 3 + 1, (range.second - range.first + 1) / 3 + 1};
        digNum = range.first + (mode - 1) * num[0] + dist(gen) % num[mode - 1];
    }

    // 生成唯一解/多解的游戏
    SudokuBoard gameBoard = digBoard(finalBoard, digNum);
    ;

    if (!unique)
    {
        return gameBoard;
    }
    else
    {
        SudokuBoard res;
        // 判断如果当前游戏的解数大于1那么重新生成
        while (1)
        {
            resCount = 0;
            res = gameBoard;
            solveSudoku(0, 0, res, 2);

            if (resCount == 1)
                return gameBoard;
            // 非唯一解，重新生成
            gameBoard = digBoard(finalBoard, digNum);
        }
    }
}

std::vector<SudokuBoard> generateGameSudoku(int count, int mode, std::pair<int, int> range, bool unique)
{

    std::vector<SudokuBoard> result;
    std::vector<SudokuBoard> finalBoards = generateAllSudokuBoards(count);
    result.reserve(count);
    for (int i = 0; i < count; i++)
    {
        printSudokuBoard(finalBoards[i]);
        result.emplace_back(generateGameSudokuImpl(finalBoards[i], mode, range, unique));
    }
    return result;
}