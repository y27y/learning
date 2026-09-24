#include <iostream>

void qsort(int arr[], int l, int r) {
    if (l >= r) {
        return;
    }
    int pivot = arr[l];
    int i = l, j = r;
    static int cnt = 0;
    while (i < j) {
        while (i < j && arr[j] >= pivot) {
            j--;
        }
        if (i < j) {
            arr[i] = arr[j];
            i++;
        }
        while (i < j && arr[i] <= pivot) {
            i++;
        }
        if (i < j) {
            arr[j] = arr[i];
            j--;
        }
        std::cout << cnt << std::endl;
        cnt++;
    }
    arr[i] = pivot;
    qsort(arr, l, i - 1);
    qsort(arr, i + 1, r);
    return;
}

int main() {
    int a[] = {5, 3, 7, 2, 8, 1, 4};
    int n = sizeof(a) / sizeof(a[0]);

    qsort(a, 0, n - 1);

    for (int i = 0; i < n; i++) {
        std::cout << a[i] << " ";
    }
    return 0;
}