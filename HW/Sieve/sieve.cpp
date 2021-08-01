/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Edward Yaroslavsky
 * Date        : 9/11/19
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
    PrimesSieve(int limit) : is_prime_{new bool[limit + 1]}, limit_{limit} {
        sieve();
    }

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    inline int num_primes() const {
        return num_primes_;
    }

    //Displays the primes in the specified output
    void display_primes() const {
        // TODO: write code to display the primes in the format specified in the
        // requirements document.
        cout << endl;
    	cout << "Number of primes found: " << count_num_primes() << endl;
    	cout << "Primes up to " << limit_ << ":" << endl;

    	//Array of numbers up to the given input
        int *prime_numbers = new int[limit_ + 1];
        for (int x = 2; x < limit_ + 1; x++) {
        	prime_numbers[x] = x;
        }

        //Finds the max prime
        int max;
        for (int i = limit_; i >= 0; i--) {
    		if (is_prime_[i]) {
    			max = prime_numbers[i];
    			break;
    		}
    	}

    	//Counts how many primes are in the array
    	int num = 0;
    	for (int i = 0; i < limit_ + 1; i++) {
    		if (is_prime_[i]) {
    			num++;
    		}
    	}

    	//Determines the amount of primes per row for the output
    	const int max_prime_width = num_digits(max),
        	primes_per_row = 80 / (max_prime_width + 1);

        if (num <= primes_per_row) { //The single line case
        	for (int i = 2; i < limit_ + 1; i++) {
        		if (is_prime_[i] && prime_numbers[i] != max) {
        			cout << prime_numbers[i] << " ";
        		}
        		else if (is_prime_[i]) {
        			cout << prime_numbers[i];
        		}
        	}
        }
        else { //multiple lines
        	int primes = 0;
        	for (int i = 2; i < limit_ + 1; i++) {
        		if (primes < primes_per_row) { //if does not need to jump to next line
        			if (is_prime_[i] && prime_numbers[i] != max && primes != primes_per_row - 1) { //if the last prime in the row
        				cout << setw(max_prime_width) << prime_numbers[i] << " ";
        				primes++;
        			}
        			else if (is_prime_[i]) { //not the last prime in the row
        				cout << setw(max_prime_width) << prime_numbers[i];
        				primes++;
        			}
        		}
        		else { //jumps to next line of output
        			cout << endl;
        			primes = 0;
        			i--;
        		}
        	}
    	}
        cout << endl;       

        delete prime_numbers;
    }

private:
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    int count_num_primes() const {
        // TODO: write code to count the number of primes found
        int num = 0;
        for (int i = 0; i < limit_ + 1; i++) {
        	if (is_prime_[i]) {
        		num++;
        	}
        }
        return num;
    }

    int num_digits(int num) const {
        // TODO: write code to determine how many digits are in an integer
        // Hint: No strings are needed. Keep dividing by 10.
        if (num / 10 == 0) {
        	return 1;
        }
        else {
        	return 1 + num_digits(num / 10);
        }
    }

    void sieve() {
        // TODO: write sieve algorithm
	    for (int i = 2; i < limit_ + 1; i++) {
	        is_prime_[i] = true;
	    }

	    for (int x = 2; x <= sqrt(limit_); x++) {
	        if (is_prime_[x]) {
	        	for (int y = x*x; y <= limit_; y+=x) {
	        		is_prime_[y] = false;
	        	}
	        }
	    } 
    }
};

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    // TODO: write code that uses your class to produce the desired output.
    //Creates PrimesSieve instance and calls display_primes() method.
    PrimesSieve ps(limit);
    ps.display_primes();

    return 0;
}
