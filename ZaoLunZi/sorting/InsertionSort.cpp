#include<iostream>
using namespace std;
void swap(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}

void InsertionSort1(int a[], int n){
    if(n == 0 || n == 1) return;
    for(int i = 1; i < n; i++){
        for(int j = i - 1; j >= 0 && a[j] > a[j + 1]; j--){
            swap(a[j], a[j + 1]);
        }
    }
}

int findleft(int a[], int l, int r, int key){
    int mid;
    int ans = -1;
    while(l <= r){
        mid = ((r - l) >> 1) + l;
        if(a[mid] >= key){        
            ans = mid;
            r = mid - 1;
        }
        else{
            l = mid + 1;
        }
    }
    return ans;
}

void InsertionSort2(int a[], int n){//二分查找优化
    if(n == 0 || n == 1) return;
    for(int i = 1; i < n; i++){
        if(a[i] < a[i - 1]){
            int p = findleft(a, 0, i - 1, a[i]);
            int temp = a[i];
            for(int j = i; j > p; j--){
                a[j] = a[j - 1];
            }
            a[p] = temp;
        }
    }
}

int main(){
    int a[] = {73, 12, 98, 45, 6, 81, 34, 57, 29, 100, 3, 66, 41, 90, 15, 77, 24, 53, 8, 62, 39, 85, 19, 71, 
2, 95, 31, 58, 14, 68, 47, 88, 21, 76, 5, 60, 36, 82, 17, 69, 27, 92, 10, 64, 43, 79, 1, 55, 33, 87, 16, 74, 
25, 61, 40, 83, 13, 70, 30, 94, 7, 59, 38, 80, 18, 67, 26, 91, 11, 63, 44, 78, 4, 56, 35, 84, 20, 72, 28, 93, 
9, 65, 42, 86, 22, 75, 32, 97, 23, 54, 37, 89, 46, 96, 49, 99, 48, 52, 50, 51};
    int n = sizeof(a) / sizeof(a[0]);

    //InsertionSort1(a, n);
    InsertionSort2(a, n);
    for(int &it : a){
        cout << it << " ";
    }
}