#pragma once
#include <iostream>
#include <algorithm>
#include "InsertionSort.h"

using namespace std;


// 将arr[l...mid]和arr[mid+1...r]两部分进行归并
template<typename T>
long long  __merge_inversion(T arr[], int l, int mid, int r) {

	T* aux = new T[r - l + 1];
	for (int i = l; i <= r; i++)
		aux[i - l] = arr[i];

	long long num = 0;
	// 初始化，i指向左半部分的起始索引位置l；j指向右半部分起始索引位置mid+1
	int i = l, j = mid + 1;
	for (int k = l; k <= r; k++) {
		if (i > mid) {// 如果左半部分元素已经全部处理完毕
			arr[k] = aux[j - l];
			++j;
		}
		else if (j > r) {// 如果右半部分元素已经全部处理完毕
			arr[k] = aux[i - l];
			++i;
		}
		else if (aux[i - l] > aux[j - l]) {// 左半部分所指元素 > 右半部分所指元素
			arr[k] = aux[j - l];
			++j;
			num += (long long)(mid - i + l);
		}
		else           // 左半部分所指元素 <= 右半部分所指元素
		{
			arr[k] = aux[i - l];
			++i;
		}
	}
	delete[] aux;
	return num;
}

// 递归使用归并排序,对arr[l...r]的范围进行排序
template <typename T>
long long __mergeSort_inversion(T arr[], int l, int r) {

		if (l >= r)
			return 0;

	int mid = l + (r - l) / 2;
	long long res1 = __mergeSort_inversion(arr, l, mid);
	long long res2 = __mergeSort_inversion(arr, mid + 1, r);
	return res1 + res2 + __merge_inversion(arr, l, mid, r);
}

template <typename T>
long long  mergeSort_inversion(T arr[], int n) {
	return __mergeSort_inversion(arr, 0, n - 1);
}