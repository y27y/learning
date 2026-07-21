#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

struct point{
    int x;
    int y;
};

int n,m;
vector<vector<int>> grid;

bool ingrid(point p){
    if(p.x >= 1 && p.y >= 1 && p.x <= n && p.y <= m) return true;
    else return false;
}
void bfs(point start){
    queue<point> q;
    grid[start.x][start.y] = 0;
    q.push(start);

    int dx[8] = {-2,-1,1,2,2,1,-1,-2};
    int dy[8] = {-1,-2,-2,-1,1,2,2,1};

    while(!q.empty()){
        point cur = q.front(); q.pop();
        for(int i=0;i<8;i++){
            point nxt = {cur.x + dx[i] , cur.y + dy[i]};
            if(ingrid(nxt) && grid[nxt.x][nxt.y] == -1){
                grid[nxt.x][nxt.y] = grid[cur.x][cur.y] + 1;
                q.push(nxt);
            }

        }
    }
}

int main(){
    cin>>n>>m;
    point start;
    cin>>start.x>>start.y;
    grid.assign(n+1,vector<int>(m+1,-1));
    bfs(start);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cout<<grid[i][j]<<" ";
        }
        cout<<endl;
    }
}