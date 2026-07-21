#include<iostream>
#include<vector>
using namespace std;

struct magic{
    int x;
    int y;
    int r;
    int direction;
};

int main(){
    int n,m; int count=1;
    vector<vector<int>> grid;
    cin >> n >> m;
    grid.resize(n, vector<int>(n, 0));
    vector<vector<int>> temp;
    temp.resize(n, vector<int>(n, 0));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            grid[i][j]=count;
            count++;
        }
    }
    vector<magic> mag(m);
    for(int i=0;i<m;i++){
        cin>>mag[i].x>>mag[i].y>>mag[i].r>>mag[i].direction;
        mag[i].x--;  mag[i].y--;
    }
 for (int i = 0; i < m; i++) {
    int cx = mag[i].y; // 列
    int cy = mag[i].x; // 行
    int r  = mag[i].r;
    for (int j = cy - r; j <= cy + r; j++) {
        for (int k = cx - r; k <= cx + r; k++) {
            int dx = k - cx;
            int dy = j - cy;
            int src_x, src_y;

            if (mag[i].direction == 0) { // 顺时针
                src_x = cx + dy;
                src_y = cy - dx;
            } 
            else { // 逆时针
                src_x = cx - dy;
                src_y = cy + dx; 
            }

            temp[j][k] = grid[src_y][src_x];
        }
    }
    for (int j = cy - r; j <= cy + r; j++)
        for (int k = cx - r; k <= cx + r; k++)
            grid[j][k] = temp[j][k];
}

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<grid[i][j]<<" ";
        }
        cout<<endl;
    }
    
}