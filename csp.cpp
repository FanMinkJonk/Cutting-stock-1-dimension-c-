#include "csp.h"

template <class T1, class T2>
bool cmp(pair<T1, T2> a, pair<T1, T2> b) {
    return a.second > b.second;
}

matrix csp1d::knapsack(matrix& v, matrix& l, matrix& d, double& L) {
    int n = v.return_no_row();

    vector<pair<int, long double>> pi(n);
    for(int i = 0; i < n; i++) {
        pi[i].first = i;
        pi[i].second = v.get_element(i, 0) * 1.0 / l.get_element(i, 0);
    }
    sort(pi.begin(), pi.end(), cmp<int, long double>);
    
    pi.push_back({n + 1, 0}); // phan tu sau phan tu cuoi

    vector<pair<int, int>> y(n);
    vector<vector<long double>> bestSolution(n, vector<long double>(1, 0));
    
    int remainingLength = L;
    long double maxValue = 0;
    int currentType = -1;
    bool P2 = true;
    
    while (true) {  
        if(P2) {
            for(int i = currentType + 1; i < n; i++) {
                int index = pi[i].first;
                y[i].first = index;
                int yi = min(remainingLength / (int)l.get_element(index, 0), (int)d.get_element(index, 0));
                y[i].second = yi;
                remainingLength -= l.get_element(index, 0) * yi;
            }  
            currentType = n - 1;
        }

        long double currentValue = 0;
        for (int i = 0; i <= currentType; i++) {
            int index = y[i].first;
            currentValue += v.get_element(index, 0) * y[i].second;
        }

        if (currentValue > maxValue)  {
            maxValue = currentValue;
            for(int i = 0; i < n; i++) {
                int index = y[i].first;
                bestSolution[index][0] = y[i].second;
            }
        }

        int k;
        for (k = currentType; k >= 0; k--) {
            if (y[k].second != 0) break;
        }
        currentType = k;

        if (currentType < 0) break;

        long double upperBound = currentValue 
                            -  v.get_element(y[k].first, 0)
                                + pi[k + 1].second * (remainingLength + l.get_element(y[k].first, 0));


        if (upperBound <= maxValue) {
            remainingLength += l.get_element(y[k].first, 0) * y[k].second;
            y[k].second = 0;
            currentType--;
            P2 = false;
        }
        else {
            remainingLength += l.get_element(y[k].first, 0);
            y[k].second -= 1;
            P2 = true;
        }
    }

    return matrix(bestSolution);
}

void csp1d::solve(){
    cout << "Solving problem\n";
    bool STOP = false;

    while(!STOP){
        matrix B_inverse = B.inverse();                                               // Invert matrix B
        matrix piT = matrix({vector<long double>((this -> demand).return_no_row(), 1)}) * B_inverse; // pi = cT.(B^-1)
        current_solution = B_inverse * (this -> demand);                                              // xB = (B^-1).d

        // The big problem :p
        matrix coef = piT.transpose();
        matrix a = this -> knapsack(coef, this -> roll_sizes, this -> demand, this -> stock);
        // End of big problem :p

        int l = -1;
        if(1 - (piT*a).get_element(0,0) >= 0){
            STOP = true;
        }
        else{
            matrix y = B_inverse*a;
            int count = 0;
            long double min = -1;
            for(int i = 0; i < y.return_no_row(); ++i){
                if(y.get_element(i,0) < 0){
                    count = count + 1;
                    if(count == y.return_no_row()){
                        STOP = false;
                        throw runtime_error( "The solution is unlimited");
                    }
                    continue;
                }
                else if(y.get_element(i,0) > 0){
                    if(min == -1 || min > (current_solution.get_element(i,0)/y.get_element(i,0))){
                        min = (current_solution.get_element(i,0)/y.get_element(i,0));
                        l = i;
                    }
                    continue;
                }
            }
        }
        if(l!=-1)
            for(int i = 0; i < B.return_no_row(); ++i){
                B.set_element(i, l, a.get_element(i,0));
            }
    }
    cout << "Problem solved!\n";
}

void csp1d::show_answer(){
    cout << "The variable matrix:\n";
    current_solution.show_matrix();
    cout << "The pattern matrix:\n";
    B.show_matrix();
    cout << "So we have to cut based on the following pattern to minimize waste:\n";
    for(int i = 0; i<B.return_no_col(); ++i){
        cout << ceil(current_solution.get_element(i,0)) << (ceil(current_solution.get_element(i,0))<=1?" plank of: ":" planks of: ");
        for(int j = 0; j<B.return_no_row(); ++j){
            cout << B.get_element(j,i) << "(" << this -> roll_sizes.get_element(j,0) << ")" << ((j==B.return_no_row()-1)?"\n":" ");
        }
    }
    cout << "Total stock use:";
    for(int i = 0; i<B.return_no_col(); ++i){
        this -> total_roll = this -> total_roll + ceil(current_solution.get_element(i,0));
    }
    cout << this -> total_roll << endl;
    cout << "Total waste:";
    long double temp = 0;
    matrix after_cut = this -> current_solution;
    for(int i = 0; i<B.return_no_col(); ++i){
        after_cut.set_element(i,0,ceil(after_cut.get_element(i,0)));
        this -> waste = this -> waste + (this -> stock * ceil(this -> current_solution.get_element(i,0)));
        for(int j = 0; j<B.return_no_row(); ++j){
            this -> waste = this -> waste - (ceil(this -> current_solution.get_element(i,0))*(B.get_element(j,i))*(this -> roll_sizes.get_element(j,0)));
        }
    }
    after_cut = B*after_cut;
    for(int i = 0; i<after_cut.return_no_row(); ++i){
        temp = temp + (after_cut.get_element(i,0)-this -> demand.get_element(i,0))*(this -> roll_sizes.get_element(i,0));
    }
    this -> waste = this -> waste + temp;

    cout << waste << endl;
}

void csp1d::set(matrix rs, matrix d, double s){
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

double csp1d::get_stock(){
    return this -> stock;
}

double csp1d::get_waste(){
    return this -> waste;
}

int csp1d::get_total_roll(){
    return this -> total_roll;
}

matrix csp1d::get_roll_sizes(){
    return this -> roll_sizes;
}

matrix csp1d::get_demand(){
    return this -> demand;
}

matrix csp1d::get_base(){
    return this -> B;
}

matrix csp1d::get_current_solution(){
    return this -> current_solution;
}


