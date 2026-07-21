#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

vector<vector<int>> p;
vector<int> t;
vector<int> indeg;
vector<int> dp;

void BFS(int n){
    queue<int> q;

    for(int i=1;i<=n;i++){
        if(indeg[i] == 0){
            dp[i] = t[i];
            q.push(i);
        }
    }

    while(q.empty() == false){
        int cur = q.front();
        q.pop();
        for(auto &nxt : p[cur]){
            dp[nxt] = max(dp[nxt],dp[cur] + t[nxt]);
            if(--indeg[nxt] == 0){
                q.push(nxt);
            } 
        }
    }

}

int main(){
    int n,x;
    cin>>n;
    t.resize(n+1);
    p.resize(n+1);
    indeg.assign(n+1,0);
    dp.assign(n+1,0);

    for(int i=1;i<=n;i++){
        int a = 0;
        while(cin>>x && x != 0){
            if(a == 1){
                t[i] = x;
            }
            if(a > 1){
                p[x].push_back(i);//i及其后续相连的工作p[i] //pre -> cur
                indeg[i]++;//i的入度
            }
            a++;
        }
    }
    BFS(n);
    int res = 0;
    for(int &ans : dp){
        res = max(ans,res);
    }
    cout<<res;
}

/*
#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

vector<vector<int>> p;
vector<int> t;
int res = -1;

void bfs(int start,int n){
    queue<int> q; 
    vector<int> ans(n+1,0);
    q.push(start);
    ans[start] = t[start];
    while(q.empty() == false){
        int cur = q.front();
        q.pop();
        for(int &i : p[cur]){
            ans[i] = max(ans[i],ans[cur] + t[i]);
            res = max(res,ans[i]);
            q.push(i);
        }
    }
}


int main(){//从尾到头，找时间最长的链
    int n,x;
    cin>>n;
    p.resize(n+1);   t.resize(n+1);   
    for(int i=1;i<=n;i++){  
        int a=0; 
        while(cin>>x && x != 0){
            if(a == 1) t[i] = x;
            if(a > 1) p[i].push_back(x);//cur -> pre//要改
            a++;
        }
    }//操作从1开始，邻接表0开始
    for(int i=1;i<=n;i++){
        bfs(i,n); 
    }
    cout<<res;
}



//明天用入度优化一下，现从入度为0开始存dp[]再bfs
*/