#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "main.h"

class matrix{
private:
    /*----- Integer Variables -----*/
    int dimension_row = 0,
        dimension_col = 0;
    
    /*----- Vector Variables -----*/
    vector<vector<long double>> m;

    /*----- Recursive Call -----*/
    double det(vector<vector<long double>>);      // Return matrix's determinant(Recursive call)
public:
    matrix(int no_row = 3, int no_col = 3){
        this -> dimension_row = no_row;
        this -> dimension_col = no_col;
        for(int i = 0; i < dimension_row; ++i){
            this -> m.push_back(vector<long double>(this -> dimension_col));
        }
    }
    matrix(vector<vector<long double>> v){
        this -> m = v;
        this -> dimension_row = v.size();
        this -> dimension_col = v.size()==0? 0 : v[0].size();
    }
    ~matrix(){
        m.clear();
    }

    void set_matrix(vector<vector<long double>>); // Set matrix
    void show_matrix();                           // Print matrix
    void remove_row(int, int);                    // Remove desire row
    void remove_col(int, int);                    // Remove desire collumn
    void set_element(int, int, long double);      // Set element

    int return_no_row(); // Return number of row
    int return_no_col(); // Return number of col

    double get_element(int, int); // Return element on row i and collumn j
    double det();                 // Return matrix's determinant

    matrix transpose();                   // Return matrix's transposal
    matrix getCofactor();                 // Return matrix's cofactor
    matrix inverse();                     // Return matrix's inversion
    matrix submatrix(int, int, int, int); // Return matrix's submatrix
    static matrix unit_matrix(int);       // Return unit matrix

    matrix& operator=(const matrix&);     // Matrix's assignment
    matrix operator+(const matrix&);      // Matrix's addition
    matrix operator*(const matrix&);      // Matrix's multiplication(Matrix x Matrix)
    matrix operator*(const long double&); // Matrix's multiplication(Matrix x number)

};

#endif

//----- This library was made by fanminkjonk(HCMUT), feel free to use, fix, adjust,... whatever you want, but make sure to give me some credit, I'll be appreciated ;) -----//
