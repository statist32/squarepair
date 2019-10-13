#include <iostream>
#include <vector>
#include <chrono>
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
void testEachTile(int rows, int columns, vector<vector<vector<int>>> history, int clickAmount, int colorAmount)
{
    vector<vector<int>> board(history.back());
    for (int row = 0; row < rows; row++)
    {
        for (int column = 0; column < columns; column++)
        {
            vector<vector<int>> tempBoard = clickBoard(row, column, board, colorAmount);
            vector<vector<vector<int>>> tempHistory(history);
            tempHistory.push_back(tempBoard);
            if (checkWin(tempBoard))
            {
                printHistory(tempHistory);
            }
        }
    }
}

vector<vector<int>> manageCounter(vector<vector<int>> tempCounter, int colorAmount)
{
    vector<vector<int>> counter(tempCounter);
    for (int row = 0; row < counter.size(); row++)
    {
        for (int column = 0; column < counter[0].size(); column++)
        {
            while (counter[row][column] >= colorAmount)
            {
                counter[row][column] -= colorAmount;
                if (column + 1 < counter[0].size())
                {
                    counter[row][column + 1]++;
                }
                else if (row + 1 < counter.size())
                {
                    counter[row + 1][0]++;
                }
            }
        }
    }
    return counter;
}

vector<vector<int>> increaseCounter(vector<vector<int>> tempCounter, int colorAmount)
{
    vector<vector<int>> counter(tempCounter);
    counter[0][0]++;
    counter = manageCounter(counter, colorAmount);
    return counter;
}

vector<vector<int>> addBoards(vector<vector<int>> board1, vector<vector<int>> board2, int colorAmount)
{
    vector<vector<int>> tempBoard(board1);
    for (int row = 0; row < tempBoard.size(); row++)
    {
        for (int column = 0; column < tempBoard[0].size(); column++)
        {
            tempBoard[row][column] += board2[row][column];
        }
    }
    tempBoard = manageCounter(tempBoard, colorAmount);
    return tempBoard;
}

void findSolution(int rows, int columns, vector<vector<vector<int>>> history, int clickAmount, int colorAmount)
{
    vector<vector<int>> board(history.back());
    vector<vector<int>> counter(rows, {0, 1, 2});
    counter = addBoards(board, counter, colorAmount);
    printBoard(counter);
}

int main(int argc, char *argv[])
{
    int rows = 3;
    int columns = 3;
    int colorAmount = 3;
    int clickAmount = 1;
    vector<vector<int>> board = {{1, 1, 1}, {1, 1, 0}, {1, 0, 0}};
    vector<vector<vector<int>>> history(1, board);

    findSolution(rows, columns, history, clickAmount, colorAmount);
}

// for (int click = 1; click < clickAmount; click++)
// {

//     const auto start = chrono::steady_clock::now();
//     cout << "Searching a solution with " << click << " clicks\n";
//     findSolution(rows, columns, history, click, colorAmount);
//     const auto end = chrono::steady_clock::now();
//     cout << "Done in " << chrono::duration_cast<chrono::seconds>(end - start).count() << " seconds!" << endl;
// }