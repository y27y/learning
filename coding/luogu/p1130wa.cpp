#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int roll(int n,int M){
    if(n-1==0) return M;
    return n-1;
}
int solve(int N,int M,vector<vector<int>>& time){
    vector<vector<int>> dp(M+1,vector<int>(N+1,0));
    for(int i=1;i<=N;i++){
        for(int j=1;j<=M;j++){
            dp[j][i]=min(dp[j-1][i]+time[j-1][i-1],dp[j-1][roll(i,M)]+time[j-1][i-1]);
        }
    }
    return dp[M][N];
}

int main(){
    int N,M;
    cin>>N>>M;
    vector<vector<int>> time(M,vector<int>(N,0));
    for(int i=0;i<M;i++){
        for(int j=0;j<N;j++){
            cin>>time[i][j];
        }
    }
    cout<<solve(N,M,time);
}