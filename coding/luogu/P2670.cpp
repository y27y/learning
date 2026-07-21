#include<iostream>
using namespace std;

int main(){
    char canvus[100][100];
    int n,m;
    cin>>n>>m;//n行m列
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>canvus[i][j];
        }
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(canvus[i][j]=='?'){
                int count = 0;
                if(i-1>=0 && canvus[i-1][j]=='*') count++;
                if(i+1<n && canvus[i+1][j]=='*') count++;
                if(j-1>=0 && canvus[i][j-1]=='*') count++;
                if(j+1<m && canvus[i][j+1]=='*') count++;
                if(i-1>=0 && j-1>=0 && canvus[i-1][j-1]=='*') count++;
                if(i-1>=0 && j+1<m && canvus[i-1][j+1]=='*') count++;
                if(i+1<n && j-1>=0 && canvus[i+1][j-1]=='*') count++;
                if(i+1<n && j+1<m && canvus[i+1][j+1]=='*') count++;
                canvus[i][j]='0'+count;
            }
        }
    }

     for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cout<<canvus[i][j];
        }
        cout<<endl;
    }
}