#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int dp(int V,int N,vector<int> v){
    vector<vector<int>> dp(N+1,vector<int>(V+1,0));

    for(int i=1;i<=N;i++){
        for(int j=1;j<=V;j++){
            if(j-v[i-1]<0) dp[i][j]=dp[i-1][j];
            else dp[i][j]=max(dp[i-1][j],dp[i-1][j-v[i-1]]+v[i-1]);
        }
    }
    return dp[N][V];
}

int main(){
    int V,N;
    cin>>V>>N;
    vector<int> v(N);
    for(vector<int>::iterator it=v.begin();it!=v.end();it++){
        cin>>(*it);
    } 
    cout<<V-dp(V,N,v);
}