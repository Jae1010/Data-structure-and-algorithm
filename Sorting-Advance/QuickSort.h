#pragma once
#include <iostream>
#include <algorithm>

template <typename T>
int __partition(T arr[], int l, int r) {

    T v = arr[l];

    int j = l; // arr[l+1...j] < v ; arr[j+1...i) > v
    for (int i = l + 1; i <= r; i++)
        if (arr[i] < v) {
            swap(arr[++j], arr[i]);
        }

    swap(arr[l], arr[j]);

    return j;
}

// 对arr[l...r]部分进行快速排序
template <typename T>
void __quickSort(T arr[], int l, int r) {

    if (l >= r)
        return;

    int p = __partition(arr, l, r);
    __quickSort(arr, l, p - 1);
    __quickSort(arr, p + 1, r);
}

template <typename T>
void quickSort(T arr[], int n) {

    __quickSort(arr, 0, n - 1);
}
