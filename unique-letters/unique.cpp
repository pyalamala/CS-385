/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Robert Schaedler III
 * Date        : Feb. 12 2020
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cctype>
#include <iostream>
#include <sstream>

using namespace std;

bool is_all_lowercase(const string &s) {
    for (const auto &c : s) {
        if (c < 'a' || c > 'z') {
            return false;
        }
    }
    return true;
}

bool all_unique_letters(const string &s) {
    unsigned int bit_set = 0;
    for (const auto &c : s) {
        unsigned int char_setter = 1 << (c - 'a');
        if (char_setter & bit_set) {
            return false;
        }
        bit_set |= char_setter;
    }

    return true;
}

int main(int argc, char *const argv[]) {
    if (argc > 2 || argc < 2) {
        cerr << "Usage: " << argv[0] << " <string>" << endl;
        return 1;
    }

    istringstream iss;
    string s;

    iss.str(argv[1]);
    if (!(iss >> s) | !(is_all_lowercase(s))) {
        cerr << "Error: String must contain only lowercase letters." << endl;
        return 1;
    }
    iss.clear();

    if (s.length() > 26 || !all_unique_letters(s)) {
        cout << "Duplicate letters found." << endl;
    } else {
        cout << "All letters are unique." << endl;
    }

    return 1;
}
