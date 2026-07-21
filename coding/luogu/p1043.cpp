#include<iostream>
#include<vector>
#include<queue>
using namespace std;
const long long INF = 1e18;

int n,m;
int a[210];
long long sum[210]={0};//0-2n的和
long long dpmin[210][210][11];
long long dpmax[210][210][11];
//            [开始][结束][切的份数]

long long getsum(int l, int r){
    long long x = sum[r] - sum[l - 1];
    return (x % 10 + 10) % 10;
}

int main(){
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        a[i + n] = a[i];
    }

    for(int i = 1; i <=2 * n; i++) {
        sum[i] = sum[i - 1] + a[i];
    }//前缀和

    for(int l = 1; l <= 2 * n; l++){
        for(int r = 1; r <= 2 * n; r++){
            for(int k = 1; k <= m; k++){
                dpmin[l][r][k] = INF;
                dpmax[l][r][k] = -INF;
            }
        }
    }

    for(int l = 1; l <= 2 * n; l++){
        for(int r = l; r <= 2 * n; r++){
            long long val = getsum(l,r);
            dpmin[l][r][1] = val;
            dpmax[l][r][1] = val;
        }
    }

    for(int len = 2; len <= n; len++){
        for(int l = 1; l + len - 1 <= 2 * n; l++){
            int r = l + len - 1;
            for(int k = 2; k <= m; k++){
                for(int p = l; p < r; p++){
                    dpmax[l][r][k] = max(dpmax[l][r][k], dpmax[l][p][k - 1] * dpmax[p + 1][r][1]);
                    dpmin[l][r][k] = min(dpmin[l][r][k], dpmin[l][p][k - 1] * dpmin[p + 1][r][1]);
                }
            }
        }
    }
    
    long long ansmin = INF, ansmax = -INF;
    for(int i = 1; i <= n; i++){
        ansmin = min(ansmin, dpmin[i][i+n-1][m]);
        ansmax = max(ansmax, dpmax[i][i+n-1][m]);
    }

    cout << ansmin << endl << ansmax;
}
