#ifndef _CSP_H_
#define _CSP_H_

#include "matrix.h"

class csp1d{
private:
    long double stock = 0; // Stock length

    matrix roll_sizes;       // Roll sizes
    matrix demand;           // Cutting demand
    matrix B;                // Cutting patterns
    matrix current_solution; // Current solution
    matrix knapsack(matrix&, matrix&, matrix&, long double&); // Solving knapsack problem
public:
    csp1d(matrix roll_sizes, matrix demand, long double stock = 0){
        if(roll_sizes.return_no_row() != demand.return_no_row() || roll_sizes.return_no_col() != 1 || demand.return_no_col() != 1){
            throw runtime_error("Invalid problem");
        }
        this -> stock      = stock;
        this -> roll_sizes = roll_sizes;
        this -> demand     = demand;
        this -> B          = matrix::unit_matrix(demand.return_no_row());
        this -> current_solution = matrix(vector<vector<long double>>(demand.return_no_row(), vector<long double>(1)));
    }
    
    ~csp1d(){}

    void solve();
    void show_answer();
    void set(long double, matrix, matrix);
};

#endif
