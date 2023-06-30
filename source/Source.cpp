#include <iostream>
#include <fstream>
#include <random>
#include <algorithm>
#include <string>

const int N = 9;
const int EMPTY = 0;

bool isSafe(int grid[N][N], int row, int col, int num) {
    // ��������Ƿ������ͬ����
    for (int i = 0; i < N; i++) {
        if (grid[row][i] == num) {
            return false;
        }
    }

    // ��������Ƿ������ͬ����
    for (int i = 0; i < N; i++) {
        if (grid[i][col] == num) {
            return false;
        }
    }

    // ���3x3�������Ƿ������ͬ����
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

    // ����δ����λ��
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

    // ����λ�ö�����䣬�����ѽ��
    if (!isEmpty) {
        return true;
    }

    // �����������
    for (int num = 1; num <= N; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;

            // �ݹ���ʣ�������
            if (solveSudoku(grid)) {
                return true;
            }

            // ����
            grid[row][col] = EMPTY;
        }
    }

    return false;
}

void generateSudoku(int grid[N][N]) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, N);

    // ���������������վ�
    solveSudoku(grid);

    // ����Ƴ���������
    int count = N * N - 1; // ��Ҫ�Ƴ�����������
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
        std::cout << "�����վ��ѱ��浽�ļ���" << filename << std::endl;
    }
    else {
        std::cout << "�޷����ļ���" << filename << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc == 3 && std::string(argv[1]) == "-c") {
        // ���������վֲ����浽�ļ�
        int numGames = std::stoi(argv[2]);
        for (int i = 1; i <= numGames; i++) {
            int grid[N][N] = { 0 };
            generateSudoku(grid);
            std::string filename = "sudoku_" + std::to_string(i) + ".txt";
            saveSudokuToFile(grid, filename);
        }
    }
    else if (argc == 3 && std::string(argv[1]) == "-s") {
        // ���ļ��ж�ȡ�������Ⲣ���
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

            std::cout << "��ȡ�������⣺" << filename << std::endl;
            std::cout << "�����..." << std::endl;

            if (solveSudoku(grid)) {
                std::cout << "���������ѽ����" << std::endl;
                for (int row = 0; row < N; row++) {
                    for (int col = 0; col < N; col++) {
                        std::cout << grid[row][col] << " ";
                    }
                    std::cout << std::endl;
                }
            }
            else {
                std::cout << "�޽�" << std::endl;
            }
        }
        else {
            std::cout << "�޷����ļ���" << filename << std::endl;
        }
    }
    else {
        std::cout << "��Ч�������в���" << std::endl;
    }

    return 0;
}
