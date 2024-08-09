#include "matrix.h"

/*--------------- void setMatrix ---------------*/

void matrix::set_matrix(vector<vector<long double>> v){
    if(v.size() == 0 || v[0].size() == 0){
        throw runtime_error("Invalid vector\n");
    }
    for(int i = 0; i < v.size(); ++i){
        if(i >= this -> dimension_row)
            m.push_back(vector<long double>(this -> dimension_col, 0));
        for(int j = 0; j<v[0].size(); ++j){
            if(j >= this -> dimension_col)
                this -> m[i].push_back(v[i][j]);
            else
                this -> m[i][j] = v[i][j];
        }
        if(v[0].size() < this -> dimension_col){
            this -> m[i].erase(this -> m[i].begin() + v[0].size(), this -> m[i].end());
        }
    }
    if(v.size() < this -> dimension_row){
        this -> m.erase(this -> m.begin() + v.size(), m.end());
    }
    this -> dimension_row = v.size();
    this -> dimension_col = v[0].size();
}

void matrix::show_matrix(){
    for(int i = 0; i<this -> dimension_row; ++i){
        for(int j = 0; j<this -> dimension_col; ++j){
            cout << this -> m[i][j];
            if(j != dimension_col - 1)
                cout << " ";
        }
        cout << endl;
    }
}

void matrix::remove_row(int begin, int total = 1){
    if(begin >= this -> dimension_row && begin < 0)
        throw runtime_error("Invalid index");
    if(total <= 1){
        this -> m.erase(m.begin() + begin);
        this -> dimension_row = this -> dimension_row - 1;
    }
    else{
        if(begin + total - 1 < this -> dimension_row){
            this -> m.erase(m.begin() + begin, m.begin() + begin + total);
            this -> dimension_row = this -> dimension_row - total;
        }
        else{
            this -> m.erase(m.begin() + begin, m.end());
            this -> dimension_row = begin;
        }
    }
}

void matrix::remove_col(int begin, int total = 1){
    if(begin >= this -> dimension_col && begin < 0)
        throw runtime_error("Invalid index");
    if(total <= 1){
        for(int i = 0; i<this -> dimension_row; ++i){
            this -> m[i].erase(m[i].begin() + begin);
        }
        this -> dimension_col = this -> dimension_col - 1;
    }
    else{
        if(begin + total - 1 < this -> dimension_col){
            for(int i = 0; i<dimension_row; ++i){
                this -> m[i].erase(m[i].begin() + begin, m[i].begin() + begin + total);
            }
            this -> dimension_col = this -> dimension_col - total;
        }
        else{
            for(int i = 0; i<dimension_row; ++i){
                this -> m[i].erase(m[i].begin() + begin, m[i].end());
            }
            this -> dimension_col = begin;
        }
    }
}

void matrix::set_element(int i, int j, long double element){
    this -> m[i][j] = element;
}

int matrix::return_no_row(){
    return this -> dimension_row;
}

int matrix::return_no_col(){
    return this -> dimension_col;
}

double matrix::get_element(int i, int j){
    return this -> m[i][j];
}

double matrix::det(vector<vector<long double>> v){
    int dimension = v.size();
    if(dimension == 0) {
        return 1;
    }

    if(dimension == 1) {
        return v[0][0];
    }

    if(dimension == 2) {
        return v[0][0] * v[1][1] - v[0][1] * v[1][0];
    }

    double result = 0;
    int sign = 1;
    for(int i = 0; i < dimension; i++) {

        vector<vector<long double>> subVect(dimension - 1, vector<long double> (dimension - 1));
        for(int m = 1; m < dimension; m++) {
            int z = 0;
            for(int n = 0; n < dimension; n++) {
                if(n != i) {
                    subVect[m-1][z] = v[m][n];
                    z++;
                }
            }
        }

        result = result + sign * v[0][i] * this -> det(subVect);
        sign = -sign;
    }

    return result;
}

double matrix::det(){
    if(this -> dimension_row != this -> dimension_col) {
        throw runtime_error("Invalid Matrix size!");
    }
    return this -> det(this -> m);
}

matrix matrix::transpose(){
    
    vector<vector<long double>> v(this -> m[0].size(), vector<long double> (this -> m.size()));
    matrix solution;

    for(size_t i = 0; i < this -> m.size(); i++) {
        for(size_t j = 0; j < this -> m[0].size(); j++) {
            v[j][i] = this -> m[i][j];
        }
    }
    solution.set_matrix(v);

    return solution;
}

matrix matrix::getCofactor(){
    if(this -> dimension_row != this -> dimension_col) {
        throw runtime_error("Invalid");
    } 

    vector<vector<long double>> v(this -> dimension_row, vector<long double> (this -> dimension_row));
    vector<vector<long double>> subVect(this -> dimension_row - 1, vector<long double> (this -> dimension_row - 1));

    for(size_t i = 0; i < this -> dimension_row; i++) {
        for(size_t j = 0; j < this -> dimension_col; j++) {

            int p = 0;
            for(size_t x = 0; x < this -> dimension_row; x++) {
                if(x == i) {
                    continue;
                }
                int q = 0;

                for(size_t y = 0; y < this -> dimension_row; y++) {
                    if(y == j) {
                        continue;
                    }

                    subVect[p][q] = this -> m[x][y];
                    q++;
                }
                p++;
            }
            v[i][j] = pow(-1, i + j) * this ->det(subVect);
        }
    }
    matrix solution(this -> dimension_row, this -> dimension_col);
    solution.set_matrix(v);

    return solution;
}

matrix matrix::inverse(){
    if(this -> det() == 0) {
        throw runtime_error("Determinant is 0");
    } 

    matrix solution(this -> dimension_row, this -> dimension_col);
    solution.set_matrix(this -> m);
    solution = this -> getCofactor().transpose();


    double d = 1.0/(this -> det());
    for(size_t i = 0; i < solution.dimension_row; i++) {
        for(size_t j = 0; j < solution.dimension_col; j++) {
            solution.m[i][j] *= d;
        }
    }

    return solution;
}

matrix matrix::submatrix(int rowb, int rowe, int colb, int cole){
    if(rowe < rowb || cole < colb){
        throw runtime_error("Invalid desire!!!");
    }
    if(rowb <= 0 && rowb >= this -> dimension_row)
        rowb = 0;
    if(colb <= 0 && colb >= this -> dimension_col)
        colb = 0;
    if(rowe <= 0 && rowe >= this -> dimension_row)
        rowe = this -> dimension_row - 1;
    if(cole <= 0 && cole >= this -> dimension_col)
        cole = this -> dimension_col - 1;
    matrix solution(rowe - rowb + 1, cole - colb + 1);
    for(int i = rowb; i<=rowe; ++i){
        for(int j = colb; j<=cole; ++j){
            solution.m[i-rowb][j-colb] = this -> m[i][j];
        }
    }
    return solution;
}

matrix matrix::unit_matrix(int dim){
    matrix solution(dim, dim);
    vector<vector<long double>> v(dim, vector<long double>(dim));

    for(int i = 0; i<dim; ++i){
        for(int j = 0; j<dim; ++j){
            if(i==j)
                v[i][j] = 1;
        }
    }
    solution.set_matrix(v);
    return solution;
}

matrix& matrix::operator=(const matrix& mat){
    this -> set_matrix(mat.m);
    this -> dimension_row = mat.dimension_row;
    this -> dimension_col = mat.dimension_col;
    return *this;
}

matrix matrix::operator+(const matrix& mat){
    if(this -> dimension_row != mat.dimension_row || this -> dimension_col != mat.dimension_col){
        throw runtime_error("Two matrixes have different dimension!!!");
    }
    matrix solution(this -> dimension_row, this -> dimension_col);
    for(int i = 0; i<this -> dimension_row; ++i){
        for(int j = 0; j<this -> dimension_col; ++j){
            solution.m[i][j] = this -> m[i][j] + mat.m[i][j];
        }
    }
    return solution;
}

matrix matrix::operator*(const matrix& mat){
    if(this -> dimension_col != mat.dimension_row)
        throw runtime_error("The first matrix's collumn is not equal to the second matrix's row!!!");
    matrix solution(this -> dimension_row, mat.dimension_col);
    for(int i = 0; i<solution.dimension_row; ++i){
        for(int j = 0; j<solution.dimension_col; ++j){
            double num = 0;
            for(int k = 0; k<this -> dimension_col; ++k){
                num += this -> m[i][k] * mat.m[k][j];
            }
            solution.m[i][j] = num;
        }
    }
    return solution;
}

matrix matrix::operator*(const long double& num){
    matrix solution(this -> dimension_row, this -> dimension_col);
    for(int i = 0; i<solution.dimension_row; ++i){
        for(int j = 0; j<solution.dimension_col; ++j){
            solution.m[i][j] = num*this -> m[i][j];
        }
    }
    return solution;
}


