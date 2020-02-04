/*******************************************************************************
 * Name    : sqrt.cpp
 * Author  : Robert Schaedler III
 * Version : 1.0
 * Date    : January 28, 2020
 * Description : Computes the the SQRT of a number using Newton's method.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <limits>
#include <sstream>

using namespace std;

double sqrtR(double num, double epsilon, double last_guess) {
    double next_guess = (last_guess + num / last_guess) / 2;
    if (num == 0.0 || num == 1.0)
        return num;
    else if (num < 0.0)
        return numeric_limits<double>::quiet_NaN();
    else if (abs(last_guess - next_guess) <= epsilon)
        return next_guess;
    else
        return sqrtR(num, epsilon, next_guess);
}

double sqrt(double num, double epsilon) {
    if (num == 0 || num == 1) {
        return num;
    } else if (num < 0) {
        return numeric_limits<double>::quiet_NaN();
    }

    double last_guess = num;
    double next_guess = (last_guess + num / last_guess) / 2;

    while (abs(last_guess - next_guess) > epsilon) {
        last_guess = next_guess;
        next_guess = (last_guess + num / last_guess) / 2;
    }

    return next_guess;
}

int main(int argc, char *argv[]) {
    if (argc > 3 || argc < 2) {
        cerr << "Usage: " << argv[0] << " <value> [epsilon]" << endl;
        return 1;
    }

    istringstream iss;
    double ep = 1e-7;
    double num;

    iss.str(argv[1]);
    if (!(iss >> num)) {
        cerr << "Error: Value argument must be a double." << endl;
        return 1;
    }

    iss.clear();
    if (argc == 3) {
        iss.str(argv[2]);
        if (!(iss >> ep) | (ep <= 0)) {
            cerr << "Error: Epsilon argument must be a positive double." << endl;
            return 1;
        }
    }

    cout.precision(8);

    cout << fixed << sqrt(num, ep) << endl;
    // cout << fixed << sqrtR(num, ep, num) << endl;
    return 0;
}