#include<iostream>
#include<vector>
using namespace std;

void q_sort(int a[], int l, int r){
    if(l >= r) return;

    int i = l, j = r;
    int pivot = a[l];
    while(i < j){
        while(i < j && a[j] >= pivot){
            j--;
        }
        if(i < j){
            a[i] = a[j];
            i++;
        }
        while(i < j && pivot >= a[i]){
            i++;
        }
        if(i < j){
            a[j] = a[i];
            j--;
        }
    }
    a[i] = pivot;

    q_sort(a, l, i - 1);
    q_sort(a, i + 1, r);

}

class heap{//小根堆
private:
    vector<int> h;
    int sz = 0;
    void up(int n){
        while(n > 1){
            int parent = n / 2;
            if(h[parent] <= h[n]) break;
            swap(h[parent], h[n]);
            n = parent;
        }
    }

    void down(int n){
        while(1){
            int left = n * 2;
            int right = n * 2 + 1;
            int _min = n;

            if (left <= sz && h[left] < h[_min]) _min = left;
            if (right <= sz && h[right] < h[_min]) _min = right;

            if(_min == n) break;
            swap(h[_min], h[n]);
            n = _min;
        }
    }
    
public:
    heap(int cap = 0){
        h.resize(cap + 1);
        sz = 0;
    }
    void push(int x){
        h.push_back(x);
        sz++;
        up(sz);
    }
    void pop(){
        swap(h[1], h[sz]);
        sz--;      
        h.pop_back();
        down(1);
    }
    int size(){
        return sz;
    }  
    bool empty(){
        return sz == 0;
    }
    int top(){
        return h[1];
    }
};

void bubble_sort(int a[], int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n - 1; j++){
            if(a[j] > a[j + 1]){
                swap(a[j], a[j + 1]);
            }
        }
    }
}

void insertion_sort(int a[], int n){
    for(int i = 1; i < n; i++){
        int key = a[i];
        int j = i - 1;
        while(j >= 0 && a[j] > key){
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}


int main(){
    int a[] = {5, 3, 7, 2, 8, 1, 4, -1, 114514};
    int n = sizeof(a) / sizeof(a[0]);

    // q_sort(a, 0, n - 1);

    // for (int i = 0; i < n; i++) {
    //     cout << a[i] << " ";
    // }
//-------------------------------------------
    // heap h;
    // for(auto & x : a){
    //     h.push(x);
    // }
    // while(h.size() != 0){
    //     cout << h.top() << " ";
    //     h.pop();
    // }
//-------------------------------------------
    // bubble_sort(a,n);
    // for(int i = 0; i < n; i++){
    //     cout << a[i] << " ";
    // }
//-------------------------------------------
    insertion_sort(a,n);
    for(int i = 0; i < n; i++){
        cout << a[i] << " ";
    }
}
