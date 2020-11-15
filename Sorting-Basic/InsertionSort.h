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