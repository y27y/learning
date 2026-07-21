#include<iostream>
#include<set>
#include<algorithm>
#include<vector>
using namespace std;

int n,k;
int sum = 0;
int cnt = 0;
void solve(int depth, int last) {
    if (depth == k) {
        if (sum == n){
            cnt++;
        }
        return;
    }
    int remain = k - depth;
    for (int i = last; i <= n; i++) {
        if (sum + i > n) break;
        // 剩余最小可能
        if (sum + i + (remain - 1) * i > n) break;
        // 剩余最大可能
        if (sum + i + (remain - 1) * n < n) continue;
        sum += i;
        solve(depth + 1, i);
        sum -= i;
    }
}

int main(){
    cin >> n >> k;
    solve(0,1);
    cout << cnt;
}



/*
int n,k;
int sum = 0;
set<multiset<int>> a;
multiset<int> ms;

void solve(int depth){
    if(depth >= k){
        if(sum == n && depth == k){    
            a.insert(ms);
        }
        return;
    }

    for(int i = 1; i <= n; i++){
        sum += i;
        ms.insert(i);
        solve(depth + 1);
        auto it = ms.find(i);
        if (it != ms.end()){
            ms.erase(it);
        }        
        sum -= i;
    } 
} 

int main(){
    cin >> n >> k;
    solve(0);
    cout << a.size();
}*/ //第一版屎山