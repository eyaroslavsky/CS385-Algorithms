/*******************************************************************************
 * Name    : gcd.cpp
 * Author  : Edward Yaroslavsky
 * Version : 1.0
 * Date    : August 29, 2019
 * Description : Computes the GCD of two command-line arguments.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

int gcd_iterative(int m, int n) {
	int lower;
	if (m == 0) {
		return n;
	}
	else if (n == 0) {
		return m;
	}
	else {
		if (m < 0) {
			m = abs(m);
		}
		if (n < 0) {
			n = abs(n);
		}
		
		if (n < m) {
		 	lower = n;
		}
		else {
			lower = m;
		}
		
		for (int i = lower; i >= 1; i--) {
			if (m % i == 0 && n % i == 0) {
				return i;
			}
		}
		return lower;
	}
}

int gcd_recursive(int m, int n) {
	if (m < 0) {
		m = abs(m);
		}
	if (n < 0) {
		n = abs(n);
	}
	
	if (n > m) {
		return gcd_recursive(n, m);
	}
	else {
		if (n == 0) {
			return m;
		}
		return gcd_recursive(n, m % n);
	}
}

int main(int argc, char* const argv[]) {
    int m, n;
    istringstream iss;

    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <integer m> <integer n>"
             << endl;
        return 1;
    }
    iss.str(argv[1]);
    if ( !(iss >> m) ) {
        cerr << "Error: The first argument is not a valid integer."
             << endl;
        return 1;
    }
    iss.clear(); // clear the error code
    iss.str(argv[2]);
    if ( !(iss >> n) ) {
        cerr << "Error: The second argument is not a valid integer."
             << endl;
        return 1;
    }

    cout << "Iterative: gcd(" << m << ", " << n << ") = " << gcd_iterative(m, n) << endl;
    cout << "Recursive: gcd(" << m << ", " << n << ") = " << gcd_recursive(m, n) << endl;
    return 0;
}
