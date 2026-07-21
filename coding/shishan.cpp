#include<iostream>
#include<vector>
using namespace std;
vector<int> ans;
vector<bool> visited;
bool haschild(int now,int n,const vector<vector<bool>>& map){//now与1~n的点还有没有能互通的
    for(int i=1;i<=n;i++){
        if(map[now][i] == true && visited[i] == false){
            return true;
        }
    }
    return false;
}

void dfs(int a,int now,int n,const vector<vector<bool>>& map){
    /*if(haschild(now,n,map) == false){
        return;
    }*///hhh，根本不需要
    for(int i=1;i<=n;i++){
        if(map[now][i] == true && visited[i] == false){
            visited[i] = true;
            dfs(a,i,n,map);
            visited[i] = false;
            ans[a] = max(ans[a],i);
        }
    }
}

int main(){
    int n,m;
    int U,V;
    cin>>n>>m;
    vector<vector<bool>> map(n+1,vector<bool>(n+1,false));
    for(int i=0;i<m;i++){
        cin>>U>>V;
        map[U][V] = true;
    }//邻接矩阵存
    ans.resize(n+1);
    for(int i=1;i<=n;i++){
        ans[i]=i;
    }
    visited.assign(n+1,false);
    for(int i=1;i<=n;i++){
        dfs(i,i,n,map);
        cout<<ans[i]<<" ";
    }
}

//B3862