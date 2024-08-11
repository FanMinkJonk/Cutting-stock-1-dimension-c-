#ifndef _CSP_H_
#define _CSP_H_

#include "matrix.h"

class csp1d{
private:
    int total_roll = 0;      // Amount of roll use

    double stock = 0;        // Stock length
    double waste;            // Total waste

    matrix roll_sizes;       // Roll sizes
    matrix demand;           // Cutting demand
    matrix B;                // Cutting patterns
    matrix current_solution; // Current solution
    matrix knapsack(matrix&, matrix&, matrix&, double&); // Solving knapsack problem
public:
    csp1d(matrix rs, matrix d, double s = 0){
        if(s <= 0)
            throw runtime_error("Invalid stock length!!!");
        if(rs.return_no_col() > 1 || rs.return_no_row() == 0)
            throw runtime_error("Invalid roll cut!!!");
        if(d.return_no_col() > 1 || d.return_no_row() == 0)
            throw runtime_error("Invalid demand!!!");
        this -> stock      = s;
        this -> roll_sizes = rs;
        this -> demand     = d;
        this -> B          = matrix::unit_matrix(demand.return_no_row());
        this -> current_solution = matrix(vector<vector<long double>>(demand.return_no_row(), vector<long double>(1)));    
        this -> total_roll = 0;
        this -> waste      = 0.0;
        cout << "Case received:\n";
        cout << "Stock:" << stock << endl;
        cout << "Demand:\n";
        this -> demand.show_matrix();
        cout << "Cut size requirement\n";
        this -> roll_sizes.show_matrix();
    }
    
    ~csp1d(){}

    void solve();                     // Solve the problem
    void show_answer();               // Output the result
    void set(matrix, matrix, double); // Set up problem
    
    double get_stock(); // Return stock value
    double get_waste(); // Return waste value

    int get_total_roll(); // Return amount of stock needed

    matrix get_roll_sizes();       // Return required roll sizes vector
    matrix get_demand();           // Return demand vector
    matrix get_base();             // Return cut pattern matrix
    matrix get_current_solution(); // Return current solution vector
};

#endif
