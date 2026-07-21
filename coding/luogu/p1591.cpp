#include <iostream>
#include <cstring>
using namespace std;
int read(int a[],string& s){
    int len=0;
    for(int i=s.size()-1;i>=0;i--){
        a[len++]=s[i]-'0';
    }
    return len;
}
int read(int a[], int x) {
    int len = 0;
    if (x == 0) return a[len++] = 0, len;
    while (x) { a[len++] = x % 10; x /= 10; }
    return len;
}
void print(int len,int c[]){
    for(int i=len-1;i>=0;i--){
        cout<<c[i];
    }
}
int multiply(int a[], int la, int b[], int lb, int c[]) {
    memset(c, 0, sizeof(int) * (la + lb));
    for(int i=0;i<la;i++){
        for(int j=0;j<lb;j++){
            c[i+j]+=a[i]*b[j];
        }
    }
    int lc=la+lb;
    for(int i=0;i<lc;i++){
        c[i+1]+=c[i]/10;
        c[i]%=10;
    }
    while (lc > 1 && c[lc - 1] == 0) lc--;
    return lc;
}


int main(){
    int t;
    cin>>t;
    int n[100],k[100];
    for(int i=0;i<t;i++){
        cin>>n[i]>>k[i];
    }
    int a[10000], b[10000], c[10000];
    
    for(int j=0;j<t;j++){
    int la = read(a, 1);  // 初始化为1
    
    // 计算 n!
    for(int i = 2; i <= n[j]; i++) {
        int lb = read(b, i);
        la = multiply(a, la, b, lb, c);
        memcpy(a, c, sizeof(int) * la);
    }

        int count=0;
        for(int i=0;i<la;i++){
            if(a[i]==k[j]) count++;
        }
        cout<<count<<endl;
    }
    return 0;
}