/*******************************************************************************
 * Name        : anagramfinder.cpp
 * Author      : Edward Yaroslavsky
 * Version     : 1.0
 * Date        : 11/11/19
 * Description : Finds the max anagrams in a dictionary file.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <cctype>
#include <fstream>
#include <unordered_map>

using namespace std;

bool compare(string str1, string str2) {
	return str1 < str2;
}

void sortDict(vector<string> &v) {
	sort(v.begin(), v.end(), compare);
}

const string whitespace = " \n\r\t\f\v";

string ltrim(const string &s) {
	size_t start = s.find_first_not_of(whitespace);
	return (start == std::string::npos) ? "" : s.substr(start);
}

string rtrim(const string &s) {
	size_t end = s.find_last_not_of(whitespace);
	return (end == std::string::npos) ? "" : s.substr(0, end+1);
}

string trim(const string &s) {
	return rtrim(ltrim(s));
}

int kSmallest(vector<string> v, int k) {
	vector<string> copy = v;
	sortDict(copy);
	string value = copy[k-1];
	for (int i = 0; i < int(v.size()); i++) {
		if (v[i] == value) {
			return i;
		}
	}
	return -1;
}

int addToMap(unordered_map<string, vector<string>> &umap, vector<string> v) {
	vector<string> newVector = v;
	int max = 1;

	for (int i = 0; i < (int)v.size(); i++) {
		if ((trim(v[i])).find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") != std::string::npos) {
			continue;			
		}

		std::transform(newVector[i].begin(), newVector[i].end(), newVector[i].begin(), ::tolower);
		newVector[i] = trim(newVector[i]);
		sort(newVector[i].begin(), newVector[i].end());
		
		if (umap.find(newVector[i]) == umap.end()) {
			vector<string> vectorToAdd;
			vectorToAdd.push_back(v[i]);
			umap[newVector[i]] = vectorToAdd;
		}
		else {
			umap[newVector[i]].push_back(v[i]);

			if ((int)umap[newVector[i]].size() > max) {
				max = (int)umap[newVector[i]].size();
			}
		}
	}

	return max;
}

void display(vector<vector<string>> v) {
	vector<string> firstValues;
	for (int i = 0; i < (int)v.size(); i++) {
		sort(v[i].begin(), v[i].end());
		firstValues.push_back(v[i][0]);
	}

	int counter = 1;
	while (counter <= (int)firstValues.size()) {
		int k = kSmallest(firstValues, counter);
		for (int x = 0; x < (int)v[k].size(); x++) {
			cout << v[k][x] <<endl;
		}
		cout << endl;
		counter++;
	}
	
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <dictionary file>" << endl;
        return 1;
    }

    vector<string> v;

    ifstream in(argv[1]);

    if (!in) {
    	cerr << "Error: File '" << argv[1] << "' not found." << endl;
    	return 1;
    }

    string str;
    while (getline(in, str)) {
    	if (str.size() > 0) {
    		v.push_back(str);
    	}
    }
    in.close();

    unordered_map<string, vector<string>> umap;
    int max = addToMap(umap, v);

    if (max == 1) {
    	cout << "No anagrams found." << endl;
    	return 0;
    }

    vector<vector<string>> maxGroupVector;
    for (auto i: umap) {
    	if ((int)i.second.size() == max) {
    		maxGroupVector.push_back(i.second);
    	}
    }

    cout << "Max anagrams: " << max << endl;
    display(maxGroupVector);

    return 0;
}