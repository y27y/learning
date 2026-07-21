#include <bits/stdc++.h>
using namespace std;

struct BigInt {
    vector<int> d;   // 数字，低位在前
    bool neg;        // 是否为负数

    BigInt() : neg(false) {}

    // 从 string 构造
    BigInt(const string& s) {
        neg = false;
        d.clear();
        int start = 0;
        if (s[0] == '-') {
            neg = true;
            start = 1;
        }
        for (int i = s.size() - 1; i >= start; i--)
            d.push_back(s[i] - '0');
        trim();
    }

    // 去除前导 0
    void trim() {
        while (d.size() > 1 && d.back() == 0)
            d.pop_back();
        if (d.size() == 1 && d[0] == 0)
            neg = false;
    }

    // 比较绝对值
    static int cmpAbs(const BigInt& a, const BigInt& b) {
        if (a.d.size() != b.d.size())
            return a.d.size() < b.d.size() ? -1 : 1;
        for (int i = a.d.size() - 1; i >= 0; i--) {
            if (a.d[i] != b.d[i])
                return a.d[i] < b.d[i] ? -1 : 1;
        }
        return 0;
    }

    // 绝对值加法
    static BigInt addAbs(const BigInt& a, const BigInt& b) {
        BigInt res;
        int carry = 0;
        int n = max(a.d.size(), b.d.size());
        for (int i = 0; i < n || carry; i++) {
            int sum = carry;
            if (i < (int)a.d.size()) sum += a.d[i];
            if (i < (int)b.d.size()) sum += b.d[i];
            res.d.push_back(sum % 10);
            carry = sum / 10;
        }
        return res;
    }

    // 绝对值减法 |a| >= |b|
    static BigInt subAbs(const BigInt& a, const BigInt& b) {
        BigInt res;
        int borrow = 0;
        for (int i = 0; i < (int)a.d.size(); i++) {
            int x = a.d[i] - borrow;
            if (i < (int)b.d.size()) x -= b.d[i];
            if (x < 0) {
                x += 10;
                borrow = 1;
            } else borrow = 0;
            res.d.push_back(x);
        }
        res.trim();
        return res;
    }

    // 加法
    friend BigInt operator+(const BigInt& a, const BigInt& b) {
        BigInt res;
        if (a.neg == b.neg) {
            res = addAbs(a, b);
            res.neg = a.neg;
        } else {
            if (cmpAbs(a, b) >= 0) {
                res = subAbs(a, b);
                res.neg = a.neg;
            } else {
                res = subAbs(b, a);
                res.neg = b.neg;
            }
        }
        return res;
    }

    // 减法
    friend BigInt operator-(const BigInt& a, const BigInt& b) {
        BigInt nb = b;
        nb.neg = !b.neg;
        return a + nb;
    }

    // 乘法
    friend BigInt operator*(const BigInt& a, const BigInt& b) {
        BigInt res;
        res.d.assign(a.d.size() + b.d.size(), 0);
        for (int i = 0; i < (int)a.d.size(); i++) {
            for (int j = 0; j < (int)b.d.size(); j++) {
                res.d[i + j] += a.d[i] * b.d[j];
            }
        }
        for (int i = 0; i < (int)res.d.size() - 1; i++) {
            res.d[i + 1] += res.d[i] / 10;
            res.d[i] %= 10;
        }
        res.neg = a.neg ^ b.neg;
        res.trim();
        return res;
    }

    // 除以 int
    friend BigInt operator/(const BigInt& a, int b) {
        BigInt res;
        res.d.assign(a.d.size(), 0);
        long long rem = 0;
        for (int i = a.d.size() - 1; i >= 0; i--) {
            rem = rem * 10 + a.d[i];
            res.d[i] = rem / b;
            rem %= b;
        }
        res.neg = a.neg ^ (b < 0);
        res.trim();
        return res;
    }

    // 输出
    friend ostream& operator<<(ostream& os, const BigInt& a) {
        if (a.neg) os << '-';
        for (int i = a.d.size() - 1; i >= 0; i--)
            os << a.d[i];
        return os;
    }
};

int main() {
    BigInt a("12345678901234567890");
    BigInt b("987654321");

    cout << a + b << endl;
    cout << a - b << endl;
    cout << a * b << endl;
    cout << a / 3 << endl;
}

