#include <iostream>//区间dp
#include <algorithm>
using namespace std;

int n;
long long a[220];
long long dp[220][220];

int main(){
    cin >> n;
    int N = 2 * n;

    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++){
        a[i + n] = a[i];
    }

    for(int len = 2; len <= n; len++){
        for(int l = 1; l + len - 1 <= N; l++){
            int r = l + len - 1;
            for(int k = l; k < r; k++){
                dp[l][r] = max(dp[l][r],dp[l][k] + dp[k+1][r] + a[l] * a[k+1] * a[r+1]);
            }
        }
    }

    long long ans = 0;
    for(int i = 1; i <= n; i++){
        ans = max(ans, dp[i][i + n - 1]);
    }

    cout << ans;
    return 0;
}
/*
#include<iostream>
#include<algorithm>
using namespace std;

struct point{
    int head;
    int tail;
};

int n;
point p[220];
int temp[220];
long long dp[220][220];

int main(){
    cin >> n;
    int N = 2 * n;
    for(int i = 1; i <= n; i++){
        cin >> temp[i];
        p[i].head = temp[i];
        p[i - 1].tail = temp[i];
    }
    p[n].tail = temp[1];
    for(int i = 1; i <= n; i++){
        p[i + n] = p[i];
    }

    for(int l = 1; l <= N; l++){
        dp[l][l+1] = p[l].head * p[l].tail * p[l + 1].tail;
    }

    for(int len = 3; len <= n; len++){
        for(int l = 1; l + len -1 <= N; l++){
            int r = l + len - 1;
            dp[l][r] = max(dp[l][r], dp[l][r - 1] + p[l].head * p[r - 1].tail * p[r].tail);
        }
    }
    long long dpmax = 0;
    for(int i = 1; i <= n; i++){
        dpmax = max(dpmax, dp[i][i + n - 1]);
    }

    cout << dpmax;
//现在是把point复制一遍一直向右走，忽略了往左
}
*/