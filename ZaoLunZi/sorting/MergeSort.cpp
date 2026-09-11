#include <iostream>
#include <vector>

void merge(int a[], int alen, int b[], int blen, std::vector<int> &c){
    int aptr = 0, bptr = 0;
    while(aptr < alen && bptr < blen){
        if(a[aptr] < b[bptr]) {
            c.push_back(a[aptr]);
            aptr++;
        }else {
            c.push_back(b[bptr]);
            bptr++;
        }
    }
    if(aptr == alen){
        for(;bptr != blen;bptr++){
            c.push_back(b[bptr]);
        }
    }
    if(bptr == blen) {
        for(;aptr != alen;aptr++){
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
    for(int i = l; i < r; i++){
        arr[i] = tmp[i - l];
    }
}

int main() {
    int arr[10] = {1,4,1,5,9,2,6,5,3,5};
    merge_sort(arr, 0, 10);
    for(auto &x : arr){
        std::cout << x << " ";
    }
}