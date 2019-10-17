#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>
#include <set>
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

void findSolutionIterative(int rows, int columns, vector<vector<int>> startBoard, int colorAmount)
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

void findSolutions(int rows, int columns, int colorAmount)
{
    cout << "Computing all possible solutions for a " << rows << " * " << columns << " board with " << colorAmount << " colors." << endl;
    set<vector<vector<int>>> solutionsAll;
    set<vector<vector<int>>> solutionsLast;
    set<vector<vector<int>>> solutionsCurrent;
    bool finished = false;
    for (int color = 0; color < colorAmount; color++)
    {
        vector<vector<int>> tempBoard = {{color, color, color}, {color, color, color}, {color, color, color}};
        solutionsAll.insert(tempBoard);
        solutionsLast.insert(tempBoard);
    }

    for (int step = 1; !finished; step++)
    {
        for (int click = 0; click < rows * columns; click++)
        {
            const int row = click / columns;
            const int column = click % columns;
            for (vector<vector<int>> board : solutionsLast)
            {
                vector<vector<int>> tempBoard = clickBoard(row, column, board, colorAmount);
                if (!solutionsAll.count(tempBoard))
                {
                    solutionsAll.insert(tempBoard);
                    solutionsCurrent.insert(tempBoard);
                }
            }
        }
        solutionsLast = solutionsCurrent;
        solutionsCurrent.clear();
        cout << solutionsLast.size() << " new solutions found with " << step << " steps." << endl;
        if (!solutionsLast.size())
        {
            finished = true;
            cout << "Number of unique boards: " << solutionsAll.size() << endl;
        }
    }
}

int main(int argc, char *argv[])
{
    int rows = 3;
    int columns = 3;
    int colorAmount = 6;
    vector<vector<int>> board = {{1, 1, 1},
                                 {1, 1, 1},
                                 {1, 1, 0}};
    const auto start = chrono::steady_clock::now();
    findSolutions(rows, columns, colorAmount);
    const auto end = chrono::steady_clock::now();
    cout << "Done in " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms!" << endl;
}
