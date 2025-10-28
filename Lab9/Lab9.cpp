/*
Program Name: EECS 348 Lab 9
Description: Functions with matrices in C++
Inputs: a single .txt file which contains both square matrices and their sizes
Outputs: various functions to add, multiply, swap, and modify the matrices in C++.
Collaborators: 
Other Sources: stackOverflow, ChatGPT, geeksforgeeks
Author: Warren Tan
Creation Date: 28/10/2025
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream> // stringstream
#include <iomanip> // setw and setfill

using namespace std;

// checks if the given string is an empty string (including new lines, spaces, etc.)
// function from ChatGPT
bool isBlank(const string& s) {
    // checks every character in the string
    for (char c : s)
        // if any character is not whitespace, the string is not blank.
        if (!isspace(static_cast<unsigned char>(c)))
            return false;
    // the string is blank
    return true;
}

// returns the maximum value from the matrix
int maxMatrix(const vector<vector<int>>& matrix){
    int maxValue = matrix[0][0];
    for(size_t i = 0; i < matrix.size(); ++i){
        for(size_t j = 0; j < matrix[i].size(); ++j){
            if(matrix[i][j] > maxValue){
                maxValue = matrix[i][j];
            }
        }
    }
    return maxValue;
}

// prints the matrix with proper formatting
void printMatrix(const vector<vector<int>>& matrix){
    // find the maximum value of the matrix
    int maxValue = maxMatrix(matrix);

    // find the maximum width of the matrix
    int maxWidth = to_string(maxValue).length();

    for(size_t i = 0; i < matrix.size(); ++i){
        for(size_t j = 0; j < matrix[i].size(); ++j){
            // setw determines the desired width of the string
            // setfill fills the space with zero until the width length is met
            // setw and setfill from ChatGPT
            cout << setw(maxWidth) << setfill('0') << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

// adds two matrices together, then returns the resulting matrix
vector<vector<int>> addMatrices(const vector<vector<int>>& matrix1, const vector<vector<int>>& matrix2){
    vector<vector<int>> addedMatrix;
    
    for(size_t i = 0; i < matrix1.size(); ++i){
        vector<int> row;
        for(size_t j = 0; j < matrix1[i].size(); ++j){
            row.push_back(matrix1[i][j] + matrix2[i][j]);
        }
        addedMatrix.push_back(row);
    }

    return addedMatrix;
}

// gets the result for an individual, matrix-multiplied cell
// used by multiplyMatrices
int getCell(const vector<vector<int>>& matrix1, const vector<vector<int>>& matrix2, size_t r, size_t c){
    // the number stored in the cell to be returned
    int cell = 0;
    
    // i is a counter
    // matrix1 counts down the row, while matrix2 counts down the column
    for(size_t i = 0; i < matrix1.size(); ++i){
        cell += matrix1[r][i] * matrix2[i][c];
    }

    return cell;
}

// multiplies two matrices together, then returns the resulting matrix
vector<vector<int>> multiplyMatrices(const vector<vector<int>>& matrix1, const vector<vector<int>>& matrix2){
    vector<vector<int>> multipliedMatrix;
    
    for(size_t i = 0; i < matrix1.size(); ++i){
        vector<int> row;
        for(size_t j = 0; j < matrix1[i].size(); ++j){
            row.push_back(getCell(matrix1, matrix2, i, j));
        }
        multipliedMatrix.push_back(row);
    }

    return multipliedMatrix;
}

// returns the sum of both diagonals in a square matrix
int diagonalSumMatrix(const vector<vector<int>>& matrix){
    int sum = 0;

    // sum diagonals
    for(int i = 0; i < matrix.size(); ++i){
        // add main diagonal
        sum += matrix[i][i];

        // add secondary diagonal
        sum += matrix[matrix.size() - i - 1][i];
    }
    
    // remove double-summing the middle element in odd matrix sizes
    if(matrix.size() % 2 == 1){
        int middle = matrix.size() / 2;
        sum -= matrix[middle][middle];
    }

    return sum;
}

// swaps two rows, if valid
vector<vector<int>> swapMatrixRows(const vector<vector<int>>& matrix, size_t row1, size_t row2){
    // rows are not valid. throw error and return an empty matrix.
    if(row1 >= matrix.size() || row2 >= matrix.size()){
        cerr << "Error: Invalid row indices." << endl;
        return {};
    }

    // create a new matrix using the preexisting matrix
    vector<vector<int>> swappedMatrix = matrix;

    // swap rows
    // swap from ChatGPT
    swap(swappedMatrix[row1], swappedMatrix[row2]);

    return swappedMatrix;
}

// swaps two columns, if valid
vector<vector<int>> swapMatrixCols(const vector<vector<int>>& matrix, size_t col1, size_t col2){
    // columns are not valid. throw error and return an empty matrix.
    if(col1 >= matrix[0].size() || col2 >= matrix[0].size()){
        cerr << "Error: Invalid column indices." << endl;
        return {};
    }

    // create a new matrix using the preexisting matrix
    vector<vector<int>> swappedMatrix = matrix;

    // swap columns
    for(size_t i = 0; i < matrix.size(); ++i){
        // swap from ChatGPT
        swap(swappedMatrix[i][col1], swappedMatrix[i][col2]);
    }

    return swappedMatrix;
}

// updates a cell in the matrix with the given integer
void updateMatrix(vector<vector<int>>& matrix, size_t row, size_t col, int num){
    // indices are not valid. throw error and return an empty matrix.
    if(row >= matrix.size() || col >= matrix[0].size()){
        cerr << "Error: Invalid indices." << endl;
        return;
    }

    matrix[row][col] = num;

    printMatrix(matrix);
}

int main(){
    // get user input
    string fileName;
    cout << "Name of file: ";
    cin >> fileName;

    // fileName = "input.txt";
    
    // attempt to open the file in parameter 'fin'
    // ifstream from ChatGPT
    ifstream fin(fileName);
    if (!fin) {
        cerr << "Error opening file." << endl;
        return 1;
    }
    
    // string to temporarily store each line from the file
    string line;
    
    // contains the size of the matrices
    size_t size;
    
    // first row contains the matrix size
    getline(fin, line);
    
    // converts input into integer tokens
    // stringstream from geeksforgeeks
    stringstream ss(line);

    // store size_t token in size
    ss >> size;

    // vectors from stackOverflow
    vector<vector<int>> matrix1;
    vector<vector<int>> matrix2;

    // counts the file's row
    size_t fileRow = -1;
    // passes through every line in file
    while(getline(fin, line)){
        // skips empty lines
        if(isBlank(line)){
            continue;
        }

        ++fileRow;
        stringstream ss(line);

        // stores the currently read row/number
        vector<int> row;
        int num;
        
        // fill row with every number from the line
        while(ss >> num){
            row.push_back(num);
        }

        // the first 'size' lines are from matrix1, the second are from matrix2
        if(fileRow < size){
            matrix1.push_back(row);
        }else if(size <= fileRow && fileRow < size * 2){
            matrix2.push_back(row);
        }
    }

    cout << "matrix1: " << endl;
    printMatrix(matrix1);
    cout << endl;

    cout << "matrix2: " << endl;
    printMatrix(matrix2);
    cout << endl;

    cout << "added matrices: " << endl;
    printMatrix(addMatrices(matrix1, matrix2));
    cout << endl;

    cout << "multiplied matrices: " << endl;
    printMatrix(multiplyMatrices(matrix1, matrix2));
    cout << endl;

    cout << "diagonal sum (matrix1): " << endl;
    cout << diagonalSumMatrix(matrix1) << endl;
    cout << endl;

    cout << "swapped matrix (rows 2 and 3): " << endl;
    printMatrix(swapMatrixRows(matrix1, 2, 3));
    cout << endl;

    cout << "swapped matrix (cols 2 and 3): " << endl;
    printMatrix(swapMatrixCols(matrix1, 2, 3));
    cout << endl;

    cout << "updated matrix (replace (2, 3) with '40'): " << endl;
    updateMatrix(matrix1, 2, 3, 40);
    cout << endl;

    return 0;
}