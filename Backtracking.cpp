#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

#define N 8 // Used for N-Queens, Knight's Tour, Hamiltonian Cycle
#define V 5 // Used for Hamiltonian Cycle
#define UNASSIGNED 0 // Used for Sudoku Solver

// --------- N-Queens Problem ----------
bool isSafeNQueen(int board[N][N], int row, int col) {
    for (int i = 0; i < col; i++)
        if (board[row][i]) return false;
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j]) return false;
    for (int i = row, j = col; j >= 0 && i < N; i++, j--)
        if (board[i][j]) return false;
    return true;
}

bool solveNQueensUtil(int board[N][N], int col) {
    if (col >= N) return true;
    for (int i = 0; i < N; i++) {
        if (isSafeNQueen(board, i, col)) {
            board[i][col] = 1;
            if (solveNQueensUtil(board, col + 1)) return true;
            board[i][col] = 0;
        }
    }
    return false;
}

void solveNQueens() {
    int board[N][N] = {0};
    if (solveNQueensUtil(board, 0)) {
        cout << "N-Queens Solution:\n";
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++)
                cout << board[i][j] << " ";
            cout << endl;
        }
    } else cout << "No solution exists.\n";
}

// --------- Sudoku Solver ----------
bool isSafeSudoku(int grid[9][9], int row, int col, int num) {
    for (int x = 0; x < 9; x++)
        if (grid[row][x] == num || grid[x][col] == num) return false;
    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j + startCol] == num) return false;
    return true;
}

bool solveSudoku(int grid[9][9]) {
    int row, col, found = 0;
    for (row = 0; row < 9; row++) {
        for (col = 0; col < 9; col++) {
            if (grid[row][col] == UNASSIGNED) {
                found = 1;
                break;
            }
        }
        if (found) break;
    }
    if (!found) return true;
    for (int num = 1; num <= 9; num++) {
        if (isSafeSudoku(grid, row, col, num)) {
            grid[row][col] = num;
            if (solveSudoku(grid)) return true;
            grid[row][col] = UNASSIGNED;
        }
    }
    return false;
}

void printSudoku(int grid[9][9]) {
    cout << "Sudoku Solution:\n";
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++)
            cout << grid[i][j] << " ";
        cout << endl;
    }
}

// --------- Knight's Tour ----------
int knightMovesX[8] = {2, 1, -1, -2, -2, -1, 1, 2};
int knightMovesY[8] = {1, 2, 2, 1, -1, -2, -2, -1};
bool isSafeKnight(int x, int y, int sol[N][N]) {
    return (x >= 0 && x < N && y >= 0 && y < N && sol[x][y] == -1);
}

bool solveKnightUtil(int x, int y, int movei, int sol[N][N]) {
    if (movei == N * N) return true;
    for (int k = 0; k < 8; k++) {
        int nextX = x + knightMovesX[k];
        int nextY = y + knightMovesY[k];
        if (isSafeKnight(nextX, nextY, sol)) {
            sol[nextX][nextY] = movei;
            if (solveKnightUtil(nextX, nextY, movei + 1, sol)) return true;
            sol[nextX][nextY] = -1;
        }
    }
    return false;
}

void solveKnightTour() {
    int sol[N][N];
    memset(sol, -1, sizeof(sol));
    sol[0][0] = 0;
    if (solveKnightUtil(0, 0, 1, sol)) {
        cout << "Knight's Tour Solution:\n";
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++)
                cout << sol[i][j] << " ";
            cout << endl;
        }
    } else cout << "No solution exists.\n";
}

// --------- Hamiltonian Cycle ----------
int graph[V][V] = {{0, 1, 0, 1, 0},
                   {1, 0, 1, 1, 1},
                   {0, 1, 0, 0, 1},
                   {1, 1, 0, 0, 1},
                   {0, 1, 1, 1, 0}};
int path[V];

bool isSafeHamiltonian(int v, int pos) {
    if (!graph[path[pos - 1]][v]) return false;
    for (int i = 0; i < pos; i++)
        if (path[i] == v) return false;
    return true;
}

bool solveHamiltonianUtil(int pos) {
    if (pos == V) return graph[path[pos - 1]][path[0]];
    for (int v = 1; v < V; v++) {
        if (isSafeHamiltonian(v, pos)) {
            path[pos] = v;
            if (solveHamiltonianUtil(pos + 1)) return true;
            path[pos] = -1;
        }
    }
    return false;
}

void solveHamiltonianCycle() {
    memset(path, -1, sizeof(path));
    path[0] = 0;
    if (solveHamiltonianUtil(1)) {
        cout << "Hamiltonian Cycle:\n";
        for (int i = 0; i < V; i++) cout << path[i] << " ";
        cout << path[0] << endl;
    } else cout << "No solution exists.\n";
}

// --------- Subset Sum Problem ----------
bool subsetSum(vector<int> &arr, int sum, int n) {
    if (sum == 0) return true;
    if (n == 0) return false;
    if (arr[n - 1] > sum) return subsetSum(arr, sum, n - 1);
    return subsetSum(arr, sum - arr[n - 1], n - 1) || subsetSum(arr, sum, n - 1);
}

// --------- Main Function ----------
int main() {
    solveNQueens();
    int sudokuGrid[9][9] = { /* Add valid Sudoku grid */ };
    solveSudoku(sudokuGrid);
    printSudoku(sudokuGrid);
    solveKnightTour();
    solveHamiltonianCycle();
    vector<int> subsetArr = {3, 34, 4, 12, 5, 2};
    int sum = 9;
    cout << "Subset Sum Exists: " << (subsetSum(subsetArr, sum, subsetArr.size()) ? "Yes" : "No") << endl;
    return 0;
}
