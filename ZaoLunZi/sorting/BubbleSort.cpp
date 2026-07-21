#include<iostream>
using namespace std;

void swap(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}

void BubbleSort(int a[], int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n - 1; j++){
            if(a[j] > a[j + 1]) swap(a[j], a[j + 1]);
        }
    }
}
int main(){
    int a[] = {5, 3, 7, 2, 8, 1, 4};
    int n = sizeof(a) / sizeof(a[0]);
    BubbleSort(a, n);
    
    for(auto &it : a){
        cout << it << " ";
    }
}