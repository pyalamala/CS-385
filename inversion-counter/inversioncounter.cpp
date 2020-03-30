/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Robert Schaedler III
 * Version     : 1.0
 * Date        : 3/25/2020
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
    long count = 0;
    for (int i = 0; i < length - 1; i++) {
        for (int j = i + 1; j < length; j++) {
            count += (array[i] > array[j]) ? 1 : 0;
        }
    }
    return count;
}

/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
    int *scratch = new int[length];
    long inversions = mergesort(array, scratch, 0, length - 1);
    delete scratch;
    return inversions;
}

/**
 1. if lo < hi then
 2.     mid = lo + (hi - lo) / 2
 3.     MERGESORT(A, lo, mid)
 4.     MERGESORT(A, mid+1, hi)
 5.     L = lo
 6.     H = mid + 1
 7.     for k <- lo to hi
 8.         do if L <= mid and (H > hi or A[L] <= A[H])
 9.             then scratch[k] = A[L]
10.                  L <- L + 1
11.             else scratch[k] = A[H]
12.                  H <- H + 1
13.     for k <- lo to hi
14.         do A[k] <- scratch[k]
 */
static long mergesort(int array[], int scratch[], int low, int high) {
    long count = 0L;
    if (low < high) {
        int mid = low + (high - low) / 2,
            L = low,
            H = mid + 1;
        count = mergesort(array, scratch, low, mid) + mergesort(array, scratch, mid + 1, high);
        for (int i = low; i <= high; i++) {
            if (L <= mid && (H > high || array[L] <= array[H])) {
                scratch[i] = array[L++];
            } else {
                scratch[i] = array[H++];
                count += mid - L + 1;
            }
        }
        for (int i = low; i <= high; i++) {
            array[i] = scratch[i];
        }
    }
    return count;
}

int main(int argc, char *argv[]) {
    if (argc > 2) {
        cerr << "Usage: " << argv[0] << " [slow]";
        return 1;
    }

    string slow;
    if (argc == 2 && (slow = argv[1]).compare("slow") != 0) {
        cerr << "Error: Unrecognized option '" << slow << "'.";
        return 1;
    }

    cout << "Enter sequence of integers, each followed by a space: " << flush;

    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }

    if (values.size() == 0) {
        cerr << "Error: Sequence of integers not received." << endl;
        return 1;
    }

    cout << "Number of inversions: " << ((argc == 2) ? count_inversions_slow(&values[0], values.size()) : count_inversions_fast(&values[0], values.size())) << endl;

    return 0;
}
