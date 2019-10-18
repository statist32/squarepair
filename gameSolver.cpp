#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>
#include <set>
using namespace std;

/* helper function to display and store solutions */
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

void printSolution(pair<vector<vector<int>>, vector<pair<int, int>>> solution)
{
    vector<vector<int>> board = solution.first;
    vector<pair<int, int>> clicks = solution.second;
    printBoard(board);
    for (pair<int, int> click : clicks)
    {
        const int row = click.first;
        const int column = click.second;

        cout << "(" << row << "," << column << "), ";
    }
    cout << endl;
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

bool containsBoard(vector<pair<vector<vector<int>>, vector<pair<int, int>>>> solutions, vector<vector<int>> board)
{
    for (pair<vector<vector<int>>, vector<pair<int, int>>> solution : solutions)
    {
        if (solution.first == board)
        {
            return true;
        }
    }
    return false;
}
/* Solver*/

void findSolutions(int rows, int columns, int colorAmount)
{
    cout << "Computing all possible solutions for a " << rows << " * " << columns << " board with " << colorAmount << " colors." << endl;
    vector<pair<vector<vector<int>>, vector<pair<int, int>>>> solutionsAll;
    vector<pair<vector<vector<int>>, vector<pair<int, int>>>> solutionsLast;
    vector<pair<vector<vector<int>>, vector<pair<int, int>>>> solutionsCurrent;

    bool finished = false;
    for (int color = 0; color < colorAmount; color++)
    {
        vector<vector<int>> tempBoard = {{color, color, color}, {color, color, color}, {color, color, color}};
        solutionsAll.push_back(make_pair(tempBoard, vector<pair<int, int>>{make_pair(-1, -1)}));
        solutionsLast.push_back(make_pair(tempBoard, vector<pair<int, int>>{make_pair(-1, -1)}));
    }
    for (int step = 1; !finished; step++)
    {
        for (int click = 0; click < rows * columns; click++)
        {
            const int row = click / columns;
            const int column = click % columns;
            for (pair<vector<vector<int>>, vector<pair<int, int>>> solution : solutionsLast)
            {
                vector<vector<int>> board(solution.first);
                vector<pair<int, int>> clicks(solution.second);
                vector<vector<int>> tempBoard = clickBoard(row, column, board, colorAmount);

                if (!containsBoard(solutionsAll, tempBoard))
                {
                    vector<pair<int, int>> tempClicks(clicks);
                    tempClicks.push_back(make_pair(row, column));
                    solutionsAll.push_back(make_pair(tempBoard, tempClicks));
                    solutionsCurrent.push_back(make_pair(tempBoard, tempClicks));
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
            printSolution(solutionsAll[180]);
        }
    }
}

int main(int argc, char *argv[])
{
    int rows = 3;
    int columns = 3;
    int colorAmount = 3;
    vector<vector<int>> board = {{1, 1, 1},
                                 {1, 1, 1},
                                 {1, 1, 0}};
    const auto start = chrono::steady_clock::now();
    findSolutions(rows, columns, colorAmount);
    const auto end = chrono::steady_clock::now();
    cout << "Done in " << chrono::duration_cast<chrono::seconds>(end - start).count() << " s!" << endl;
}
