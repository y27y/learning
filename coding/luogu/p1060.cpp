#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int solve(int n,int m,vector<int>& v,vector<int>& p){
    if(n==0 || m==0) return 0;
    if(m<v[n-1]) return solve(n-1,m,v,p);
    return max(solve(n-1,m,v,p),solve(n-1,m-v[n-1],v,p)+v[n-1]*p[n-1]);
}

int main(){
    int n,m;
    cin>>m>>n;
    vector<int> v(n);
    vector<int> p(n);
    for(int i=0;i<n;i++){
        cin>>v[i]>>p[i];
    }
    cout<<solve(n,m,v,p);
}