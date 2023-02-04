#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <iostream>
#include "ValidOperation.hpp"

class Matrix {

    private: 
        // Dynamic arrays to store variable length matrices
        int** value = 0;
        int r;
        int c;

    public:

        void input(std::vector< std::vector<int> >& A, 
            int _r, int _c);
        void display();
        
        Matrix operator+(Matrix x);
        Matrix operator*(Matrix x);
};

#endif
