#include <iostream>  // Includes the iostream library for input and output operations (e.g., cout, cin).
#include <vector>    // Includes the vector library for using the std::vector class for dynamic arrays.
#include <fstream>   // Includes the fstream library for reading from and writing to files.
using namespace std; // Allows the use of standard namespace elements without prefixing them with 'std::'.

// Class definition for Matrix to handle matrix operations.
class Matrix {
private:
    vector<vector<int> > data; // A 2D vector to store matrix data.
    int size;                 // The size of the matrix (assumed to be square).

public:
    // Constructor that initializes the matrix size and resizes the data vector to create an n x n matrix.
    Matrix(int n) : size(n) {
        data.resize(n, vector<int>(n)); // Resizes the 2D vector to n x n with all elements initialized to 0.
    }

    // Function to load matrix data from a file and store it in the data vector.
    void LoadFromFile(const string& filename) {
        ifstream file(filename); // Opens the file for reading.
        if (!file) {             // Checks if the file was successfully opened.
            cerr << "Error: Unable to open file." << endl; // Outputs an error message if the file cannot be opened.
            exit(1);             // Exits the program with a non-zero status to indicate an error.
        }
        for (int i = 0; i < size; ++i) {         // Loops through each row. It will start from the first row and will keep running as long as i is less than the matrix size. Then increments by 1 after each iteration    
            for (int j = 0; j < size; ++j) {     // Loops through each column in the row. starts from beginning, keep running as long as as i less than matrix size, increments by 1
                file >> data[i][j];             // Reads an integer from the file and stores it in the matrix.
            }
        }
        file.close(); // Closes the file after reading.
    }

    // Function to display the matrix in a user-friendly format.
    void display() const {
        for (const auto& row : data) {        // Iterates through each row in the matrix. It first ensures that each row is accessed as a read-only reference and then loops over the data vector  
            for (int val : row) {             // Iterates through each value/element in the row.
                cout << val << " ";           // Prints the element followed by a space just for a neater output 
            }
            cout << endl;                     // Moves to the next line after printing a row.
        }
    }

    // Overloads the + operator to add two matrices and return the result as a new matrix.
    Matrix operator+(const Matrix& other) const {
        Matrix result(size); // Creates a new matrix object to store the result.
        for (int i = 0; i < size; ++i) {      // Loops through each row.
            for (int j = 0; j < size; ++j) {  // Loops through each column.
                result.data[i][j] = data[i][j] + other.data[i][j]; // Adds corresponding elements from both matrices.
            }
        }
        return result; // Returns the resulting matrix.
    }

    // Overloads the * operator to multiply two matrices and return the result as a new matrix.
    Matrix operator*(const Matrix& other) const {
        Matrix result(size); // Creates a new matrix to store the product.
        for (int i = 0; i < size; ++i) {       // Loops through each row.
            for (int j = 0; j < size; ++j) {   // Loops through each column.
                result.data[i][j] = 0;        // Initializes the element to 0.
                for (int k = 0; k < size; ++k) { // Loops through each element for the dot product.
                    result.data[i][j] += data[i][k] * other.data[k][j]; // Multiplies and adds the results.
                }
            }
        }
        return result; // Returns the resulting matrix.
    }

    // Function to calculate and return the sum of the main and secondary diagonals.
    int sumDiagonals() const {
        int mainDiagonalSum = 0, secondaryDiagonalSum = 0; // Initializes sums for both diagonals.
        for (int i = 0; i < size; ++i) {                   // Loops through each row.
            mainDiagonalSum += data[i][i];                 // Adds the main diagonal element.
            secondaryDiagonalSum += data[i][size - i - 1]; // Adds the secondary diagonal element.
        }
        return mainDiagonalSum + secondaryDiagonalSum;     // Returns the total sum.
    }

    // Function to swap two rows in the matrix if the indices are valid.
    void swapRows(int row1, int row2) {
        if (row1 >= 0 && row1 < size && row2 >= 0 && row2 < size) { // Checks if the row indices are within bounds.
            swap(data[row1], data[row2]); // Swaps the rows using the built-in swap function.
        } else {
            cerr << "Error: Invalid row indices." << endl; // Outputs an error if the indices are invalid.
        }
    }
};

int main() {
    int n; // Variable to store matrix size.
    cout << "Enter the size of the matrix (n): ";
    cin >> n; // Reads matrix size from user input.
    Matrix matrix1(n), matrix2(n); // Creates two Matrix objects with the specified size.

    // Loads matrix data from files.
    cout << "Loading matrix data from 'matrix-data.txt'..." << endl;
    matrix1.LoadFromFile("matrix-data.txt"); // Loads data into the first matrix.
    matrix2.LoadFromFile("matrix-data.txt"); // Loads data into the second matrix for demonstration.

    // Displays the original matrices.
    cout << "Matrix 1:" << endl;
    matrix1.display(); // Prints the first matrix.
    cout << "Matrix 2:" << endl;
    matrix2.display(); // Prints the second matrix.

    // Performs matrix addition and displays the result.
    Matrix sumMatrix = matrix1 + matrix2; // Adds the matrices.
    cout << "Sum of matrices:" << endl;
    sumMatrix.display(); // Prints the sum matrix.

    // Performs matrix multiplication and displays the result.
    Matrix productMatrix = matrix1 * matrix2; // Multiplies the matrices.
    cout << "Product of matrices:" << endl;
    productMatrix.display(); // Prints the product matrix.

    // Calculates and displays the sum of the diagonal elements.
    cout << "Sum of diagonal elements in Matrix 1: " << matrix1.sumDiagonals() << endl;

    // Prompts the user for row indices to swap and displays the modified matrix.
    int row1, row2;
    cout << "Enter two row indices to swap (0-based): ";
    cin >> row1 >> row2; // Reads the row indices from user input.
    matrix1.swapRows(row1, row2); // Swaps the specified rows.
    cout << "Matrix 1 after swapping row " << row1 << " and row " << row2 << ":" << endl;
    matrix1.display(); // Prints the matrix after swapping.

    return 0; // Indicates successful program termination.
}
