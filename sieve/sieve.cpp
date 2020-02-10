/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Robert Schaedler III
 * Date        : Feb. 06, 2020
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
   public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete[] is_prime_;
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;

   private:
    // Instance variables
    bool* const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit) : is_prime_{new bool[limit + 1]}, limit_{limit} {
    sieve();
}

void PrimesSieve::display_primes() const {
    cout << "Number of primes found: " << num_primes() << endl;
    cout << "Primes up to " << limit_ << ":" << endl;

    const int max_prime_width = num_digits(max_prime_), primes_per_row = 80 / (max_prime_width + 1);

    int row_prime_count = 0;
    for (int i = 2; i < limit_ + 1; i++) {
        // print a new row if the current row is "full"
        if (row_prime_count == primes_per_row) {
            row_prime_count = 0;
            cout << endl;
        }

        if (!is_prime_[i]) {
            // print a leading space on all primes except the first
            if (row_prime_count != 0) {
                cout << " ";
            }

            if (num_primes() > primes_per_row) {  // print multiple rows
                cout << setw(max_prime_width) << i;
            } else {  // print single row
                cout << i;
            }
            row_prime_count++;
        }
    }

    cout << endl;
}

int PrimesSieve::count_num_primes() const {
    int count = 0;
    for (int i = 2; i < limit_ + 1; i++) {
        if (!is_prime_[i]) {
            count++;
        }
    }
    return count;
}

void PrimesSieve::sieve() {
    for (int i = 2; i <= sqrt(limit_); i++) {
        if (!is_prime_[i]) {
            for (int j = pow(i, 2); j <= limit_; j += i) {
                is_prime_[j] = true;
            }
        }
    }

    // find the max prime
    for (int i = limit_; i > 2; i--) {
        if (!is_prime_[i]) {
            max_prime_ = i;
            break;
        }
    }

    num_primes_ = count_num_primes();
}

int PrimesSieve::num_digits(int num) {
    return (num / 10 == 0) ? 1 : 1 + num_digits(num / 10);
}

int main() {
    cout << "**************************** "
         << "Sieve of Eratosthenes"
         << " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if (!(iss >> limit)) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    // TODO: write code that uses your class to produce the desired output.
    cout << endl;
    PrimesSieve sieve = PrimesSieve(limit);
    sieve.display_primes();

    return 0;
}
