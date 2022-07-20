#include <iostream>
#include <vector>

bool isDiagonallyDominant(const std::vector<std::vector<double>> &matrix) {
    bool strictly = false;
    for (int i = 0; i < matrix.size(); ++i) {
        double sum = 0;
        for (double j: matrix[i]) {
            sum += abs(j);
        }
        if (sum < 2 * matrix[i][i]) {
            strictly = true;
        } else if (sum > 2 * matrix[i][i]) {
            return false;
        }
    }
    return strictly;
}

bool almostSame(const std::vector<double> &a,
                const std::vector<double> &b,
                double eps) {
    if(a.size()!=b.size()){
       return false;
    }
    for (int i = 0; i < a.size(); ++i) {
        if (abs(a[i] - b[i]) > eps) {
            return false;
        }
    }
    return true;
}

std::vector<double> solve(const std::vector<std::vector<double>> &matrix,
                          const std::vector<double> &B,
                          double eps) {
    if (!isDiagonallyDominant(matrix)) {
        std::cout << "Matrix is not diagonally dominant\n";
        std::vector<double> noSol;
        return noSol;
    }

    std::vector<double> sol(matrix.size(), 0);
    std::vector<double> tempSol(matrix.size(),eps+1);//this initialization is for first iteration(sol=tempSol)

    while (!almostSame(sol, tempSol, eps)) {
        sol = tempSol;
        tempSol.clear();
        for (double s: sol) {
            std::cout << s << ' ';
        }
        std::cout << std::endl;
        for (int i = 0; i < matrix.size(); ++i) {
            double sum = 0;
            for (int j = 0; j < matrix[i].size(); ++j) {
                sum += matrix[i][j] * sol[j];
            }
            tempSol.push_back((B[i] - (sum - matrix[i][i] * sol[i])) / matrix[i][i]);
        }
    }
    return sol;
}


int main() {
    std::vector<std::vector<double>> matrix = {{9, 2,  3},
                                               {1, 12, 9},
                                               {4, 6,  14}};


     std::vector<double> b = {7, 2, 1};


    /*std::vector<std::vector<double>> matrix = {{5, 0.2,  -0.7},
                                               {1, 3.8, -1.5},
                                               {1, -1,  7.3}};
    std::vector<double> b = {1, -1, 0};*/
    double eps = 0.0001;

    std::vector<double> solution = solve(matrix, b, eps);

    for (double i: solution) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
    return 0;
}