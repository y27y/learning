#include<iostream>
#include<algorithm>
using namespace std;
int mem[1001]={0};
int solve(int n){
    if(n==1) return 1;
    else{
        if(mem[n]!=0) return mem[n];
        else{
            int sum=1;
            for(int i=1;i<=n/2;i++){
                sum+=solve(i);
            }  
            return mem[n] = sum;
        }
    }
}

int main(){
    int n;
    cin>>n;
    cout<<solve(n);
}