/*#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

struct point{
    double x;
    double y;
};
int n;
vector<point> p;
vector<vector<double>> v;
vector<bool> visited;
double sum = 0; double ans = 1000000;
void dfs(int now,int depth){
    if (sum >= ans) return;//剪枝
    if(depth == n){
        ans = min(ans,sum);
        return;
    }
    for(int i=1;i<=n;i++){
        if(visited[i]){
            continue;
        }
        sum += v[now][i];
        visited[i] = true;
        dfs(i,depth+1);
        sum -= v[now][i];
        visited[i] = false;
    }   
}

int main(){
    cin>>n;
    p.resize(n+1);
    v.assign(n+1,vector<double>(n+1,0));
    visited.assign(n+1,false);
    for(int i=1;i<=n;i++){
        cin>>p[i].x>>p[i].y;
    }
    p[0].x = 0; p[0].y = 0;
    for(int i=0;i<=n;i++){
        for(int j=i;j<=n;j++){
            double dx = p[i].x - p[j].x;
            double dy = p[i].y - p[j].y;
            v[i][j] = sqrt(dx * dx + dy * dy);
            v[j][i] = v[i][j];
        }
    }

    visited[0] = true;
    dfs(0,0);
    printf("%.2f",ans);
}*///dfs最多n = 15

//状压dp

#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
#define INF 10000000
struct point{
    double x;
    double y;
};
int n;
vector<point> p;
vector<vector<double>> v;
vector<vector<double>> dp;
vector<double> start;


int getbit(const int a,const int b){ 
    return (a >> b) & 1; 
}//a在二进制下的第b位

void solve(){
    for(int i = 1; i < (1 << n); i++){
        for(int j = 0; j < n; j++){
            if(getbit(i,j) == 0){
                continue;
            }
            else{
                int past_i,past_j;
                past_i = i - (1 << j);//状态转移之前的状态
                for(int k = 0; k < n; k++){
                    if(getbit(past_i,k) == 1){
                        past_j = k;//转移之前的位置
                        dp[i][j] = min(dp[i][j] , dp[past_i][past_j] + v[past_j][j]);
                    }
                }
            }
        }
    }
}

int main(){
    cin >> n;
    p.resize(n);
    start.resize(n);
    v.assign(n,vector<double>(n,0));
    dp.assign(1 << n,vector<double>(n,INF));
    for(int i = 0; i < n; i++){
        cin >> p[i].x >> p[i].y;
    }

    for(int i = 0; i < n; i++){
        start[i] = sqrt(p[i].x * p[i].x + p[i].y * p[i].y);
        for(int j = i; j < n; j ++){
            double dx = p[i].x - p[j].x;
            double dy = p[i].y - p[j].y;
            v[i][j] = sqrt(dx * dx + dy * dy);
            v[j][i] = v[i][j];
        }
    }
    //dp初始化
    for(int i = 0; i < n; i++){
        dp[1 << i][i] = start[i];
    }
    solve();
    double ans = INF;
    for(int i = 0; i < n; i++){
        ans = min(ans,dp[(1 << n) - 1][i]);
    }
    printf("%.2lf",ans);
}
//2026.2.12//2:13 a.m 终于ac了