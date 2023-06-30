#include <iostream>
#include <fstream>
#include <random>
#include <algorithm>
#include <string>

const int N = 9;
const int EMPTY = 0;

bool isSafe(int grid[N][N], int row, int col, int num) {
    // 检查行中是否存在相同数字
    for (int i = 0; i < N; i++) {
        if (grid[row][i] == num) {
            return false;
        }
    }

    // 检查列中是否存在相同数字
    for (int i = 0; i < N; i++) {
        if (grid[i][col] == num) {
            return false;
        }
    }

    // 检查3x3方格中是否存在相同数字
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

bool solveSudoku(int grid[N][N]) {
    int row, col;
    bool isEmpty = false;

    // 查找未填充的位置
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (grid[row][col] == EMPTY) {
                isEmpty = true;
                break;
            }
        }
        if (isEmpty) {
            break;
        }
    }

    // 所有位置都已填充，数独已解决
    if (!isEmpty) {
        return true;
    }

    // 尝试填充数字
    for (int num = 1; num <= N; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;

            // 递归解决剩余的数独
            if (solveSudoku(grid)) {
                return true;
            }

            // 回溯
            grid[row][col] = EMPTY;
        }
    }

    return false;
}

void generateSudoku(int grid[N][N]) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, N);

    // 生成完整的数独终局
    solveSudoku(grid);

    // 随机移除部分数字
    int count = N * N - 1; // 需要移除的数字数量
    while (count > 0) {
        int row = dis(gen) - 1;
        int col = dis(gen) - 1;
        if (grid[row][col] != EMPTY) {
            grid[row][col] = EMPTY;
            count--;
        }
    }
}

void saveSudokuToFile(int grid[N][N], const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (int row = 0; row < N; row++) {
            for (int col = 0; col < N; col++) {
                file << grid[row][col] << " ";
            }
            file << std::endl;
        }
        file.close();
        std::cout << "数独终局已保存到文件：" << filename << std::endl;
    }
    else {
        std::cout << "无法打开文件：" << filename << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc == 3 && std::string(argv[1]) == "-c") {
        // 生成数独终局并保存到文件
        int numGames = std::stoi(argv[2]);
        for (int i = 1; i <= numGames; i++) {
            int grid[N][N] = { 0 };
            generateSudoku(grid);
            std::string filename = "sudoku_" + std::to_string(i) + ".txt";
            saveSudokuToFile(grid, filename);
        }
    }
    else if (argc == 3 && std::string(argv[1]) == "-s") {
        // 从文件中读取数独问题并求解
        std::string filename = argv[2];
        std::ifstream file(filename);
        if (file.is_open()) {
            int grid[N][N] = { 0 };
            for (int row = 0; row < N; row++) {
                for (int col = 0; col < N; col++) {
                    file >> grid[row][col];
                }
            }
            file.close();

            std::cout << "读取数独问题：" << filename << std::endl;
            std::cout << "求解中..." << std::endl;

            if (solveSudoku(grid)) {
                std::cout << "数独问题已解决：" << std::endl;
                for (int row = 0; row < N; row++) {
                    for (int col = 0; col < N; col++) {
                        std::cout << grid[row][col] << " ";
                    }
                    std::cout << std::endl;
                }
            }
            else {
                std::cout << "无解" << std::endl;
            }
        }
        else {
            std::cout << "无法打开文件：" << filename << std::endl;
        }
    }
    else {
        std::cout << "无效的命令行参数" << std::endl;
    }

    return 0;
}
