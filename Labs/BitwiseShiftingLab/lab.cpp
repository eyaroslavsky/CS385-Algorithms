#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

int mystery1(int a, int b) {
	int c = a - b,
		d = (c >> 7) & 1,
		mystery = a - c * d;
	return mystery;
}

void mystery2(int values[], int i, int j) {
	values[i] = values[i] ^ values[j];
	values[j] = values[i] ^ values[j];
	values[i] = values[i] ^ values[j];

	for (int x = 0; x < 4; x++) {
		cout << "[" << values[x] << ",";
	}
	cout << "]" << endl;
}

int mystery3(int x, int y) {
	int s, c;
	s = x ^ y;
	c = x & y;
	while (c != 0) {
		c = c << 1;
		x = s;
		y = c;
		s = x ^ y;
		c = x & y;
	}
	return s;
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

    //cout << "mystery1(" << m << "," << n << ") = " << mystery1(m, n) << endl;
    cout << "mystery1(3, 7) = " << mystery1(3, 7) << endl;
    cout << "mystery1(8, 7) = " << mystery1(8, 7) << endl;

    //cout << "mystery2([1,2,3,4], 0, 3) = " << endl;
    //mystery2([1,2,3,4], 0, 3);
    //cout << "mystery2([1,2,3,4], 1, 2) = " << endl;
    //mystery2([1,2,3,4], 1, 2);

    cout << "mystery3(5, 7) = " << mystery3(5, 7) << endl;
    cout << "mystery3(2, 8) = " << mystery3(2, 8) << endl;
    return 0;
}