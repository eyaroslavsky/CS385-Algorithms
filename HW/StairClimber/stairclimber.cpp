/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Edward Yaroslavsky
 * Date        : 9/28/19
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector< vector<int> > get_ways(int num_stairs) {
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.
    vector< vector<int> > ways;
    if (num_stairs <= 0) { //base case
    	vector<int> empty;
    	ways.push_back(empty);
    }
    else {
    	for (int i = 1; i < 4; i++) { //Not larger than 3 steps at a time
    		if (num_stairs >= i) {
    			vector< vector<int> > result;
    			result = get_ways(num_stairs - i);
    			for (auto j: result) {
    				j.insert(j.cbegin(), i);
    				ways.push_back(j); //Add the vector that works
    			}    			
    		}
    	}
    }
    return ways;
}

void display_ways(const vector< vector<int> > &ways) {
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.
    stringstream ss;
    ss << ways.size();
    string size;
    ss >> size; //for adjusting the spacing
    int counter = 1;
    for (auto v: ways) {
    	cout << setw(size.size()) << counter << ". [";
    	for (size_t i = 0; i < v.size(); i++) {
    		if (i == v.size() - 1) { //if it's the last step possibility
    			cout << v[i];
    		}
    		else {
    			cout << v[i] << ", ";
    		}
    	}
    	cout << "]" << endl;
    	counter++;
    }
}

int main(int argc, char * const argv[]) {
	if (argc != 2) { //if there aren't 2 arguments
        cerr << "Usage: " << argv[0] << " <number of stairs>" << endl;
        return 1;
    }

    istringstream iss;
    iss.str(argv[1]);
    int stairs;
    if (!(iss >> stairs) || stairs <= 0) { //if the input isn't an integer or is not positive
        cerr << "Error: Number of stairs must be a positive integer." << endl;
        return 1;
    }

    else {
    	if (get_ways(stairs).size() == 1) {
    		cout << get_ways(stairs).size() << " way to climb " << stairs << " stair." << endl;
    	}
    	else {
    		cout << get_ways(stairs).size() << " ways to climb " << stairs << " stairs." << endl;
    	}
    	display_ways(get_ways(stairs));
    }

    return 0;
}
