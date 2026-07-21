#include<iostream>
#include<vector>
using namespace std;
typedef struct item{
    int x;
    int y;
    int dirx=-1;
    int diry=0;
}item;//x->行，y->列
int main(){
    item cow,farmer;
    int time=0;
    char grid[10][10];
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            cin>>grid[i][j];
            if(grid[i][j]=='C'){
                cow.x=i;
                cow.y=j;
            }
            if(grid[i][j]=='F'){
                farmer.x=i;
                farmer.y=j;
            }
        }
    }

    while(1){
        if(cow.x==farmer.x && cow.y==farmer.y){
            cout<<time<<endl;
            return 0;
        }
        else{
            if(cow.x+cow.dirx>=0 && cow.x+cow.dirx<10 && cow.y+cow.diry>=0 && cow.y+cow.diry<10 && (grid[cow.x+cow.dirx][cow.y+cow.diry] != '*')){
                grid[cow.x+cow.dirx][cow.y+cow.diry] = 'C';
                grid[cow.x][cow.y] = '.';
                cow.x+=cow.dirx;   cow.y+=cow.diry;
            }
            else{
                if(cow.dirx==0 && cow.diry==-1){cow.dirx=-1; cow.diry=0;}
                else if(cow.dirx==1 && cow.diry==0){cow.dirx=0; cow.diry=-1;}
                else if(cow.dirx==0 && cow.diry==1){cow.dirx=1; cow.diry=0;}
                else if(cow.dirx==-1 && cow.diry==0){cow.dirx=0; cow.diry=1;}
            }

            if(farmer.x+farmer.dirx>=0 && farmer.x+farmer.dirx<10 && farmer.y+farmer.diry>=0 && farmer.y+farmer.diry<10 && grid[farmer.x+farmer.dirx][farmer.y+farmer.diry] != '*'){
                grid[farmer.x+farmer.dirx][farmer.y+farmer.diry] = 'F';
                grid[farmer.x][farmer.y] = '.';
                farmer.x+=farmer.dirx;   farmer.y+=farmer.diry;
            }
            else{
                if(farmer.dirx==0 && farmer.diry==-1){farmer.dirx=-1; farmer.diry=0;}
                else if(farmer.dirx==1 && farmer.diry==0){farmer.dirx=0; farmer.diry=-1;}
                else if(farmer.dirx==0 && farmer.diry==1){farmer.dirx=1; farmer.diry=0;}
                else if(farmer.dirx==-1 && farmer.diry==0){farmer.dirx=0; farmer.diry=1;}
            }
        }
        time++;
        if(time>1145154){
            cout<<0<<endl;
            return 0;
        }
    }
}