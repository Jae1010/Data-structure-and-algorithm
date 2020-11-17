#pragma once
#include <iostream>
#include <algorithm>



template <typename T>
void insertionSort1(T arr[], int n) {
	for (int i = 0; i < n; i++) {
		for (int j = i; j > 0 && arr[j] < arr[j - 1]; j--) {
			swap(arr[j], arr[j - 1]);
		}
	}
}

//ÓÅ»¯°æ
template <typename T>
void insertionSort(T arr[], int n) {
	for (int i = 0; i < n; i++) {
		T e = arr[i];
		int j;
		for (j = i; j > 0 && arr[j - 1] > e; j--) {
			arr[j] = arr[j - 1];
		}
		arr[j] = e;
	}
}

template <typename T>
void insertionSort(T arr[], int l, int r) {
	for (int i = l; i <= r; i++) {
		T e = arr[i];
		int j;
		for (j = i; j > l && arr[j - 1] > e; j--) {
			arr[j] = arr[j - 1];
		}
		arr[j] = e;
	}
}