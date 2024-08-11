#include "matrix.h"
#include "csp.h"

int main(){
    matrix demand({{80},{50},{100}});
    // Or we could simply write "matrix demand; demand.set_matrix({{80},{50},{100}});"

    matrix roll({{4},{6},{7}});
    double stock = 15;
    
    csp1d demo(roll, demand, stock);
    demo.solve();
    demo.show_answer();

    return 0;
}
