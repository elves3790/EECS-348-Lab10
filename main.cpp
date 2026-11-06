#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <iomanip>
#include <algorithm> // for std::swap

class Matrix{
private:
    int N;
    int** data;

public:
    //constructor
    Matrix(int size){
    N = size;
    data = new int*[N];
    for(int i = 0; i<N; i++){
        data[i] = new int[N];
    }
    }

    ~Matrix(){
    for(int i =0; i < N; i++){
        delete[] data[i];
    }
    delete[] data; //
    }

    Matrix(const Matrix& other) {
        N = other.N;
        data = new int*[N];
        for (int i = 0; i < N; i ++){
            data[i] = new int*[N];
            for (int j = 0; j < N; j++){
                data[i][j] = other.data[i][j];
            }
        }

    }
    Matrix& operator=(const Matrix& other) {
    if (this == &other) {
        return *this; // Self-assignment check
    }

    // 1. Clean up old memory
    for (int i = 0; i < N; i++) {
        delete[] data[i];
    }
    delete[] data;

    // 2. Allocate and copy new memory
    N = other.N;
    data = new int*[N];
    for (int i = 0; i < N; i++) {
        data[i] = new int[N];
        for (int j = 0; j < N; j++) {
            data[i][j] = other.data[i][j];
        }
    }

    return *this;
}

};
int getSize() const { return N; }

    // Direct access helper
    int get(int r, int c) const { return data[r][c]; }
    void set(int r, int c, int val) { data[r][c] = val; }

    // 1. Display matrix with aligned columns
    void display() const {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                std::cout << std::setw(4) << data[i][j] << " ";
            }
            std::cout << "\n";
        }
    }

    // 2. Matrix Addition Operator
    Matrix operator+(const Matrix& other) const {
        Matrix result(N);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                result.data[i][j] = this->data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    // 3. Matrix Multiplication Operator
    Matrix operator*(const Matrix& other) const {
        Matrix result(N);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                int sum = 0;
                for (int k = 0; k < N; ++k) {
                    sum += this->data[i][k] * other.data[k][j];
                }
                result.data[i][j] = sum;
            }
        }
        return result;
    }

    // 4. Sum of main and secondary diagonal elements
    void sumDiagonals() const {
        int mainSum = 0;
        int secSum = 0;
        for (int i = 0; i < N; ++i) {
            mainSum += data[i][i];
            secSum += data[i][N - 1 - i];
        }
        std::cout << "Main diagonal sum: " << mainSum << "\n";
        std::cout << "Secondary diagonal sum: " << secSum << "\n";
        std::cout << "Total diagonal sum: " << (mainSum + secSum) << "\n";
    }

    // 5. Swap rows (passed by value so original is unchanged)
    static Matrix swapRows(Matrix m, int r1 = 0, int r2 = 1) {
        if (r1 >= 0 && r1 < m.N && r2 >= 0 && r2 < m.N) {
            std::swap(m.data[r1], m.data[r2]);
        } else {
            std::cout << "Invalid row indices.\n";
        }
        return m;
    }

    // 6. Swap columns (passed by value)
    static Matrix swapCols(Matrix m, int c1 = 0, int c2 = 1) {
        if (c1 >= 0 && c1 < m.N && c2 >= 0 && c2 < m.N) {
            for (int i = 0; i < m.N; ++i) {
                std::swap(m.data[i][c1], m.data[i][c2]);
            }
        } else {
            std::cout << "Invalid column indices.\n";
        }
        return m;
    }

    // 7. Update element (passed by value)
    static Matrix updateElement(Matrix m, int r = 0, int c = 0, int val = 100) {
        if (r >= 0 && r < m.N && c >= 0 && c < m.N) {
            m.data[r][c] = val;
        } else {int main() {
    std::string filename;
    std::cout << "Enter the input file name: ";
    std::cin >> filename;

    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Error: Could not open file " << filename << "\n";
        return 1;
    }

    int N;
    if (!(infile >> N) || N <= 0) {
        std::cerr << "Error: Invalid matrix size.\n";
        return 1;
    }

    Matrix A(N);
    Matrix B(N);

    // Read Matrix A
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            int val;
            infile >> val;
            A.set(i, j, val);
        }
    }

    // Read Matrix B
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            int val;
            infile >> val;
            B.set(i, j, val);
        }
    }
    infile.close();

    // 1. Display Matrices
    std::cout << "\n--- Practice 1: Initial Matrices ---\n";
    std::cout << "Matrix A:\n";
    A.display();
    std::cout << "\nMatrix B:\n";
    B.display();

    // 2. Add Matrices
    std::cout << "\n--- Practice 2: Matrix Addition (A + B) ---\n";
    Matrix sum = A + B;
    sum.display();

    // 3. Multiply Matrices
    std::cout << "\n--- Practice 3: Matrix Multiplication (A * B) ---\n";
    Matrix prod = A * B;
    prod.display();

    // 4. Sum of Diagonals
    std::cout << "\n--- Practice 4: Diagonal Sums (Matrix A) ---\n";
    A.sumDiagonals();

    // 5. Swap Rows (Default 0 and 1)
    std::cout << "\n--- Practice 5: Swap Rows (Matrix A, default rows 0 and 1) ---\n";
    Matrix swappedRows = Matrix::swapRows(A);
    swappedRows.display();

    // 6. Swap Columns (Default 0 and 1)
    std::cout << "\n--- Practice 6: Swap Columns (Matrix A, default cols 0 and 1) ---\n";
    Matrix swappedCols = Matrix::swapCols(A);
    swappedCols.display();

    // 7. Update Element (Default: (0, 0) = 100)
    std::cout << "\n--- Practice 7: Update Element (Matrix A, default (0, 0) to 100) ---\n";
    Matrix updated = Matrix::updateElement(A);
    updated.display();

    std::cout << "\nVerify original Matrix A is unchanged:\n";
    A.display();

    return 0;
}
            std::cout << "Invalid indices for update.\n";
        }
        return m;
    }
};
