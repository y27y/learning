#include<iostream>
#include<string>

using namespace std;
void score(int n,string s){
    int win1=0,win2=0;
    int i=0;
    while(s[i]!='E'){
        if(s[i]=='W') win1++;
        else if(s[i]=='L') win2++;
        if((win1>=n || win2>=n) && (abs(win1-win2)>=2)){
            cout<<win1<<":"<<win2<<endl;
            win1=0;
            win2=0;
        }
        i++;
    }
    cout<<win1<<":"<<win2<<endl;
}
int main(){
    string s;
    char c;
    while(cin>>c){
        s+=c;       
        if(c=='E') break;
    }
    score(11,s);
    cout<<"\n";
    score(21,s);
}
/*WWWWWWWWWWWWWWWWWWWW
WWLWE*/