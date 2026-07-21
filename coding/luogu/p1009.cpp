#include <bits/stdc++.h>
using namespace std;

string add(const string& a, const string& b) {
    int i = a.size() - 1;
    int j = b.size() - 1;
    int carry = 0;
    string res;

    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += a[i--] - '0';
        if (j >= 0) sum += b[j--] - '0';

        res.push_back(sum % 10 + '0');
        carry = sum / 10;
    }

    reverse(res.begin(), res.end());
    return res;
}

string multiply(const string& a, const string& b) {
    if (a == "0" || b == "0") return "0";

    int n = a.size(), m = b.size();
    vector<int> res(n + m, 0);

    for (int i = n - 1; i >= 0; i--) {
        for (int j = m - 1; j >= 0; j--) {
            int mul = (a[i] - '0') * (b[j] - '0');
            int sum = mul + res[i + j + 1];
            res[i + j + 1] = sum % 10;
            res[i + j] += sum / 10;
        }
    }

    string ans;
    int i = 0;
    while (i < n + m && res[i] == 0) i++; // 去前导零
    for (; i < n + m; i++) ans += res[i] + '0';

    return ans.empty() ? "0" : ans;
}

bool mem[100]={0};
string cache[100];
string factorial(int n){
    if(n==1) return "1";
    else{
        if(mem[n]==1) return cache[n];
        else{
            cache[n]=multiply(to_string(n),factorial(n-1));
            mem[n]=1;
            return cache[n];
        }
    }
}

int main() {
    int n;
    cin>>n;
    string ans="0";
    for(int i=1;i<=n;i++){
        ans=add(ans,factorial(i));
    }
    cout<<ans;
}
