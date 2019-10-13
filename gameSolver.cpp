#include <iostream>
#include <vector>
using namespace std;

/* helper function to display solutions */
void printBoard(vector<vector<int>> board)
{
    for (vector<int> row : board)
    {
        for (int item : row)
        {
            cout << item << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void printHistory(vector<vector<vector<int>>> history)
{
    for (vector<vector<int>> board : history)
    {
        printBoard(board);
    }
}

/*game logic*/
int manageColor(int color, int colorAmount)
{
    return (color + 1) % colorAmount;
}

vector<std::vector<int>> clickBoard(int row, int column, vector<vector<int>> board, int colorAmount)
{
    vector<vector<int>> tempBoard(board);
    const int rows = tempBoard.size();
    const int columns = tempBoard[0].size();

    tempBoard[row][column] = manageColor(tempBoard[row][column], colorAmount);
    for (int offset = -1; offset < 2; offset += 2)
    {

        if (row + offset >= 0 && row + offset < columns)
            tempBoard[row + offset][column] = manageColor(tempBoard[row + offset][column], colorAmount);
        if (column + offset >= 0 && column + offset < rows)
            tempBoard[row][column + offset] = manageColor(tempBoard[row][column + offset], colorAmount);
    }
    return tempBoard;
}

bool checkWin(vector<vector<int>> board)
{
    const int check = board[0][0];
    for (vector<int> row : board)
    {
        for (int item : row)
        {
            if (check != item)
                return false;
        }
    }
    return true;
}

void findSolution(int rows, int columns, vector<vector<vector<int>>> history, int clickAmount, int colorAmount)
{

    vector<vector<int>> board(history.back());
    if (clickAmount <= 0)
    {
        if (checkWin(board))
        {
            cout << "Solved" << endl;
            printHistory(history);
        }
    }
    else
    {
        for (int row = 0; row < rows; row++)
        {
            for (int column = 0; column < columns; column++)
            {
                vector<vector<int>> tempBoard = clickBoard(row, column, board, colorAmount);
                vector<vector<vector<int>>> tempHistory(history);

                tempHistory.push_back(tempBoard);
                findSolution(rows, columns, tempHistory, clickAmount - 1, colorAmount);
            }
        }
    }
}

int main(int argc, char *argv[])
{
    int rows = 3;
    int columns = 3;
    int colorAmount = 3;
    int clickAmount = 2;
    vector<vector<int>> board = {{2, 2, 2}, {2, 2, 1}, {2, 1, 1}};
    vector<vector<vector<int>>> history(1, board);
    cout << "Searching Solution with " << clickBoard << clickAmount << endl;
    findSolution(rows, columns, history, clickAmount, colorAmount);
    cout << "Done!" << endl;
}