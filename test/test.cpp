#include <gtest/gtest.h>
#include <fstream>
#include "../include/sudoku.h"

// 测试打印数独棋盘函数
TEST(PrintSudokuBoardTest, PrintsBoardCorrectly) {
  // 创建一个数独棋盘
  const std::array<std::array<int, 9>, 9> board = {{
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    }};

  // 期望的打印结果
  std::string expectedOutput = "+-------+-------+-------+\n"
                               "| 5 3   |   7   |       |\n"
                               "| 6     | 1 9 5 |       |\n"
                               "|   9 8 |       |   6   |\n"
                               "+-------+-------+-------+\n"
                               "| 8     |   6   |     3 |\n"
                               "| 4     | 8   3 |     1 |\n"
                               "| 7     |   2   |     6 |\n"
                               "+-------+-------+-------+\n"
                               "|   6   |       | 2 8   |\n"
                               "|       | 4 1 9 |     5 |\n"
                               "|       |   8   |   7 9 |\n"
                               "+-------+-------+-------+\n";

  // 重定向标准输出到一个文件流
  testing::internal::CaptureStdout();
  // 调用打印数独棋盘函数
  printSudokuBoard(board);
  // 获取实际的打印结果
  std::string actualOutput = testing::internal::GetCapturedStdout();

  // 断言期望的打印结果和实际的打印结果相等
  EXPECT_EQ(expectedOutput, actualOutput);
}

// 测试从文件中读取数独棋盘函数
TEST(ReadSudokuBoardFromFileTest, ReadsBoardFromFile) {
  // 创建一个临时文件并写入数独棋盘数据
  std::string filename = "test_board.txt";
  std::ofstream file(filename);
  file << "$1$3$6$$93467$9$127$$51$346$2346$89$4678951238$$12$4$$23467$95167895$$34$$12$467$\n";
  file.close();

  // 调用从文件中读取数独棋盘函数
  std::vector<SudokuBoard> boards = readSudokuBoardFromFile(filename);

  // 断言读取到的数独棋盘数据与期望的数据相等
  EXPECT_EQ(1, boards.size());
  EXPECT_EQ(9, boards[0].size());
  EXPECT_EQ(9, boards[0][0].size());
  EXPECT_EQ(0, boards[0][0][0]);
  EXPECT_EQ(1, boards[0][0][1]);
  EXPECT_EQ(0, boards[0][0][2]);
  // ... 检查其余的数独棋盘数据

  // 删除临时文件
  std::remove(filename.c_str());
}

// Test case for generateGameSudoku function
TEST(ShuduTest, GenerateGameSudokuTest) {
    // Test case 1
    int count = 5;
    int mode = 1;
    std::pair<int, int> range(30, 40);
    bool unique = true;
    std::vector<SudokuBoard> result = generateGameSudoku(count, mode, range, unique);
    // Add your assertions here to validate the result
    ASSERT_EQ(result.size(), count);
}

// Test case for solveSudoku function
TEST(ShuduTest, SolveSudokuTest) {
    // Test case 1
    SudokuBoard board = {0,1,0,3,0,6,0,0,9,3,4,6,7,0,9,0,1,2,7,0,0,5,1,0,3,4,6,0,2,3,4,6,0,8,9,0,4,6,7,8,9,5,1,2,3,8,0,0,1,2,0,4,0,0,2,3,4,6,7,0,9,5,1,6,7,8,9,5,0,0,3,4,0,0,1,2,0,4,6,7,0};
    SudokuBoard result = solveSudoku(board);
    SudokuBoard trueres = {5,1,2,3,4,6,7,8,9,3,4,6,7,8,9,5,1,2,7,8,9,5,1,2,3,4,6,1,2,3,4,6,7,8,9,5,4,6,7,8,9,5,1,2,3,8,9,5,1,2,3,4,6,7,2,3,4,6,7,8,9,5,1,6,7,8,9,5,1,2,3,4,9,5,1,2,3,4,6,7,8};
    ASSERT_EQ(trueres, result);
}

// Test case for generateAllSudokuBoards function
TEST(ShuduTest, GenerateAllSudokuBoardsTest) {
    // Test case 1
    int numSolutions = 10;
    std::vector<SudokuBoard> result = generateAllSudokuBoards(numSolutions);
    ASSERT_EQ(result.size(), numSolutions);
}

// Test case for generateGameSudokuImpl function
TEST(ShuduTest, GenerateGameSudokuImplTest) {
    // Test case 1
    SudokuBoard finalBoard = {1,2,3,4,5,6,7,8,9,4,5,6,7,8,9,1,2,3,7,8,9,1,2,3,4,5,6,2,3,4,5,6,7,8,9,1,5,6,7,8,9,1,2,3,4,8,9,1,2,3,4,5,6,7,3,4,5,6,7,8,9,1,2,6,7,8,9,1,2,3,4,5,9,1,2,3,4,5,6,7,8};

    int mode = 1;
    std::pair<int, int> range(30, 40);
    bool unique = true;

    SudokuBoard result = generateGameSudokuImpl(finalBoard, mode, range, unique);

}

// Test case for digBoard function
TEST(ShuduTest, DigBoardTest) {
    // Test case 1
    SudokuBoard finalBoard = {1,2,3,4,5,6,7,8,9,4,5,6,7,8,9,1,2,3,7,8,9,1,2,3,4,5,6,2,3,4,5,6,7,8,9,1,5,6,7,8,9,1,2,3,4,8,9,1,2,3,4,5,6,7,3,4,5,6,7,8,9,1,2,6,7,8,9,1,2,3,4,5,9,1,2,3,4,5,6,7,8};

    int digNum = 35;

    SudokuBoard result = digBoard(finalBoard, digNum);
    int nums = 0;
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(result[i][j] == 0){
                nums++;
            }
        }
    }
    ASSERT_EQ(digNum, nums);
    
}

// Test case for solveSudoku function (overloaded version)
TEST(ShuduTest, SolveSudokuOverloadedTest) {
    // Test case 1
    SudokuBoard board = {0,1,0,3,0,6,0,0,9,3,4,6,7,0,9,0,1,2,7,0,0,5,1,0,3,4,6,0,2,3,4,6,0,8,9,0,4,6,7,8,9,5,1,2,3,8,0,0,1,2,0,4,0,0,2,3,4,6,7,0,9,5,1,6,7,8,9,5,0,0,3,4,0,0,1,2,0,4,6,7,0};
    
    int solutionCount = 0;
    solveSudoku(0, 0, board, solutionCount);
    
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
