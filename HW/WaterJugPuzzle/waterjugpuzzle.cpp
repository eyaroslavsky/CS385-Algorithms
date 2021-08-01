/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Edward Yaroslavsky and Charles Fee
 * Date        : 10/13/19
 * Description : Water Jug Problem
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <sstream>
#include <vector>
#include <queue>

using namespace std;

// Struct to represent state of water in the jugs.
struct State
{
    int a, b, c;
    vector<int> parent;
    vector<string> directions;
    State() : a(0), b(0), c(0), parent({}){}
    State(int _a, int _b, int _c, vector<int> _parent) : a(_a), b(_b), c(_c), parent(_parent){}

    void setABC(int _a, int _b, int _c){
        a = _a;
        b = _b;
        c = _c; 
    }
    void setParent(int aindex, int bindex){
        parent.push_back(aindex);
        parent.push_back(bindex);
    }
    vector<int> getParent(){
        return parent;
    }
    string to_string()
    {
        ostringstream oss;
        if(a < getParent()[0] && b == getParent()[1]){
            if(getParent()[0]-a > 1){
                oss << "Pour " << getParent()[0]-a << " gallons from A to C. "<< "(" << a << ", " << b << ", " << c << ")";
            }else{
                oss << "Pour " << getParent()[0]-a << " gallon from A to C. "<< "(" << a << ", " << b << ", " << c << ")";
            }
        }else if(a > getParent()[0] && b == getParent()[1]){
            if(a-getParent()[0] > 1){
                oss << "Pour " << a-getParent()[0] << " gallons from C to A. "<< "(" << a << ", " << b << ", " << c << ")";
            }else{
                oss << "Pour " << a-getParent()[0] << " gallon from C to A. "<< "(" << a << ", " << b << ", " << c << ")";
            }
        }else if(a == getParent()[0] && b < getParent()[1]){
            if(getParent()[1]-b > 1){
                oss << "Pour " << getParent()[1]-b << " gallons from B to C. "<< "(" << a << ", " << b << ", " << c << ")";
            }else{
                oss << "Pour " << getParent()[1]-b << " gallon from B to C. "<< "(" << a << ", " << b << ", " << c << ")";
            }
        }else if(a == getParent()[0] && b > getParent()[1]){
            if(b-getParent()[1] > 1){
                oss << "Pour " << b-getParent()[1] << " gallons from C to B. "<< "(" << a << ", " << b << ", " << c << ")";
            }else{
                oss << "Pour " << b-getParent()[1] << " gallon from C to B. "<< "(" << a << ", " << b << ", " << c << ")";
            }
        }else if(a < getParent()[0]){
            if(getParent()[0]-a > 1){
                oss << "Pour " << getParent()[0]-a << " gallons from A to B. "<< "(" << a << ", " << b << ", " << c << ")";
            }else{
                oss << "Pour " << getParent()[0]-a << " gallon from A to B. "<< "(" << a << ", " << b << ", " << c << ")";
            }
        }else if(b < getParent()[1]){
            if(getParent()[1]-b > 1){
                oss << "Pour " << getParent()[1]-b << " gallons from B to A. "<< "(" << a << ", " << b << ", " << c << ")";
            }else{
                oss << "Pour " << getParent()[1]-b << " gallon from B to A. "<< "(" << a << ", " << b << ", " << c << ")";
            }
        }
        return oss.str();
    }
};
void waterjug(int a, int b, int c, int ga, int gb, int gc)
{
    int ca = 0;
    int cb = 0;
    int cc = c;
    queue <vector<int>> q;
    q.push({ca,cb,cc});
    State **array  = new State*[a+2];
    for (int i = 0; i <= a; ++i){
        array[i] = new State[b+2];
    }
    array[ca][cb].setParent(3005,3005);
    array[ca][cb].setABC(0,0,8);
    bool solvable = false;
    vector<int> wumbo;
    vector <int> base = {3005,3005};
    while(!q.empty()){
        ca = q.front()[0];
        cb = q.front()[1];
        cc = q.front()[2];
        q.pop();
        

        //goal reached break out of loop
        if(ca == ga && cb == gb && cc == gc){
            solvable = true;
            break;
        }

        //C to A and sees if there is a cycle
        if(cc != 0 && ca != a && cc >= (a - ca) && array[a][cb].getParent().empty()){
            array[a][cb].setABC(a, cb, cc-(a-ca));
            array[a][cb].setParent(ca,cb);
            q.push({a,cb,cc-(a-ca)});
        } else if(cc != 0 && ca != a && cc < (a - ca) && array[ca+cc][cb].getParent().empty()){
            array[ca+cc][cb].setABC(ca+cc,cb,0);
            array[ca+cc][cb].setParent(ca,cb);
            q.push({ca+cc, cb, 0});
        }
        //B to A and sees if there is a cycle
        if(cb != 0 && ca != a && cb >= (a - ca) && array[a][cb-(a-ca)].getParent().empty()){
            array[a][cb-(a-ca)].setABC(a,cb-(a-ca), cc);
            array[a][cb-(a-ca)].setParent(ca,cb);
            q.push({a, cb-(a-ca), cc});
        }else if(cb != 0 && ca != a && cb < (a - ca) && array[ca+cb][0].getParent().empty()){
            array[ca+cb][0].setABC(ca+cb,0,cc);
            array[ca+cb][0].setParent(ca,cb);
            q.push({ca+cb, 0, cc});
        }
        //C to B
        if(cc != 0 && cb != b && cc >= (b-cb) && array[ca][b].getParent().empty()){
            array[ca][b].setABC(ca,b,cc-(b-cb));
            array[ca][b].setParent(ca,cb);
            q.push({ca,b,cc-(b-cb)});
        }else if(cc != 0 && cb != b && cc < (b - cb) && array[ca][cb+cc].getParent().empty()){
            array[ca][cb+cc].setABC(ca,cb+cc,0);
            array[ca][cb+cc].setParent(ca,cb);
            q.push({ca, cb+cc, 0});
        }
        //A to B
        if(ca != 0 && cb != b && ca >= (b-cb) && array[ca-(b-cb)][b].getParent().empty()){
            array[ca-(b-cb)][b].setABC(ca-(b-cb), b, cc);
            array[ca-(b-cb)][b].setParent(ca,cb);
            q.push({ca-(b-cb), b, cc});
        }else if(ca != 0 && cb != b && ca < (b-cb) && array[0][cb+ca].getParent().empty()){
            array[0][cb+ca].setABC(0,cb+ca,cc);
            array[0][cb+ca].setParent(ca,cb);
            q.push({0, cb+ca, cc});
        }
        //B to C
        if(cb!= 0 && cc != c && cb >= (c-cc) && array[ca][cb-(c-cc)].getParent().empty()){
            array[ca][cb-(c-cc)].setABC(ca, cb-(c-cc), c);
            array[ca][cb-(c-cc)].setParent(ca,cb);
            q.push({ca,cb-(c-cc), c});
        }else if(cb != 0 && cc != c && cb < (c-cc) && array[ca][0].getParent().empty()){
            array[ca][0].setABC(ca,0,cc+cb);
            array[ca][0].setParent(ca,cb);
            q.push({ca,0,cc+cb});
        }
        //A to C
        if(ca != 0 && cc != c && ca >= (c-cc) && array[ca-(c-cc)][cb].getParent().empty()){
            array[ca-(c-cc)][cb].setABC(ca-(c-cc), cb, c);
            array[ca-(c-cc)][cb].setParent(ca,cb);
            q.push({ca-(c-cc), cb, c});
        }else if(ca != 0 && cc != c && ca < (c-cc) && array[0][cb].getParent().empty()){
            array[0][cb].setABC(0,cb,cc+ca);
            array[0][cb].setParent(ca,cb);
            q.push({0,cb, cc+ca});
        }

    }
    if(solvable == true){
        vector<string> solution;
    while(array[ca][cb].getParent() != base){
        solution.push_back(array[ca][cb].to_string());
        int tempa = ca;
        ca = array[ca][cb].getParent()[0];
        cb = array[tempa][cb].getParent()[1];
    }
    solution.push_back("Initial state. (0, 0, "+to_string(c)+")");
    for(int i = solution.size()-1; i >= 0; i--){
        cout << solution[i] << endl;
    }
    }else{
        cout << "No solution." << endl;
    }
    for (int i = 0; i < a+1; ++i) {
        delete [] array[i];
    }
    // Delete the array itself.
    delete [] array;


}

int main(int argc, char * const argv[]){
    int x, y, a, b, c, ga, gb, gc;
    istringstream iss;
    vector<string> jugs = {"nothing", "A", "B", "C"};
    if(argc != 7){
        cerr << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
        return 1;
    }
    for(int i = 1; i < argc; i++){
        iss.str(argv[i]);
        if((!(iss >> x) || x < 0)){
            if(i <= 3){
                cerr << "Error: Invalid capacity '" << argv[i] << "' for jug "<< jugs[i] <<"." << endl;
                return 1;
            }else if(i > 3){
                cerr << "Error: Invalid goal '" << argv[i] << "' for jug "<< jugs[i-3] << "."<< endl;
                return 1;
            }
        }else if(i == 3 && x <= 0){
            cerr << "Error: Invalid capacity '" << argv[i] << "' for jug C." << endl;
            return 1;
        }
        iss.clear();
    }

    for(int i = 1; i < 4; i++){
        iss.str(argv[i]);
        iss >> x;
        iss.clear();
        iss.str(argv[i+3]);
        iss >> y;
        if(x < y){
            cerr << "Error: Goal cannot exceed capacity of jug "<< jugs[i] << "." << endl;
            return 1;
        }
        iss.clear();
    }
    iss.str(argv[4]);
    iss >> ga;
    iss.clear();
    iss.str(argv[5]);
    iss >> gb;
    iss.clear();
    iss.str(argv[6]);
    iss >> gc;
    iss.clear();
    iss.str(argv[1]);
    iss >> a;
    iss.clear();
    iss.str(argv[2]);
    iss >> b;
    iss.clear();
    iss.str(argv[3]);
    iss >> c;
    iss.clear();
    if(c < ga+gb+gc || c > ga+gb+gc){
        cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
        return 1;
    }
    waterjug(a,b,c,ga,gb,gc);

    
    return 0;
}