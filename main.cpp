#include <iostream>
using namespace std;

const int SIZE = 9;

void printBoard(int board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

bool isSafe(int board[SIZE][SIZE], int row, int col, int num) {
    for (int i = 0; i < SIZE; i++) {
        if (board[row][i] == num || board[i][col] == num) {
            return false;
        }
    }
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

bool solveSudoku(int board[SIZE][SIZE]) {
    int row, col;

    bool isEmpty = false;
    for (row = 0; row < SIZE; row++) {
        for (col = 0; col < SIZE; col++) {
            if (board[row][col] == 0) {
                isEmpty = true;
                break;
            }
        }
        if (isEmpty) {
            break;
        }
    }

    if (!isEmpty) {
        return true;
    }

    for (int num = 1; num <= 9; num++) {
        if (isSafe(board, row, col, num)) {
            board[row][col] = num;

            if (solveSudoku(board)) {
                return true;
            }

            board[row][col] = 0;
        }
    }

    return false;
}

int main() {
    int board[SIZE][SIZE] = {
            {5, 3, 0, 0, 7, 0, 9, 0, 2},
            {6, 0, 0, 1, 9, 5, 0, 0, 0},
            {0, 9, 8, 0, 0, 0, 0, 6, 0},
            {8, 0, 0, 0, 6, 0, 4, 0, 3},
            {4, 2, 0, 8, 0, 3, 0, 0, 1},
            {7, 0, 3, 0, 2, 0, 8, 0, 6},
            {0, 6, 0, 0, 0, 0, 2, 8, 0},
            {0, 0, 0, 4, 1, 9, 0, 0, 5},
            {0, 0, 5, 2, 8, 0, 0, 7, 9}
    };


    printBoard(board);

    while (true) {
        int row, col, num;
        cout << "Введите координаты (строка и столбец) и число (от 1 до 9): ";
        cin >> row >> col >> num;

        if (row < 1 || row > 9 || col < 1 || col > 9 || num < 1 || num > 9) {
            cout << "Некорректный ввод." << endl;
            continue;
        }

        if (board[row - 1][col - 1] == 0 && isSafe(board, row - 1, col - 1, num)) {
            board[row - 1][col - 1] = num;
            printBoard(board);

            bool isComplete = true;
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    if (board[i][j] == 0) {
                        isComplete = false;
                        break;
                    }
                }
                if (!isComplete) {
                    break;
                }
            }

            if (isComplete) {
                cout << "Победа вместо обеда" << endl;
                break;
            }
        } else {
            cout << "Невозможно разместить число в данной позиции." << endl;
        }
    }
    return 0;
}