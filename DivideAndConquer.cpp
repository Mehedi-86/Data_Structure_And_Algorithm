#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>
#include <cfloat>  // Fix for DBL_MAX

using namespace std;

// Helper functions for Strassen's Multiplication
vector<vector<int>> addMatrix(const vector<vector<int>> &A, const vector<vector<int>> &B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
    return C;
}

vector<vector<int>> subtractMatrix(const vector<vector<int>> &A, const vector<vector<int>> &B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
    return C;
}

// Strassen’s Matrix Multiplication
vector<vector<int>> strassen(const vector<vector<int>> &A, const vector<vector<int>> &B) {
    int n = A.size();
    if (n == 1) {
        return {{A[0][0] * B[0][0]}};
    }

    int newSize = n / 2;
    vector<vector<int>> A11(newSize, vector<int>(newSize)), A12(newSize, vector<int>(newSize)),
        A21(newSize, vector<int>(newSize)), A22(newSize, vector<int>(newSize)),
        B11(newSize, vector<int>(newSize)), B12(newSize, vector<int>(newSize)),
        B21(newSize, vector<int>(newSize)), B22(newSize, vector<int>(newSize));

    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    auto P1 = strassen(A11, subtractMatrix(B12, B22));
    auto P2 = strassen(addMatrix(A11, A12), B22);
    auto P3 = strassen(addMatrix(A21, A22), B11);
    auto P4 = strassen(A22, subtractMatrix(B21, B11));
    auto P5 = strassen(addMatrix(A11, A22), addMatrix(B11, B22));
    auto P6 = strassen(subtractMatrix(A12, A22), addMatrix(B21, B22));
    auto P7 = strassen(subtractMatrix(A11, A21), addMatrix(B11, B12));

    vector<vector<int>> C(n, vector<int>(n));
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = P5[i][j] + P4[i][j] - P2[i][j] + P6[i][j];
            C[i][j + newSize] = P1[i][j] + P2[i][j];
            C[i + newSize][j] = P3[i][j] + P4[i][j];
            C[i + newSize][j + newSize] = P5[i][j] + P1[i][j] - P3[i][j] - P7[i][j];
        }
    }
    return C;
}

// Closest Pair of Points (Divide & Conquer)
struct Point {
    double x, y;
};

double distance(Point p1, Point p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

double closestUtil(vector<Point> &points, int left, int right) {
    if (right - left <= 3) {
        double minDist = DBL_MAX;
        for (int i = left; i < right; i++)
            for (int j = i + 1; j < right; j++)
                minDist = min(minDist, distance(points[i], points[j]));
        return minDist;
    }

    int mid = (left + right) / 2;
    double dLeft = closestUtil(points, left, mid);
    double dRight = closestUtil(points, mid, right);
    double d = min(dLeft, dRight);

    vector<Point> strip;
    for (int i = left; i < right; i++)
        if (fabs(points[i].x - points[mid].x) < d)
            strip.push_back(points[i]);

    sort(strip.begin(), strip.end(), [](Point a, Point b) { return a.y < b.y; });

    for (int i = 0; i < strip.size(); i++)
        for (int j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < d; j++)
            d = min(d, distance(strip[i], strip[j]));

    return d;
}

double closestPair(vector<Point> &points) {
    sort(points.begin(), points.end(), [](Point a, Point b) { return a.x < b.x; });
    return closestUtil(points, 0, points.size());
}

// Towers of Hanoi
void towersOfHanoi(int n, char from, char to, char aux) {
    if (n == 1) {
        cout << "Move disk 1 from " << from << " to " << to << endl;
        return;
    }
    towersOfHanoi(n - 1, from, aux, to);
    cout << "Move disk " << n << " from " << from << " to " << to << endl;
    towersOfHanoi(n - 1, aux, to, from);
}

// Main Function
int main() {
    // Test Strassen's Algorithm
    vector<vector<int>> A = {{1, 2}, {3, 4}};
    vector<vector<int>> B = {{5, 6}, {7, 8}};
    vector<vector<int>> result = strassen(A, B);

    cout << "Strassen’s Matrix Multiplication Result:\n";
    for (auto &row : result) {
        for (auto &elem : row)
            cout << elem << " ";
        cout << endl;
    }

    // Test Closest Pair of Points
    vector<Point> points = {{2.1, 3.5}, {12.3, 30.1}, {40.0, 50.2}, {5.0, 1.2}, {3.0, 4.8}};
    cout << "Closest Distance: " << closestPair(points) << endl;

    // Test Towers of Hanoi
    cout << "Towers of Hanoi Moves:\n";
    towersOfHanoi(3, 'A', 'C', 'B');

    return 0;
}
