#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class heap{//大根堆
    
private:
    vector<int> h;//从下标1开始使用，方便计算
    int sz;

    void up(int n){//n为插入数字的位置
        while(n > 1){
            int parent = n / 2;
            if(h[parent] >= h[n]) break;
            swap(h[parent], h[n]);
            n = parent;
        }
    }

    void down(int n){
        while(1){
            int left = n * 2;
            int right = left + 1;
            int _max = n;

            if (left <= sz && h[left] > h[_max]) _max = left;
            if (right <= sz && h[right] > h[_max]) _max = right;

            if(_max == n) break;
            swap(h[_max], h[n]);
            n = _max;
        }
    }


public:    
    heap(int cap = 0){
        h.resize(cap + 1);
        sz = 0;
    }

    void push(int x){
        if (sz + 1 >= h.size()){
            h.push_back(0);
        }
        sz++;
        h[sz] = x;
        up(sz); 
    }

    void pop(){
        if(sz == 0) return;
        h[1] = h[sz];
        sz--;
        down(1);
    }

    int top(){
        return h[1];
    }

    int size(){
        return sz;
    }

    bool empty(){
        return sz == 0;
    }
};


int main(){
    heap h;
    h.push(114);
    h.push(51);
    h.push(41919);
    h.push(810);

    cout << h.size() << endl;

    while(!h.empty()) {
        cout << h.top() << " ";
        h.pop();
    }

}//heap
