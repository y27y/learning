#include <iostream>

void qsort(int arr[], int l, int r){
    if(l >= r){
        return;
    }
    int mid = l + (r - l) >> 1;
    int pivot = arr[l];
    int i = l, j = r;
    while(){

    }
    qsort(arr, l, mid);
    qsort(arr, mid, r);

}

int main(){

}