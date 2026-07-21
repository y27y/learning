#include<iostream>
#include<algorithm>
using namespace std;
const long long INF = 1e18;

int n;
long long a[220];
long long dpmax[220][220];
long long dpmin[220][220];
long long sum[220]={0};
long long getsum(int l, int r){
    return sum[r] - sum[l - 1];
}

int main(){
    cin >> n;
    int N = 2 * n;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        a[i + n] = a[i];
    }
    for(int i = 1; i <= N; i++){
        sum[i] = sum[i - 1] + a[i];
    }
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            dpmax[i][j] = 0;
            dpmin[i][j] = INF;
        }
        dpmax[i][i] = 0; dpmin[i][i] = 0;
    }

    for(int len = 2; len <= n; len++){
        for(int l = 1; l + len - 1 <= N; l++){
            int r = l + len - 1;
            for(int k = l; k < r; k++){
                dpmax[l][r] = max(dpmax[l][r], dpmax[l][k] + dpmax[k + 1][r] + getsum(l,r));
                dpmin[l][r] = min(dpmin[l][r], dpmin[l][k] + dpmin[k + 1][r] + getsum(l,r));
            }
        }
    }

    long long maxans = -1, minans = INF;
    for(int i = 1; i <= n; i++){
        maxans = max(maxans, dpmax[i][i + n - 1]);
        minans = min(minans, dpmin[i][i + n - 1]);
    }
    cout << minans << endl << maxans;
}