/*#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

long long mypow(int a,int b){
    long long res=1;
    for(int i=0;i<b;i++){
        res*=a;
    }
    return res;
}

long long frow(int n,int m,vector<vector<int>> &a){//第n行的最大和
    vector<vector<long long>> dp(m,vector<long long>(m,0));
    for(int i=0;i<m;i++){
        dp[i][i]=(a[n][i]*(mypow(2,m)));
    }
    for(int right=1;right<=m-1;right++){
        for(int left=right-1;left>=0;left--){
            dp[left][right]=max(a[n][left] * (mypow(2,m-right+left)) + dp[left+1][right],a[n][right] * (mypow(2,m-right+left)) + dp[left][right-1]);
        }
    }
    return dp[0][m-1];
}
 
int main(){
    int n,m;
    cin>>n>>m;
    vector<vector<int>> a(n,vector<int>(m));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>a[i][j];
        }
    }
    long long sum=0;
    for(int i=0;i<n;i++){
        sum+=frow(i,m,a);
    }
    cout<<sum<<endl;
    return 0;
}*/



#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// 高精度加法：a + b
string add(const string &a, const string &b) {
    string res = "";
    int carry = 0;
    int i = a.size() - 1, j = b.size() - 1;
    while(i >= 0 || j >= 0 || carry) {
        int x = i >= 0 ? a[i--] - '0' : 0;
        int y = j >= 0 ? b[j--] - '0' : 0;
        int sum = x + y + carry;
        carry = sum / 10;
        res.push_back(sum % 10 + '0');
    }
    reverse(res.begin(), res.end());
    return res;
}

// 高精度乘法：a * b（字符串 × 字符串）
string mul(const string &a, const string &b) {
    if(a == "0" || b == "0") return "0";
    vector<int> res(a.size() + b.size(), 0);

    for(int i = a.size() - 1; i >= 0; i--) {
        for(int j = b.size() - 1; j >= 0; j--) {
            res[i+j+1] += (a[i]-'0') * (b[j]-'0');
        }
    }

    // 处理进位
    for(int i = res.size() - 1; i > 0; i--) {
        res[i-1] += res[i] / 10;
        res[i] %= 10;
    }

    // 转成字符串
    string s = "";
    int start = 0;
    while(start < res.size() && res[start] == 0) start++;
    for(int i = start; i < res.size(); i++) s.push_back(res[i] + '0');
    return s.empty() ? "0" : s;
}

// 预处理 2 的幂，返回长度为 m+1 的数组，p[k] = 2^k
vector<string> preprocess_powers(int m) {
    vector<string> p(m+1, "1");
    string two = "2";
    for(int i = 1; i <= m; i++) {
        p[i] = mul(p[i-1], two);
    }
    return p;
}

string frow(int n, int m, vector<vector<int>> &a, const vector<string> &p) {
    vector<vector<string>> dp(m, vector<string>(m, "0"));
    for(int i = 0; i < m; i++) {
        dp[i][i] = mul(to_string(a[n][i]), p[m]); // 最后一次取数权重
    }

    // 区间长度 >= 2
    for(int right = 1; right <= m - 1; right++) {
        for(int left = right - 1; left >= 0; left--) {
            int k = m - (right - left + 1) + 1; // 当前取数是第 k 次
            string left_option = mul(to_string(a[n][left]), p[k]);
            string right_option = mul(to_string(a[n][right]), p[k]);

            string temp1 = add(left_option, dp[left+1][right]);
            string temp2 = add(right_option, dp[left][right-1]);

            // 取最大值
            if(temp1.size() > temp2.size() || (temp1.size() == temp2.size() && temp1 > temp2))
                dp[left][right] = temp1;
            else
                dp[left][right] = temp2;
        }
    }
    return dp[0][m-1];
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m));
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            cin >> a[i][j];

    // 预处理 2^k
    vector<string> p = preprocess_powers(m);

    string sum = "0";
    for(int i = 0; i < n; i++) {
        sum = add(sum, frow(i, m, a, p));
    }
    cout << sum << endl;
    return 0;
}
