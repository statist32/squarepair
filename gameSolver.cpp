#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>
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

void findSolutionRecursive(int rows, int columns, vector<vector<vector<int>>> history, int clickAmount, int colorAmount)
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
                findSolutionRecursive(rows, columns, tempHistory, clickAmount - 1, colorAmount);
            }
        }
    }
}

vector<int> incrementClicks(vector<int> clicks, int rows, int columns)
{
    vector<int> tempClicks(clicks);
    const int dimension = rows * columns;
    const int size = tempClicks.size();
    bool finished = false;
    for (int i = size - 1; i >= 0 && !finished; i--)
    {
        tempClicks[i] = (tempClicks[i] + 1) % dimension;
        if (tempClicks[i])
        {
            finished = true;
        }
        if (!i && !finished)
        {
            tempClicks.push_back(0);
        }
    }

    return tempClicks;
}

void findSolutionIterative(int rows, int columns, vector<vector<int>> startBoard, int clickAmount, int colorAmount)
{
    vector<vector<int>> board(startBoard);
    vector<int> clicks(1, 0);
    bool finished = false;
    for (int rounds = 0; (rounds < pow((rows * columns), 10)) && !finished; rounds++)
    {
        vector<vector<int>> tempBoard(board);
        for (int click : clicks)
        {
            int row = click / columns;
            int column = click % columns;

            tempBoard = clickBoard(row, column, tempBoard, colorAmount);
        }
        if (checkWin(tempBoard))
        {
            cout << "Solved in " << clicks.size() << " steps with these steps" << endl;
            for (int click : clicks)
            {
                cout << click << " ";
            }
            cout << endl;
            finished = true;
        }

        clicks = incrementClicks(clicks, rows, columns);
    }
}

int main(int argc, char *argv[])
{
    int rows = 3;
    int columns = 3;
    int colorAmount = 3;
    int clickAmount = 1;
    vector<vector<int>> board = {{1, 1, 1},
                                 {1, 1, 1},
                                 {1, 1, 0}};
    const auto start = chrono::steady_clock::now();
    findSolutionIterative(rows, columns, board, clickAmount, colorAmount);
    const auto end = chrono::steady_clock::now();
    cout << "Done in " << chrono::duration_cast<chrono::seconds>(end - start).count() << " seconds!" << endl;
}

// for (int click = 1; click < clickAmount; click++)
// {

//     const auto start = chrono::steady_clock::now();
//     cout << "Searching a solution with " << click << " clicks\n";
//     findSolution(rows, columns, history, click, colorAmount);
//     const auto end = chrono::steady_clock::now();
//     cout << "Done in " << chrono::duration_cast<chrono::seconds>(end - start).count() << " seconds!" << endl;
// }