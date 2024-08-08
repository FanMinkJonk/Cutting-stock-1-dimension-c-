#include "matrix.h"
#include "csp.h"

int main(){
    matrix demand({{7},{9},{4}});
    matrix roll({{11},{5},{3}});
    int stock = 17;
    
    cout << "Building case\n";
    csp1d demo(roll, demand, stock);
    cout << "Case received:\n";
    cout << "Stock:" << stock << endl;
    cout << "Demand:\n";
    demand.show_matrix();
    cout << "Cut size requirement\n";
    roll.show_matrix();
    cout << "Solving problem...\n";
    demo.solve();
    cout << "Finished solving problem\n";
    cout << "Answer:\n";
    demo.show_answer();

    return 0;
}