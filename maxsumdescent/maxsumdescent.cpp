/*******************************************************************************
 * Name        : maxsumdescent.cpp
 * Author      : Robert Schaedler III
 * Version     : 1.0
 * Date        : Apr. 21, 2020
 * Description : Dynamic programming solution to max sum descent problem.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const char DELIMITER = ' ';

int **values, **sums;
int num_rows, max_sum_index, table_max;

/**
 * Returns the number of digits in an integer. 
 */
int num_digits(int num) {
    return (num / 10 == 0) ? 1 : 1 + num_digits(num / 10);
}

/**
 * Displays the 2D array of values read from the file in the format of a table.
 */
void display_table() {
    int max_width = num_digits(table_max);
    for (int i = 0; i < num_rows; i++) {
        cout << setw(max_width) << values[i][0];
        for (int j = 1; j < i + 1; j++) {
            cout << setw(max_width + 1) << values[i][j];
        }
        cout << "\n";
    }
}

/**
 * Returns the maximum sum possible in the triangle of values.
 * By starting at the top of the triangle and moving to adjacent numbers on the
 * row below, this function uses dynamic programming to build up another table
 * of partial sums.
 */
int compute_max_sum() {
    sums = new int *[num_rows];
    sums[0] = values[0];

    int *row;
    for (int i = 1; i < num_rows; ++i) {
        row = new int[i + 1];
        row[0] = values[i][0] + sums[i - 1][0];
        for (int j = 1; j < i; ++j) {
            row[j] = values[i][j] + max(sums[i - 1][j - 1], sums[i - 1][j]);
        }
        row[i] = values[i][i] + sums[i - 1][i - 1];
        sums[i] = row;
    }

    int max_sum = sums[num_rows - 1][0];
    for (int i = 1; i < num_rows; ++i) {
        if (sums[num_rows - 1][i] > max_sum) {
            max_sum = sums[num_rows - 1][i];
            max_sum_index = i;
        }
    }

    return max_sum;
}

/**
 * Returns a vector of ints with the values from the top to the bottom of the
 * triangle that comprise the maximum sum.
 */
vector<int> backtrack_solution() {
    vector<int> solution;
    solution.reserve(num_rows);

    int row_index = max_sum_index;
    solution.emplace_back(values[num_rows - 1][row_index]);
    for (int i = num_rows - 2; i > 0; --i) {
        if (row_index == 0) {
            solution.emplace_back(values[i][row_index]);
        } else if (row_index > i) {
            solution.emplace_back(values[i][--row_index]);
        } else {
            if (sums[i][row_index] < sums[i][row_index - 1]) {
                solution.emplace_back(values[i][--row_index]);
            } else {
                solution.emplace_back(values[i][row_index]);
            }
        }
    }
    solution.emplace_back(values[0][0]);

    return solution;
}

/**
 * Reads the contents of the file into the global 2D array 'values'. If
 * successful, the function also allocates memory for the 2D array 'sums'.
 */
bool load_values_from_file(const string &filename) {
    ifstream input_file(filename.c_str());
    if (!input_file) {
        cerr << "Error: Cannot open file '" << filename << "'.\n";
        return false;
    }
    input_file.exceptions(ifstream::badbit);
    string line;
    vector<string> data;
    try {
        while (getline(input_file, line)) {
            data.push_back(line);
        }
        input_file.close();
    } catch (const ifstream::failure &f) {
        cerr << "Error: An I/O error occurred reading '" << filename << "'.";
        return false;
    }

    num_rows = data.size();
    values = new int *[num_rows];
    int num;
    for (int i = 0; i < num_rows; i++) {
        stringstream ss(data[i]);
        string buffer;

        int row_index = 0;
        int *row = new int[i + 1];
        while (getline(ss, buffer, DELIMITER)) {
            num = stoi(buffer);
            table_max = max(table_max, num);
            row[row_index++] = num;
        }
        values[i] = row;
    }

    return true;
}

/**
 * Frees up the memory allocated for the 2D array of values and the 2D array of
 * partial sums.
 */
void cleanup() {
    for (int i = 0; i < num_rows; i++) {
        delete[] values[i];
        delete[] sums[i];
    }
    delete[] values;
    delete[] sums;
}

int main(int argc, char *const argv[]) {
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);

    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }
    string filename(argv[1]);
    if (!load_values_from_file(filename)) {
        return 1;
    }

    if (num_rows == 0) {
        cout << "Max sum: 0\nValues: [] \n";
        return 0;
    }

    display_table();
    cout << "Max sum: " << compute_max_sum() << "\n";

    vector<int> solution = backtrack_solution();
    cout << "Values: [" << solution[num_rows - 1];
    for (int i = num_rows - 2; i >= 0; --i) {
        cout << ", " << solution[i];
    }
    cout << "]\n";

    cleanup();

    return 0;
}
