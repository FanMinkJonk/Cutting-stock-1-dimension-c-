This code was made by CO2011, DT01, Team 5 (Semester 3, 2023-2024)
Instruction:
     Step 1: Use matrixes to build test cases, for example "matrix demo({{80},{50},{100}});" indicates this is a vector.
     Step 2: Create a variable of type "csp1d", for example "csp1d demo_problem;".
     Step 3: Load the problem using "csp1d::set(matrix, matrix, double)" method, for example "demo_problem.set(roll_sizes, demand, stock);".
	Note: everything must be in order
	- roll_sizes: is the size of required cut length
	- demand: is the amount of rolls needed according to roll_sizes
	- stock: is the length of the stock
     Step 4: Use "csp1d::solve()" to solve the problem, for example "demo_problem.solve();"
     Step 5: Use "csp1d::show_answer()" to show the result, for example "demo_problem.show_answer();"

Built in methods:
class csp1d{
public:
     void solve(); 		       // Solve the problem
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

Reference: https://www.researchgate.net/publication/349425538_Modified_Greedy_Heuristic_for_the_one-dimensional_cutting_stock_problem
