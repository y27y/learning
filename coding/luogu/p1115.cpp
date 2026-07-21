#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int solve(int n,vector<int>& a){
    int ans=-1e9;
    int cur=a[0];
    for (int i = 1; i < a.size(); i++) {
        cur = max(cur + a[i], a[i]);
        ans = max(ans, cur);
    }
    return ans;
}

int main(){
    int n;
    cin>>n;
    vector<int> a(n,0);
    for(int i=0;i<n;i++) cin>>a[i];
    cout<<solve(n-1,a)<<endl;
}
