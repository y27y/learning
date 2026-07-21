#include<iostream>
using namespace std;
string add(string a,string b){
    int len=max(a.size(),b.size());
    int sum[len+1]={0};

    for(int i=0;i<len;i++){
        if(i < (int)a.size())
            sum[i]+=a[a.size()-i-1]-'0';
    }
    for(int i=0;i<len;i++){
        if(i < (int)b.size())
            sum[i]+=b[b.size()-i-1]-'0';
    }
    for(int i=0;i<len;i++){
        if(sum[i]>=10){
            sum[i+1]+=1;
            sum[i]%=10;
        }
    }
    string ans;
    if(sum[len]==0) len--;
    for(int i=0;i<len+1;i++){
        ans+=(sum[len-i]+'0');
    }
    return ans;
}


int main(){
    string a,b;
    cin>>a>>b;
    cout<<add(a,b)<<endl;
}