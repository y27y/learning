#include<iostream>
#include<vector>
using namespace std;

int n,m;
vector<vector<int>> dp;//传第m次球在n手里

int solve(){
    for(int i = 1; i <= m; i++){
        for(int j = 0; j < n; j++){
            dp[i][j] = dp[i-1][(j-1+n)%n] + dp[i-1][(j+1)%n];
        }
    }
    return dp[m][0];
}
int main(){
    cin >> n >> m;
    dp.assign(m+1,vector<int>(n,0));
    dp[0][0] = 1;
    cout << solve();
}//eeeeeeasy