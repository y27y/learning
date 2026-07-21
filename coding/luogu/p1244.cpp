#include<iostream>
using namespace std;
int n,m;
int main(){
    cin >> n >> m;
    cout << (m + 1) * (1 << n);
}