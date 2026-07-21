#include<iostream>//p1807
#include<vector>
#include<algorithm>
#include<queue>
#include<cstring>
using namespace std;

const long long INF = 1e18;
vector<vector<pair<int,int>>> adj;//邻接表，存储(目标节点, 权重)
vector<int> indeg;//入度（仅计算从1可达的子图）
vector<long long> dp;
int n;

void solve(){
    // 使用拓扑排序+DP求最长路
    vector<int> indeg(n+1, 0);
    vector<bool> reachable(n+1, false);
    
    // 第一步：BFS标记所有从1可达的节点
    queue<int> q;
    q.push(1);
    reachable[1] = true;
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(auto [v, w] : adj[u]){
            if(!reachable[v]){
                reachable[v] = true;
                q.push(v);
            }
        }
    }
    
    // 第二步：计算可达子图中的入度
    for(int u = 1; u <= n; u++){
        if(reachable[u]){
            for(auto [v, w] : adj[u]){
                if(reachable[v]){
                    indeg[v]++;
                }
            }
        }
    }
    
    // 第三步：拓扑排序 + DP
    dp[1] = 0;
    q = queue<int>();
    for(int i = 1; i <= n; i++){
        if(reachable[i] && indeg[i] == 0){
            q.push(i);
        }
    }//这题里可以等价于q.push(1);
    
    while(!q.empty()){
        int u = q.front();
        q.pop();
        
        for(auto [v, w] : adj[u]){
            if(reachable[v]){
                dp[v] = max(dp[v], dp[u] + w);
                if(--indeg[v] == 0){
                    q.push(v);
                }
            }
        }
    }
}

int main(){
    cin>>n;
    int m;
    cin>>m;
    adj.resize(n+1);
    dp.assign(n+1, -INF);
    
    for(int i=0;i<m;i++){
        int x,y,weight;
        cin>>x>>y>>weight;
        adj[x].push_back({y, weight});
    }
    
    solve();
    
    if(dp[n] == -INF){
        cout<<"-1";
    }
    else{
        cout<<dp[n];
    }
}




/*
#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;

const int INF = 1e9;
vector<vector<int>> p;//邻接表
vector<vector<int>> w;//权重
vector<int> indeg;//入度
vector<int> dp;

void kahn(){
    queue<int> q;
    q.push(1);
    dp[1] = 0;
    while(q.empty() == false){
        int cur = q.front();
        q.pop();
        for(auto &nxt : p[cur]){
            dp[nxt] = max(dp[nxt],dp[cur]+w[cur][nxt]);
            if(--indeg[nxt] == 0){
                q.push(nxt);
            }
        }
    }
}

int main(){
    int n,m;
    cin>>n>>m;
    p.resize(n+1);
    dp.assign(n+1, -INF);
    indeg.assign(n+1,0);
    w.assign(n+1,vector<int>(n+1,0));
    for(int i=1;i<=m;i++){
        int x,y,weight;
        cin>>x>>y>>weight;
        p[x].push_back(y);
        indeg[y]++;
        w[x][y] = weight;
    }
    kahn();
    if(dp[n] == -INF){
        cout<<"-1";
    }
    else{
        cout<<dp[n];
    }
}

*///这段死于分叉导致--indeg到不了0