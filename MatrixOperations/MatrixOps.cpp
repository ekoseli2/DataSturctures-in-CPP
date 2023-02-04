#include "Matrix.hpp"

// Input the elements of first matrix into arr

using namespace std;

void Matrix::input(vector<vector<int> >& A, int _r, int _c) {

    // With the dimensions defined, now add them to the class definitions
    r = _r;
    c = _c;
    // Create first row of pointers
    value = (int**)malloc(r * sizeof(int*));
    for(int i = 0; i < r; i++) {
        // Now allocate each new row into the array
        value[i] = (int*)malloc(c * sizeof(int));
    }

    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
            value[i][j] = A[i][j];
        }
    }
}

void Matrix::display() {
    if(value != NULL) {
        for(int i = 0; i < r; i++) {
            for(int j = 0; j < c; j++) {

                cout << value[i][j] << ' ';
            }
            cout << endl;
        }
    }
}

// Function to check if the operation is possible with addition
bool ValidOperation::CheckAdd(int row1, int col1, int row2, int col2) {
   
    if( (row1 == row2) && (col1 == col2) ){
        return true;
    }
    else {
        return false;
    }

}

// Function definition to check in the operation is possible with mult
bool ValidOperation::CheckMult(int col1, int row2) {

    if(col1 == row2) {
        return true;
    }
    else {
        return false;
    }
}

// Add the first matrix to the second
Matrix Matrix::operator+(Matrix x) {
    // DECLARE A NEW OBJECT result matrix 
    Matrix result;

    if( ValidOperation::CheckAdd(r, c, x.r, x.c) == true ) {
        result.r = r;
        result.c = c;
        
        // Create the array for result matrix
        result.value = (int**)malloc(r * sizeof(int*));
        for(int i = 0; i < result.r; i++) {
        // Now allocate each new row into the array
            result.value[i] = (int*)malloc(result.c * sizeof(int));
        }

        // Arithmetic starts here
        for(int i = 0; i < r; i++) {
            for(int j = 0; j < c; j++) {
                // Add the matrix element to the equivalent index
                // and store inside the result matrix
                result.value[i][j] = this->value[i][j] + x.value[i][j];
            }
        }
        return result;
    }

    else {
        cout << "Invalid Operation" << endl;
        return;
    }
}


Matrix Matrix::operator*(Matrix x) {

    Matrix result;

    if( ValidOperation::CheckMult(c, x.r) == true ) 
    {
        // result matrix
        result.r = r;
        result.c = x.c;

        // Create the array for result matrix
        result.value = (int**)malloc(r * sizeof(int*));
        for(int i = 0; i < result.r; i++) {
        // Now allocate each new row into the array
            result.value[i] = (int*)malloc(result.c * sizeof(int));
        }

        // Arithmetic starts here
        for(int i = 0; i < r; i++) 
        {
            for(int j = 0; j < x.c; j++) 
            {
                // Current position must be initialized to 0 before adding
                // subsequent elements in summation
                result.value[i][j] = 0;

                for(int k = 0; k < x.r; k++) {
                    result.value[i][j] += 
                    ( (this->value[i][k]) * (x.value[k][j]) );
                }
            }
        }
        return result;
    }

    else {
        cout << "Invalid Operation" << endl;
        return;
    }
}
