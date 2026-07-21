#include<iostream>
#include<vector>
using namespace std;

vector<vector<long long>> dp;
vector<vector<int>> root;
int n;

long long solve(int l, int r){
    if(l > r){
        return 1;
    }    
    if (dp[l][r] != -1){
        return dp[l][r];
    }
    if(l == r){
        root[l][r] = l;
        return dp[l][r];
    }
    long long best = 0;
    for(int i = l; i <= r; i++){
        long long left = solve(l,i - 1);
        long long right = solve(i + 1,r);
        long long val = left * right + dp[i][i]; 
        if(val > best){
            best = val;
            root[l][r] = i;
        }
    }
    dp[l][r] = best;
    return dp[l][r];
}

void print_tree(int l, int r){
    if(l > r){
        return;
    }
    int rot = root[l][r];
    cout << rot << " ";
    print_tree(l,rot - 1);
    print_tree(rot + 1,r);
}

int main(){
    cin >> n;
    dp.assign(n + 1, vector<long long>(n + 1, -1));
    root.assign(n + 1, vector<int>(n + 1, 0));
    for(int i = 1; i <= n; i++){
        cin >> dp[i][i];
        root[i][i] = i;
    }

    int ans = solve(1,n);
    cout << ans << endl;
    print_tree(1,n);
}