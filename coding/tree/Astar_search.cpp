#include <iostream>//p1746
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct point{
    int x;
    int y;
    bool operator==(const point& other) const{
        return x == other.x && y == other.y;
    }
    bool operator<(const point& other) const{
        if(x != other.x) return x < other.x;
        return y < other.y;
    }
};

vector<vector<int>> mp;
vector<vector<bool>> visited;
vector<vector<int>> length;

// 计算曼哈顿距离
int heuristic(point cur, point stop){
    return abs(cur.x - stop.x) + abs(cur.y - stop.y);
}

void astar(int n, point start, point stop){
    // 优先队列 f 最小在前，pair: <f值, point>
    priority_queue<pair<int, point>, vector<pair<int, point>>, greater<pair<int, point>>> pq;
    pq.push({heuristic(start, stop), start});
    visited[start.x][start.y] = true;
    length[start.x][start.y] = 0;

    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    while(!pq.empty()){
        auto node = pq.top(); pq.pop();
        point cur = node.second;

        if(cur == stop) return;

        for(int i = 0; i < 4; i++){
            point next = {cur.x + dx[i], cur.y + dy[i]};
            if(next.x >= 1 && next.x <= n && next.y >= 1 && next.y <= n 
               && mp[next.x][next.y] == 0 && !visited[next.x][next.y]){
                length[next.x][next.y] = length[cur.x][cur.y] + 1;

                int f = length[next.x][next.y] + heuristic(next, stop);

                pq.push({f, next});
                visited[next.x][next.y] = true;
            }
        }
    }
}

int main(){
    int n;
    string str;
    cin >> n;
    mp.resize(n+1, vector<int>(n+1));
    visited.assign(n+1, vector<bool>(n+1, false));
    length.assign(n+1, vector<int>(n+1, 0));

   for(int i=1;i<=n;i++){
        cin>>str;
        for(int j=1;j<=n;j++){
            mp[i][j] = str[j-1] - '0';
        }
    }

    point start, stop;
    cin >> start.x >> start.y >> stop.x >> stop.y;

    astar(n, start, stop);

    if(!visited[stop.x][stop.y]) cout << -1 << endl;
    else cout << length[stop.x][stop.y] << endl;
}