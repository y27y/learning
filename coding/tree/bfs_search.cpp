#include<iostream>//p17446
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

struct point{
    int x;
    int y;
    bool operator==(const point& other) const{
        return this->x == other.x && this->y == other.y;
    }
};
vector<vector<int>> mp;
vector<vector<bool>> visited;
vector<vector<int>> length;

void bfs(int n,point start,point stop){
    queue<point> q;
    q.push(start);
    visited[start.x][start.y] = true;

    while(!q.empty()){
        point cur = q.front();
        q.pop();
        if(cur == stop){
            return;
        } 
        else{
            vector<point> directions = {{-1,0},{1,0},{0,-1},{0,1}};
            for(auto dir : directions){
                point next = {cur.x + dir.x, cur.y + dir.y};
                if(next.x >= 1 && next.x <= n && next.y >= 1 && next.y <= n && mp[next.x][next.y] == 0 && !visited[next.x][next.y]){
                    visited[next.x][next.y] = true;
                    length[next.x][next.y] = length[cur.x][cur.y] + 1;
                    q.push(next);
                }
            }
        }
    }

}

int main(){
    int n;
    cin>>n;
    string str;
    mp.resize(n+1,vector<int>(n+1));
    visited.assign(n+1,vector<bool>(n+1,false));
    length.assign(n+1,vector<int>(n+1,0));
    for(int i=1;i<=n;i++){
        cin>>str;
        for(int j=1;j<=n;j++){
            mp[i][j] = str[j-1] - '0';
        }
    }
    point start,stop;
    cin>>start.x>>start.y>>stop.x>>stop.y;

    bfs(n,start,stop);

    if(!visited[stop.x][stop.y]){
        cout<<-1<<endl;
    }
    else{
        cout<<length[stop.x][stop.y]<<endl;
    }
}