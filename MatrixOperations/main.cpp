#include "Matrix.hpp"
#include <fstream>

using namespace std;

int main() {
    // Vectors to hold the values of the matrices
    vector<vector<int> > matrix_vals1;
    vector<vector<int> > matrix_vals2;
    // Dimensions to copy into the matrix class
    int M, N1, N2, P;
    ifstream mat1, mat2;
    // Take the fileName to use from user that will represent matrix 1
    string fileName1;
    while (fileName1.empty()) {
        cout << "Enter file name: ";
        char c[255];
        cin.getline(c, 255);
        fileName1 = string(c);
    }
    mat1.open(fileName1);
    // Read the User files
    mat1 >> M >> N1;
    cout << "Dimensions: [" << M << " * " << N1 << ']' << endl;
    for(int i = 0; i < M; i++) {
        vector<int> temp;
        for(int j = 0; j < N1; j++) {
            int val;
            mat1 >> val;
            cout << val << ' ';
            temp.push_back(val);
        }
        matrix_vals1.push_back(temp);
        cout << endl;
    }
    // Read the second file to the second matrix value vector
    cout << endl;
    string fileName2;
    while (fileName2.empty()) 
    {
        cout << "Enter file name: ";
        char c[255];
        cin.getline(c, 255);
        fileName2 = string(c);
    }
    mat2.open(fileName2);
    // Read the User files
    mat2 >> N2 >> P;
    cout << "Dimensions: [" << N2 << " * " << P << ']' << endl;
    for(int i = 0; i < N2; i++) {
        vector<int> temp;
        for(int j = 0; j < P; j++) {
            int val;
            mat2 >> val;
            cout << val << ' ';
            temp.push_back(val);
        }
        matrix_vals2.push_back(temp);
        cout << endl;
    }

    // Input Matrices
    Matrix matrix1, matrix2, add_matrix, mult_matrix;
    matrix1.input(matrix_vals1, M, N1);
    matrix2.input(matrix_vals2, N2, P);

    cout << endl << "Adding the matrices: " << endl;
    add_matrix = matrix1 + matrix2;
    add_matrix.display();

    cout << endl << "Multiplying the matrices: " << endl << endl;
    mult_matrix = matrix1 * matrix2;
    mult_matrix.display();

    return 0;
}
