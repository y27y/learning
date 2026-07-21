#include <iostream>
#include <vector>
using namespace std;

struct person {
    string name;
    int direction;
};

int main() {
    int n, m;
    cin >> n >> m;

    vector<person> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i].direction >> p[i].name;
    }

    vector<int> a(m), s(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i] >> s[i];
    }

    long long pos = 0;
    for (int i = 0; i < m; i++) {
        pos = (pos % n + n) % n; 

        if (p[pos].direction == 0) {
            if (a[i] == 0) pos -= s[i];
            else pos += s[i];
        } else {
            if (a[i] == 0) pos += s[i];
            else pos -= s[i];
        }
    }

    pos = (pos % n + n) % n;
    cout << p[pos].name << endl;
}
