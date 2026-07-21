#include<iostream>
#include<algorithm>
using namespace std;

void quick_sort(int a[], int l, int r){
    if(l >= r) return;

    int i = l, j = r;
    int pivot = a[l];
    while(i < j){//内层循环加入(i < j)，防止越界
        while(i < j && a[j] >= pivot){
            j--;
        }
        if(i < j){
            a[i] = a[j];
            i++;
        }
        while(i < j && a[i] <= pivot){
            i++;
        }
        if(i < j){ 
            a[j] = a[i];
            j--;
        }
    }
    a[i] = pivot;
    
    quick_sort(a, l, i - 1);
    quick_sort(a, i + 1, r);
}

int main(){
    int a[] = {5, 3, 7, 2, 8, 1, 4};
    int n = sizeof(a) / sizeof(a[0]);

    quick_sort(a, 0, n - 1);

    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    return 0;
}