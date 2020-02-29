/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Robert Schaedler III
 * Date        : Feb. 18, 2020
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

using namespace std;

/**
 * Returns the number of digits in an integer. 
 */
int num_digits(int num) {
    return (num / 10 == 0) ? 1 : 1 + num_digits(num / 10);
}

/**
 * Return a vector of vectors of ints representing the different combinations of ways to climb num_stairs stairs, moving up either 1, 2, or 3 stairs at a time.
 */
vector<vector<int>> get_ways(int num_stairs) {
    vector<vector<int>> ways;
    if (num_stairs <= 0) {
        ways.push_back(vector<int>());
    } else {
        for (int i = 1; i < 4; i++) {
            if (num_stairs >= i) {
                vector<vector<int>> result = get_ways(num_stairs - i);
                for (auto &v : result) {
                    v.insert(v.begin(), i);
                }
                ways.insert(ways.end(), result.begin(), result.end());
            }
        }
    }
    return ways;
}

/** 
 * Displays the ways to climb stairs by iterating over the vector of vectors and printing each combination. 
 */
void display_ways(const vector<vector<int>> &ways) {
    const int max_count = ways.size(), max_count_width = num_digits(max_count);
    int count = 0;
    for (auto &v : ways) {
        cout << setw(max_count_width) << ++count << ". ";
        cout << "[";
        unsigned int i = 0;
        if (i >= 0) {
            cout << v[i++];
        }
        for (; i < v.size(); i++) {
            cout << ", " << v[i];
        }
        cout << "]" << endl;
    }
}

int main(int argc, char *const argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <number of stairs>" << endl;
        return 1;
    }

    istringstream iss;
    int num;

    iss.str(argv[1]);
    if (!(iss >> num) | (num <= 0)) {
        cerr << "Error: Number of stairs must be a positive integer." << endl;
        return 1;
    }
    iss.clear();

    vector<vector<int>> ways = get_ways(num);
    int size = ways.size();

    if (size > 1) {
        cout << size << " ways to climb " << num << " stairs." << endl;
    } else {
        cout << size << " way to climb " << num << " stair." << endl;
    }

    display_ways(ways);

    return 0;
}
