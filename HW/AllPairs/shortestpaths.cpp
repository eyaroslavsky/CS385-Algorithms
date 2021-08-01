/*******************************************************************************
 * Name        : shortestpaths.cpp
 * Author      : Jared Follet and Edward Yaroslavsky
 * Date        : 12/2/19
 * Description : All Pairs, Shortest Paths
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <limits>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

using namespace std;
long num_vertices = 0;
const long INF = std::numeric_limits<long>::max();
long** matrix;
long** lengths;
long** inter;
vector<char> result;

int len(long val){
  int length = 1;
  
  while (val > 9){
    length += 1;
    val = val / 10;
  }
  return length;
}

/**
* Displays the matrix on the screen formatted as a table.
*/
void display_table(long** const matrix, const string &label, const bool use_letters = false) {
        cout << label << endl;
        long max_val = 0;
        for (int i = 0; i < num_vertices; i++) {
        	for (int j = 0; j < num_vertices; j++) {
        		long cell = matrix[i][j];
        		if (cell < INF && cell > max_val) {
        			max_val = matrix[i][j];
       			}
        	}
        }
        int max_cell_width = use_letters ? len(max_val) :
          	len(max(static_cast<long>(num_vertices), max_val));
  	//cout << "Max Val: " << max_val << "and Max Width: " << max_cell_width << endl;
        cout << ' ';
        for (int j = 0; j < num_vertices; j++) {
        	cout << setw(max_cell_width + 1) << static_cast<char>(j + 'A');
        }
        cout << endl;
        for (int i = 0; i < num_vertices; i++) {
        	cout << static_cast<char>(i + 'A');
        	for (int j = 0; j < num_vertices; j++) {
       			cout << " " << setw(max_cell_width);
        		if (matrix[i][j] == INF) {
        			cout << "-";
        		} else if (use_letters) {
        			cout << static_cast<char>(matrix[i][j] + 'A');
        		} else {
        			cout << matrix[i][j];
        		}
        	}
        	cout << endl;
        }
        cout << endl;
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

bool readLine(string line, int linenum){
  	vector<string> args;
  	string temp = "";
  	line = trim(line);
	for (int i = 0; i < (int)line.size(); i++) {
        	if (line[i] == ' ') {
                	args.push_back(temp);
                  	temp.clear();
                } else {
                  	temp += line[i];
                }
        }
  	args.push_back(temp);
  
  	if (args.size() != 3) {
        	cerr << "Error: Invalid edge data '" << line << "' on line " << linenum << "." << endl;
          	return false;
        }
  	
  	char largestLetter = 'A' + num_vertices - 1;
  	
  	for(int i = 0; i < (int)args.size(); i++){
          	if (args[i].size() != 1){
                	if (i == 0){
                        	cerr << "Error: Starting vertex '" << args[i] << "' on line " << linenum << " is not among valid values A-" << largestLetter << "." << endl;
                        	return false;
                        } else if (i == 1) {
				cerr << "Error: Ending vertex '" << args[i] << "' on line " << linenum << " is not among valid values A-"<< largestLetter <<"."<<endl;
				return false;
			}
                }
          	if (args[i][0] < 'A' || args[i][0] > largestLetter){
                  if (i == 0){
                  	cerr << "Error: Starting vertex '" << args[i] << "' on line " << linenum << " is not among valid values A-"<< largestLetter <<"."<<endl;
                    	return false;
                  } else if (i == 1) {
                  	cerr << "Error: Ending vertex '" << args[i] << "' on line " << linenum << " is not among valid values A-"<< largestLetter <<"."<<endl;
                  	return false;
                  }
                
                }
          	if (i == 2){
                  if (!(std::isdigit(args[i][0]))){
                    	cerr << "Error: Invalid edge weight '" << args[i] << "' on line " << linenum << "." << endl;
			return false;
                  }else if (std::stoi(args[i]) < 1){
                    	cerr << "Error: Invalid edge weight '" << args[i] << "' on line " << linenum << "." << endl;
			return false;
                  }
                }
        }
  	
  	int row = args[0][0] - 'A';
  	int col = args[1][0] - 'A';
  	int edgeweight = std::stoi(args[2]);
  	matrix[row][col] = edgeweight;
  
  	return true;
}

void floyd() {
	lengths = new long*[num_vertices];
 	for (int i = 0; i < num_vertices; i++) {
 		lengths[i] = new long[num_vertices];
 		for (int j = 0; j < num_vertices; j++){                  
 			lengths[i][j] = matrix[i][j];
 		}
 	}
  
 	inter = new long*[num_vertices];
 	for(int i = 0; i < num_vertices; i++) {
 	 	inter[i] = new long[num_vertices];
 	 	for (int j = 0; j < num_vertices; j++) {
                	inter[i][j] = INF;
                }
        }
  
  	/*for(int i = 0; i < num_vertices; i++){
          	for (int j = 0; j < num_vertices; j++){
			for (int k = 0; k < num_vertices; k++){
                          	if (lengths[j][i] != INF && lengths[i][k] != INF && lengths[j][k] > (lengths[j][i] + lengths[i][k])){
                                  	lengths[j][k] = lengths[j][i] + lengths[i][k];
                                  	inter[j][k] = i;
                                }
                          	if (j == k){
                                  matrix[j][k] = 0;
                                  lengths[j][k] = 0;
                                  inter[j][k] = INF;                                  
                                }
                        }            
          	}
        }*/
  	
        for(int k = 0; k < num_vertices; k++) {
                  for(int i = 0; i < num_vertices; i++) {
                      for(int j = 0; j < num_vertices; j++) {
                          if(lengths[i][k] != INF && lengths[k][j] != INF && lengths[i][j] > (lengths[i][k] + lengths[k][j])) {
                                      lengths[i][j] = lengths[i][k] + lengths[k][j];
                                      inter[i][j] = k;
                          }
                          if(i == j){
                              matrix[i][j] = 0;
                              lengths[i][j] = 0;
                              inter[i][j] = INF;
                          }
                      }
                  }
        }

  	
  	display_table(matrix, "Distance matrix:", false);
        display_table(lengths, "Path lengths:", false);
        display_table(inter, "Intermediate vertices:", true);
}

void traversehelper(int row, int col){
	if (inter[row][col] == INF) {
        	result.push_back('A' + row);
                result.push_back('A' + col);
        } else {
        	traversehelper(row, inter[row][col]);
                traversehelper(inter[row][col], col);
        }
  	
}

vector<char> traverse(int row, int col){
  	traversehelper(row,col);
  	vector<char> clean;
  	for (int i = 0; i < (int)result.size(); i++){
          	if (std::find(clean.begin(), clean.end(), result[i]) == clean.end()){
                  clean.push_back(result[i]);
                }
          	
        }
  	result.clear();
  	return clean;
}

void path(){
  
  for (int i = 0; i < num_vertices; i++){
    	for (int j = 0; j < num_vertices; j++){
          	vector<char> result = traverse(i,j);
          	if (lengths[i][j] < INF) {
                	cout << (char)('A' + i) << " -> " << (char)('A' + j) << ", distance: " << lengths[i][j] << ", path: ";
          		for (int k = 0; k < (int)result.size(); k++){
                  		cout << result[k];
                  		if (k != (int)result.size()-1){
                    			cout << " -> ";
                  		}
                	}
                } else {
                	cout << (char)('A' + i) << " -> " << (char)('A' + j) << ", distance: infinity, path: none";
                }
                  	
          	cout << endl;
        }
  }
  
  
}

void deletevec(){
  for (int i = 0; i < num_vertices; i++){
    	delete matrix[i];
        delete lengths[i];
        delete inter[i];
  }
  delete matrix;
  delete lengths;
  delete inter;
}


int main(int argc, char * const argv[]){
  // Make sure the right number of command line arguments exist.    
  if (argc != 2) {        
          cerr << "Usage: " << argv[0] << " <filename>" << endl;
          return 1;    
  }    
  // Create an ifstream object.    
  ifstream input_file(argv[1]);    
  // If it does not exist, print an error message.    
  if (!input_file) {        
          cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;        
          return 1;    
  }    
  // Add read errors to the list of exceptions the ifstream will handle.    
  input_file.exceptions(ifstream::badbit);    
  string line;    
  try {        	  
          unsigned int line_number = 1;        
          // Use getline to read in a line.        
          // See http://www.cplusplus.com/reference/string/string/getline/        
          while (getline(input_file, line)) {            
                  if (line_number == 1) {
                    	istringstream iss;   
                    	iss.str(line);
                  	if (!(iss >> num_vertices)) {
                        	cerr << "Error: Invalid number of vertices '" << line << "' on line " << line_number << "." << endl;
                        	return 1;
                        }
                    	
                    	if (num_vertices < 1 || num_vertices > 26) {
                        	cerr << "Error: Invalid number of vertices '" << line << "' on line " << line_number << "." << endl;
                          	return 1;
                        }
                    	
                    	matrix = new long*[num_vertices];
  			for (int i = 0; i < num_vertices; i++){
    				matrix[i] = new long[num_vertices];
    				for (int j = 0; j < num_vertices; j++){
                                	if (i == j) {
                                        	matrix[i][j] = 0;
                                        } else {                              
          					matrix[i][j] = INF;
                                        }
        			}
  			}
                    	
                  } else {
                    	if (!(readLine(line, line_number))){
                        	return 1;
                        }
                  }        
                  line_number++;        
          }        
    
  	  
  // Don't forget to close the file.        
          input_file.close();    
  } 
  catch (const ifstream::failure &f) {        
          cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";        
          return 1;    
  } 
  
  floyd();
  path();
  deletevec();
  return 0;	

}




