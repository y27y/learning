#include<iostream>
#include<algorithm>
#include <vector>
using namespace std;
int dp(int t[],int v[],int T,int M){
    vector<vector<int>> dp(M+1,vector<int>(T+1));
    for(int i=1;i<=M;i++){
        for(int j=1;j<=T;j++){
            if(j-t[i-1]<0) dp[i][j]=dp[i-1][j];
            else{
                dp[i][j]=max(dp[i-1][j],dp[i-1][j-t[i-1]]+v[i-1]);
            }
        }
    }
    return dp[M][T];
}


int main(){
    int T,M;
    cin>>T>>M;
    int t[101],v[101];
    for(int i=0;i<M;i++){
        cin>>t[i]>>v[i];
    }
    cout<<dp(t,v,T,M);
}