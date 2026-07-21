#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;

long long f(int N, int K, string& s){//长度N，k个*
    vector<vector<long long>> dp(N+1, vector<long long>(K+1, 0));
    vector<vector<long long>> num(N+1,vector<long long>(N+1,0));//从i-j的数字大小

    for(int i=1;i<=N;i++){
        for(int j=i;j<=N;j++){
            num[i][j]=stoll(s.substr(i,j-i+1));
            dp[i][0]=num[1][i];
        }
    }


    for(int i=1;i<=N;i++){
        for(int j=1;j<=K;j++){
            if(j>=i) break;
            for(int t=j-1;t<=i-1;t++){//j-1上都是0
                dp[i][j]=max(dp[i][j], dp[t][j-1]*num[t+1][i]);
            }
        }
    }

    return dp[N][K];
}

int main(){
    int N,K;
    string s;
    cin>>N>>K;
    cin>>s;
    s=" "+s;
    cout<<f(N,K,s)<<endl;
}
