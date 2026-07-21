#include<iostream>
#include<vector>
using namespace std;
int vs[5][5] = {{0, 0, 1, 1, 0}, {1, 0, 0, 1, 0}, {0, 1, 0, 0, 1}, {0, 0, 1, 0, 1}, {1, 1, 0, 0, 0}};
int main(){
    int n,na,nb;
    cin>>n>>na>>nb;
    vector<int> a(na),b(nb);
    for(int i=0;i<na;i++) cin>>a[i];
    for(int i=0;i<nb;i++) cin>>b[i];
    int score_a=0,score_b=0;
    for(int i=0;i<n;i++){
        score_a+=vs[a[i%na]][b[i%nb]];
        score_b+=vs[b[i%nb]][a[i%na]];
    }
    cout << score_a << " " << score_b;
}