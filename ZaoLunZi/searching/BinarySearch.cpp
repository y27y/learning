#include<iostream>
using namespace std;

int BinarySearch(int a[], int start, int end, int key){
    int mid = (end - start) / 2 + start;
    while(start <= end){
        if(a[mid] > key){
            end = mid;
        }
        else if(a[mid] < key){
            start = mid;
        }
        else{
            return mid;
        } 
        mid = (end - start) / 2 + start;
    }
    return -1;
}

int findleft(int a[], int l, int r, int key){//找>=key的最左值
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

int findright(int a[], int l, int r, int key){//<=key的最右值
    int mid;
    int ans = -1;
    while(l <= r){
        mid = ((r - l) >> 1) + l;
        if(a[mid] <= key){        
            ans = mid;
            l = mid + 1;
        }
        else{
            r = mid - 1;
        }
    }
    return ans;
}

int main(){
    int a[] = {1, 3, 5, 7, 9, 11, 13};
    //cout << BinarySearch(a, 0, 6, 13);
    //cout << findleft(a, 0, 6, 6);
    cout << findright(a, 0, 6, 12);  
}