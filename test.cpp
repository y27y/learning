#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "./ZaoLunZi/data structure/queue/queue.hpp"
using namespace std;
const char* cp("Hello World!");

int add(int x, int y){
    return x + y;
}

int main(){
    vector<int> v = {0,1,2,3,4,5,6,7,8,9};
    string s;
     
    my_queue<int> q;
    q.push(1);
    q.push(2);
    replace(v.begin(), v.end(), 0, 9);
    
    for(auto &x : v){
        cout << x;
    }
}
// ifstream is("test.txt", ios::in);
// string line;

// while(getline(is, line)){
//     stringstream ss(line);
//     string word;
//     while(ss >> word){
//         cout << word << endl;
//     }
// }
