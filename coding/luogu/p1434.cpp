#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int r,c;
vector<vector<int>> grid;
vector<vector<int>> length;
vector<vector<bool>> visited;
int dx[4] = {0,0,1,-1};
int dy[4] = {1,-1,0,0};

bool ingrid(int x,int y){
    if(x >= 1 && x <= r && y >= 1 && y <= c) return true;
    else return false;
}

int dfs(int x,int y){
    if(visited[x][y]) return length[x][y];
    for(int i=0;i<4;i++){
        int nx = x + dx[i];
        int ny = y + dy[i];
        if(ingrid(nx,ny) && grid[nx][ny] < grid[x][y]){
            dfs(nx,ny);
            length[x][y] = max(length[x][y],length[nx][ny] + 1);
        }
    }          
    visited[x][y] = true;
    return length[x][y];
}

int main(){
    cin>>r>>c;
    grid.resize(r+1,vector<int>(c+1));
    length.assign(r+1,vector<int>(c+1,1));
    visited.assign(r+1,vector<bool>(c+1,false));
    for(int i=1;i<=r;i++){
        for(int j=1;j<=c;j++){
            cin>>grid[i][j];
        }
    }

    int ans=1;
    for(int i=1;i<=r;i++){
        for(int j=1;j<=c;j++){
            dfs(i,j);
            ans = max(ans,length[i][j]);
        }
    }
    cout<<ans;
}