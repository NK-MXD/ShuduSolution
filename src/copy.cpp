// 只生成一个结果
bool solveSudoku(SudokuBoard &board)
{
    int row, col;
    bool isEmpty = false;

    // 查找未填充的位置
    for (row = 0; row < N; row++)
    {
        for (col = 0; col < N; col++)
        {
            if (board[row][col] == EMPTY)
            {
                isEmpty = true;
                break;
            }
        }
        if (isEmpty)
        {
            break;
        }
    }

    // 所有位置都已填充，数独已解决
    if (!isEmpty)
    {
        return true;
    }

    // 尝试填充数字
    for (int num = 1; num <= N; num++)
    {
        if (isSafe(board, row, col, num))
        {
            board[row][col] = num;

            // 递归解决剩余的数独
            if (solveSudoku(board))
            {
                return true;
            }

            // 回溯
            board[row][col] = EMPTY;
        }
    }

    return false;
}
