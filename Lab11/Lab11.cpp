/*
Program Name: EECS 348 Lab 11
Description: Functions with matrices in C++
Inputs: a single .txt file which contains both square matrices and their sizes
Outputs: various functions to add, multiply, swap, and modify the matrices in C++.
Collaborators: 
Other Sources: ChatGPT, geeksforgeeks
Author: Warren Tan
Creation Date: 05/11/2025
*/

#include <iostream> // console printing/user input
#include <fstream> // file input
#include <string> // string class
#include <sstream> // split strings for processing
#include <iomanip> // setw and setfill

// brings the std functions, classes, variables, etc. into the current scope
using namespace std;

class Matrix {
    private:
        // the size of the matrix
        int size;

        // the data for the matrix
        int** data;

        // checks if the given string is an empty string (including new lines, spaces, etc.)
        // helper function for setMatrix
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
        // helper function for printMatrix
        int maxMatrix(){
            int maxValue = data[0][0];
            for(size_t i = 0; i < size; ++i){
                for(size_t j = 0; j < size; ++j){
                    if(data[i][j] > maxValue){
                        maxValue = data[i][j];
                    }
                }
            }
            return maxValue;
        }

        // gets the result for an individual, matrix-multiplied cell
        // helper function for multiplyMatrices
        int getMultipliedCell(const Matrix& matrix1, const Matrix& matrix2, size_t row, size_t col){
            // the number stored in the cell to be returned
            int cell = 0;
            
            // i is a counter
            // matrix1 counts down the row, while matrix2 counts down the column
            for(size_t i = 0; i < matrix1.size; ++i){
                cell += matrix1.data[row][i] * matrix2.data[i][col];
            }

            return cell;
        }

    public:
        // constructor
        Matrix(int n){
            // store the size of the matrix
            size = n;

            // reserve space for data
            data = new int*[size];
            for(int i = 0; i < size; ++i){
                data[i] = new int[size];
            }
        }

        // destructor
        ~Matrix(){
            // delete row data
            for(int i = 0; i < size; ++i){
                delete[] data[i];
            }
            // delete the row
            delete[] data;
        }

        // Copy constructor (deep copy)
        // function declaration from geeksforgeeks
        Matrix(const Matrix& other) {
            // obtain the size of the matrix to copy
            size = other.size;
            
            // reserve space for data to be deep copied
            data = new int*[size];

            // copy the rows
            for (int i = 0; i < size; ++i) {
                // reserve space for columns in the row to be deep copied
                data[i] = new int[size];
                
                // copy the data
                for (int j = 0; j < size; ++j) {
                    data[i][j] = other.data[i][j];
                }
            }
        }

        // size getter
        int getSize(){
            return size;
        }

        // data getter
        int getValue(int row, int col){
            if(row < 0 || size <= row || col < 0 || size <= col){
                // throw an out of range error
                // out_of_range from ChatGPT
                throw out_of_range("Invalid index");
            }
            return data[row][col];
        }

        // sets the matrix using a file input
        void setMatrix(ifstream& fin){
            // string to temporarily store each line from the file
            string line;

            // keeps track of the current position in the matrix
            int rowNum = 0;
            int colNum = 0;

            // get lines from the file and store it in 'line'
            // ensure that the input only reads the current matrix's lines by limiting the row
            while(rowNum < size && getline(fin, line)){
                // check if the file row is blank, if so, skip it
                if(isBlank(line)){
                    continue;
                }
                
                // reset colNum's count
                colNum = 0;
                
                // converts input into integer tokens
                istringstream ss(line);

                // stores the currently read number
                int num;

                // fill row with every number from the line
                while(ss >> num){
                    // store data in the matrix
                    data[rowNum][colNum] = num;
                    
                    // increment colNum for next iteration
                    ++colNum;
                }

                ++rowNum;
            }
        }

        // prints the matrix with proper formatting
        void printMatrix(){
            // find the maximum value of the matrix
            int maxValue = maxMatrix();

            // find the maximum width of any value in the matrix
            int maxWidth = to_string(maxValue).length();

            // print matrix values
            for(size_t i = 0; i < size; ++i){
                for(size_t j = 0; j < size; ++j){
                    // setw determines the desired width of the string
                    // setfill fills the space with zero until the width length is met
                    // setw and setfill from ChatGPT
                    cout << setw(maxWidth) << setfill('0') << data[i][j] << " ";
                }
                cout << endl;
            }
        }

        // adds two matrices together, then returns the resulting matrix
        Matrix operator+(Matrix& other){
            Matrix addedMatrix(getSize());
            
            for(size_t i = 0; i < addedMatrix.size; ++i){
                for(size_t j = 0; j < addedMatrix.size; ++j){
                    addedMatrix.updateMatrix(i, j, getValue(i, j) + other.getValue(i, j), false);
                }
            }

            addedMatrix.printMatrix();

            return addedMatrix;
        }

        // multiplies two matrices together, then returns the resulting matrix
        Matrix operator*(Matrix& other){
            Matrix multipliedMatrix(getSize());
            
            for(size_t i = 0; i < multipliedMatrix.getSize(); ++i){
                for(size_t j = 0; j < multipliedMatrix.getSize(); ++j){
                    multipliedMatrix.updateMatrix(i, j, getMultipliedCell(*this, other, i, j), false);
                }
            }

            multipliedMatrix.printMatrix();

            return multipliedMatrix;
        }

        // returns the sum of both diagonals in a square matrix
        int diagonalSumMatrix(){
            int sum = 0;

            // sum diagonals
            for(int i = 0; i < size; ++i){
                // add main diagonal
                sum += getValue(i, i);

                // add secondary diagonal
                sum += getValue(size - i - 1, i);
            }
            
            // remove double-summing the middle element in odd matrix sizes
            if(size % 2 == 1){
                int middle = size / 2;
                sum -= getValue(middle, middle);
            }

            return sum;
        }

        // swaps two rows, if valid
        static void swapMatrixRows(Matrix swappedMatrix, int row1=0, int row2=1){
            // rows are not valid. throw error and return an empty matrix.
            if(row1 < 0 || swappedMatrix.getSize() <= row1 || row2 < 0 || swappedMatrix.getSize() <= row2){
                cerr << "Error: Invalid row indices." << endl;
                return;
            }

            // swap rows of the matrix
            for(int j = 0; j < swappedMatrix.getSize(); ++j){
                // store row1, so no data gets lost
                int tempVal = swappedMatrix.getValue(row1, j);

                // assign row2 cell to row1
                swappedMatrix.updateMatrix(row1, j, swappedMatrix.getValue(row2, j), false);

                // assign the temporary value to row2
                swappedMatrix.updateMatrix(row2, j, tempVal, false);
            }

            swappedMatrix.printMatrix();
        }

        // swaps two cols, if valid
        static void swapMatrixCols(Matrix swappedMatrix, int col1=0, int col2=1){
            // cols are not valid. throw error and return an empty matrix.
            if(col1 < 0 || swappedMatrix.getSize() <= col1 || col2 < 0 || swappedMatrix.getSize() <= col2){
                cerr << "Error: Invalid col indices." << endl;
                return;
            }

            // swap cols of the matrix
            for(int i = 0; i < swappedMatrix.getSize(); ++i){
                // store col1, so no data gets lost
                int tempVal = swappedMatrix.getValue(i, col1);

                // assign col2 cell to col1
                swappedMatrix.updateMatrix(i, col1, swappedMatrix.getValue(i, col2), false);

                // assign the temporary value to col2
                swappedMatrix.updateMatrix(i, col2, tempVal, false);
            }

            swappedMatrix.printMatrix();
        }

        // updates a cell in the matrix with the given integer
        void updateMatrix(size_t row=0, size_t col=0, int num=100, bool print=true){
            // indices are not valid. throw error and return an empty matrix.
            if(row >= size || col >= size){
                cout << "Error: Invalid indices." << endl;
                return;
            }

            this->data[row][col] = num;

            if(print)
                printMatrix();
        }
};

// reads file and produces outputs based on file contents
void processFile(const string& inputFile){

    // print name of file
    cout << inputFile << endl;

    // attempt to open the file in variable 'fin'
    // ifstream from ChatGPT
    ifstream fin(inputFile);
    if (!fin) {
        cerr << "Error opening file." << endl;
        return;
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
    
    // initialize two matrices with same size
    Matrix matrix1(size);
    Matrix matrix2(size);

    // store data in the matrix from the file input
    matrix1.setMatrix(fin);
    matrix2.setMatrix(fin);

    // 
    cout << "matrix1: " << endl;
    matrix1.printMatrix();
    cout << endl;

    cout << "matrix2: " << endl;
    matrix2.printMatrix();
    cout << endl;

    cout << "added matrices: " << endl;
    matrix1 + matrix2;
    cout << endl;

    cout << "multiplied matrices: " << endl;
    matrix1 * matrix2;
    cout << endl;

    cout << "diagonal sum (matrix1): " << endl;
    cout << matrix1.diagonalSumMatrix() << endl;
    cout << endl;

    cout << "row-swapped matrix (default: rows 0 and 1): " << endl;
    Matrix::swapMatrixRows(matrix1);
    cout << endl;

    cout << "col-swapped matrix (default: cols 0 and 1): " << endl;
    Matrix colSwapped(size);
    Matrix::swapMatrixCols(matrix1);
    cout << endl;

    cout << "updated matrix (default: replace(0, 0) with '100'): " << endl;
    matrix1.updateMatrix();
    cout << endl;
}


int main(){
    // get user input
    string fileName;
    cout << "Name of file: ";
    cin >> fileName;
    
    // process file
    processFile(fileName);
    
    return 0;
}