#include<iostream>
#include<vector>
#include<algorithm>
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

string multiply(string a,string b){
    if(a == "0" or b == "0") return "0";
    int len_a=a.size(),len_b=b.size();
    string partial[len_b];//每位相乘的结果
    int sum[len_a+1]={0};
    for(int j=0;j<len_b;j++){
    sum[len_a]=0;
    for(int i=0;i<len_a;i++){
        sum[i]=(b[len_b-j-1]-'0')*(a[len_a-i-1]-'0');
    }

    for(int i=0;i<len_a;i++){
        if(sum[i]>=10){
            sum[i+1]+=(sum[i]/10);
            sum[i]%=10;
        }
    }

    if(sum[len_a]==0){
    for(int i=0;i<len_a;i++){
        partial[j]+=(sum[len_a-i-1]+'0');
    }
    }
    else{
        for(int i=0;i<len_a+1;i++){
        partial[j]+=(sum[len_a-i]+'0');
    }
    }

    for(int i=len_b-j;i<len_b;i++){
        partial[j]+='0';
    }
    }

    string ans;
    for(int i=0;i<len_b;i++){
        ans=add(ans,partial[i]);
    }
    return ans;
}

int main(){
    string a,b;
    cin>>a>>b;
    cout<<multiply(a,b)<<endl;
}