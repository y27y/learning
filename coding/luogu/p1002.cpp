#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
long long cache[101][101];
bool mem[101][101];
bool isblocked(int x,int y,int x1,int y1){
    if((x==x1 && y==y1) || (x==x1+2 && y==y1+1) || (x==x1+2 && y==y1-1) || (x==x1+1 && y==y1+2) || (x==x1+1 && y==y1-2) || (x==x1-1 && y==y1+2) || (x==x1-1 && y==y1-2) || (x==x1-2 && y==y1+1) || (x==x1-2 && y==y1-1))
        return true;
    else return false;
}

long long solve(int x,int y,int x1,int y1){
    if(x < 0 || y < 0) return 0;
    if(isblocked(x,y,x1,y1)) return 0; 
    if(x==0 && y==0) return 1;
    
    if(mem[x][y]) return cache[x][y];
    mem[x][y] = true;
    cache[x][y] = solve(x-1,y,x1,y1)+solve(x,y-1,x1,y1);
    return cache[x][y];
}//不开long long见祖宗

int main(){
    int x,y,x1,y1;
    cin>>x>>y>>x1>>y1;
    cout<<solve(x,y,x1,y1);
}