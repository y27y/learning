#include<iostream>
#include<vector>
using namespace std;

vector<int> res;
vector<bool> used;
int n;
int time=0;

void DFS(int depth,vector<int>& a,int &time){

    if(depth == n){
        for(int &x : res){
            cout<<x<<" ";
        }
        cout<<endl;
        return;
    }


    for(int i=0;i<n;i++){
        if(used[i] == true){
            continue;
        }
        used[i] = true;
        res.push_back(a[i]);
        //------------------
        DFS(depth+1,a,time);
        //------------------
        res.pop_back();
        used[i] = false;
        time++;
    }
}

int main(){
    cin>>n;
    vector<int> a(n);
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    res.clear();
    used.assign(n,false);

    DFS(0,a,time);
    cout<<time;
}



//BFS
/*
queue<int> q;                // 创建一个队列，用于 BFS 的节点扩展（FIFO 顺序）
q.push(start);               // 把起点 start 入队，开始搜索
dist[start] = 0;             // 起点到自己的距离为 0

while (!q.empty()) {         // 当队列不空时，说明还有节点待扩展
    int u = q.front();       // 取出队首节点 u，准备扩展它的邻居
    q.pop();                 // 弹出队首节点，保证 BFS 队列先进先出

    for (int v : neighbors(u)) {      // 遍历 u 的所有邻居节点 v
        if (dist[v] == -1) {         // 如果 v 没被访问过（距离为 -1 表示未访问）
            dist[v] = dist[u] + 1;   // 更新 v 的最短距离 = u 的距离 + 1
            q.push(v);               // 把 v 入队，等待下一层扩展
        }
    }
}

// BFS 结束后，dist[target] 就是起点到目标节点的最短步数
int ans = dist[target];  
*/