#pragma once
#include <iostream>
#include <algorithm>

template <typename T>
void bubbleSort(T arr[], int n) {
	bool sort = false;
	for (int i = 0; i < n; i++) {
		for (int j = 1; j < n - i; j++)
			if (arr[j - 1] > arr[j])  //j+1会越界
				swap(arr[j - 1], arr[j]);
	}
}

//优化版1
template <typename T>
void bubbleSort1(T arr[], int n) {
	bool sorted = false;
	while (!sorted) {
		sorted = true;
		for (int i = 1; i < n; i++) {
			if (arr[i-1] > arr[i]) {  //i+1会越界
				swap(arr[i-1], arr[i]);
				sorted = false;
			}
		}
		--n;
	}
}

//优化版2
template <typename T>
void bubbleSort2(T arr[], int n) {
	int newn;
	do {
		newn = 0;
		for (int i = 1; i < n; i++) {
			if (arr[i - 1] > arr[i]) {  //i+1会越界
				swap(arr[i - 1], arr[i]);
				// 记录最后一次的交换位置,在此之后的元素在下一轮扫描中均不考虑
				newn = i; 
			}	
		}
		n = newn;
	} while (newn > 0);
}