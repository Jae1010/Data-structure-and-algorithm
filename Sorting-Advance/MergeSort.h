#pragma once
#include <iostream>
#include <algorithm>

using namespace std;


// 将arr[l...mid]和arr[mid+1...r]两部分进行归并
template<typename T>
void __merge(T arr[], int l, int mid, int r) {

	T *aux = new T[r - l + 1];
	for (int i = l; i <= r; i++)
		aux[i - l] = arr[i];

	// 初始化，i指向左半部分的起始索引位置l；j指向右半部分起始索引位置mid+1
	int i = l, j = mid + 1;
	for (int k = l; k <= r; k++) {
		if (i > mid) {// 如果左半部分元素已经全部处理完毕
			arr[k] = aux[j - l];
			++j;
		}
		else if(j > r){// 如果右半部分元素已经全部处理完毕
			arr[k] = aux[i - l];
			++i;
		}
		else if (aux[i - l] > aux[j - l]) {// 左半部分所指元素 > 右半部分所指元素
			arr[k] = aux[j - l];
			++j;
		}
		else           // 左半部分所指元素 <= 右半部分所指元素
		{
			arr[k] = aux[i - l];
			++i;
		}
	}
	delete[] aux;
}

// 递归使用归并排序,对arr[l...r]的范围进行排序
template <typename T>
void __mergeSort(T arr[], int l, int r) {

	if (l >= r)
		return;
	int mid = l + (r - l) / 2;
	__mergeSort(arr, l, mid);
	__mergeSort(arr, mid + 1, r);
	if (arr[mid] > arr[mid+1])
		__merge(arr, l, mid, r);
}

template <typename T>
void mergeSort(T arr[], int n) {
	__mergeSort(arr, 0, n - 1);
}