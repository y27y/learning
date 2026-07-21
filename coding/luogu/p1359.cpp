#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int res=1e9;
vector<int> dp;
int solve(int n,vector<vector<int>>& r,int res){
    if(n==1){
        return 0;
    }
    if(dp[n] != -1) return dp[n];
    for(int i=1;i<=n-1;i++){       
       res=min(solve(n-i,r,res)+r[n-i][n],res);
    }
    dp[n] = res;
    return res;
}

int main(){
    int n;
    cin>>n;
    vector<vector<int>> r(n+1, vector<int>(n+1,0));
    for(int i=1;i<=n;i++){//i->j的价格
        for(int j=i+1;j<=n;j++){
            cin>>r[i][j];
        }
    }
    dp.assign(n+1,-1);
    cout<<solve(n,r,res);
}