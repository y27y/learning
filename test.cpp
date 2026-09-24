#include "./ZaoLunZi/data structure/queue/queue.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <vector>
//--------------
#include <iterator>
#include <numeric>
using namespace std;
const char* cp("Hello World!");

int add(int x, int y) {
    return x + y;
}

void test_function() {
    int v = 42;
    auto f = [v]() mutable { return ++v; };
    v = 0;
    auto j = f();
    cout << j;
}

int main() {
    // int (*ADD)(int a, int b) = add;
    vector<int> v = {1, 2, 3, 4};
    ostream_iterator<int> out_iter(cout);
    copy(v.cbegin(), v.cend(), out_iter);
    cout << endl;
    cout;
    // istream_iterator<int> in(cin), eof;
    // cout << accumulate(in, eof, 0, ADD);
    // while (in != eof) {
    //     v.push_back(*in++);
    // }
    // for(auto &x : v){
    //     cout << x << " ";
    // }

    // test_function();
    //  auto f = [](int a, int b) -> int {return a + b;};
    //  int c = f(1, 2);
    //  cout << c << endl;
    //  cout << (10 >> 1);
    //  vector<int> v = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    //  string s;

    // my_queue<int> q;

    // q.push(1);
    // q.push(2);
    // replace(v.begin(), v.end(), 0, 9);

    // for (auto& x : v) {
    //     cout << x;
    // }
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
