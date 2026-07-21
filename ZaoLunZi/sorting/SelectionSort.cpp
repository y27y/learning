#include<iostream>
using namespace std;
void swap(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}

void SelectionSort(int a[], int n){
    for(int i = 0; i < n; i++){
        int min_i = i;
        for(int j = i + 1; j < n; j++){
            if(a[j] < a[min_i]){
                min_i = j;
            }
        }
        swap(a[i], a[min_i]);
    }
}

int main(){
    int a[] = {5, 3, 7, 2, 8, 1, 4};
    int n = sizeof(a) / sizeof(a[0]);

    SelectionSort(a, n);
    for(int &it : a){
        cout << it << " ";
    }
}