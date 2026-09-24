#include <iostream>
#include <vector>
/*

所有的区间保持左闭右开[l, r)
==所以r其实是尾后位置==

*/
void merge(int a[], int alen, int b[], int blen, std::vector<int>& c) {
    int aptr = 0, bptr = 0;
    while (aptr < alen && bptr < blen) {
        if (a[aptr] < b[bptr]) {
            c.push_back(a[aptr]);
            aptr++;
        } else {
            c.push_back(b[bptr]);
            bptr++;
        }
    }
    if (aptr == alen) {
        for (; bptr != blen; bptr++) {
            c.push_back(b[bptr]);
        }
    }
    if (bptr == blen) {
        for (; aptr != alen; aptr++) {
            c.push_back(a[aptr]);
        }
    }
}

void merge_sort(int arr[], int l, int r) {
    if (r - l <= 1)
        return;
    int mid = l + ((r - l) >> 1);
    merge_sort(arr, l, mid);
    merge_sort(arr, mid + 1, r);

    std::vector<int> tmp;
    merge(arr + l, mid - l, arr + mid, r - mid, tmp);
    for (int i = l; i < r; i++) {
        arr[i] = tmp[i - l];
    }
}

void merge_without_recurse(int arr[], int n) {//无递归merge_sort
    for (int l, m, r, step = 1; step < n; step *= 2) {
        l = 0;
        while(l < n){
            m = l + step - 1;
            if(m + 1 >= n){//如果已经没有右侧了
                break;
            }
            r = std::min(l + 2 * step - 1, n - 1);
            std::vector<int> tmp;
            merge(arr + l, m - l + 1, arr + m + 1, r - m, tmp);
            for (int i = l; i <= r; i++) {
                arr[i] = tmp[i - l];
            }
            l = r + 1;
        }
    }
}

int main() {
    int arr[10] = {1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    //merge_sort(arr, 0, 10);
    merge_without_recurse(arr, 10);
    for (auto& x : arr) {
        std::cout << x << " ";
    }
}