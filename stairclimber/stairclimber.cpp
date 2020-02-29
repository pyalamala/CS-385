/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Robert Schaedler III
 * Date        : Feb. 24, 2020
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int max_count_width = 0, ways_size = 0;

/**
 * Returns the number of digits in an integer. 
 */
int num_digits(int num) {
    return (num / 10 == 0) ? 1 : 1 + num_digits(num / 10);
}

/**
 * Calculates the number of possible ways to traverse num_stair stairs, 
 * moving up either 1, 2, or 3 stairs at a time.
 */
int num_ways(int num_stairs) {
    if (num_stairs == 1 || num_stairs == 2) {
        return num_stairs;
    } else if (num_stairs == 3) {
        return 4;
    }

    int n1 = 1, n2 = 2, n3 = 4, num_ways = 0;
    for (; num_stairs > 3; num_stairs--) {
        num_ways = n1 + n2 + n3;
        n1 = n2;
        n2 = n3;
        n3 = num_ways;
    }
    return num_ways;
}

/** 
 * Internal method for finding the different combinations of 
 * ways to climb num_stairs.
 */
void get_ways_helper(int num_stairs, vector<vector<int>> &ways, vector<int> &way) {
    if (num_stairs == 0) {
        ways.emplace_back(way);
    } else {
        for (int i = 1; i < 4; i++) {
            if (num_stairs >= i) {
                way.emplace_back(i);
                get_ways_helper(num_stairs - i, ways, way);
                way.pop_back();
            } else {
                break;
            }
        }
    }
}

/**
 * Return a vector of vectors of ints representing the different 
 * combinations of ways to climb num_stairs stairs, moving up 
 * either 1, 2, or 3 stairs at a time.
 */
vector<vector<int>> get_ways(int num_stairs) {
    vector<vector<int>> ways;
    ways.reserve(ways_size);

    vector<int> way;
    way.reserve(num_stairs);

    get_ways_helper(num_stairs, ways, way);
    return ways;
}

/** 
 * Displays the ways to climb stairs by iterating over the 
 * vector of vectors and printing each combination. 
 */
void display_ways(const vector<vector<int>> &ways) {
    const int max_count = ways.size(), max_count_width = num_digits(max_count);

    int count = 0;
    const auto ways_end = ways.cend();
    for (auto ways_iter = ways.cbegin(); ways_iter != ways_end; ++ways_iter) {
        printf("%*d. [", max_count_width, ++count);

        auto val_iter = ways_iter->cbegin();
        const auto val_iter_end = ways_iter->cend();

        printf("%d", *val_iter++);
        for (; val_iter != val_iter_end; ++val_iter) {
            printf(", %d", *val_iter);
        }
        printf("]\n");
    }
}

int main(int argc, char *const argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number of stairs>\n", argv[0]);
        return 1;
    }

    int num;
    istringstream iss;

    iss.str(argv[1]);
    if (!(iss >> num) | (num <= 0)) {
        fprintf(stderr, "Error: Number of stairs must be a positive integer.\n");
        return 1;
    }
    iss.clear();

    ways_size = num_ways(num);
    max_count_width = num_digits(ways_size);

    vector<vector<int>> results = get_ways(num);

    const char *plural = (ways_size > 1) ? "s" : "";
    printf("%d way%s to climb %d stair%s.\n", ways_size, plural, num, plural);

    display_ways(results);

    return 0;
}
