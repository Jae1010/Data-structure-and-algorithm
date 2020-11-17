#pragma once
#include <iostream>
#include <algorithm>
#include "InsertionSort.h"
#include <cassert>

template <typename T>
int __partition_selection(T arr[], int l, int r) {

	swap(arr[l], arr[rand() % (r - l + 1) + l]);
	T v = arr[l];

	//arr[l+1, j] < v, arr[j+1, i) >v
	int j = l;
	for (int i = l + 1; i <= r; i++) {
		if (arr[i] < v) {
			swap(arr[++j], arr[i]);
		}
	}
	swap(arr[l], arr[j]);
	return j;
}


template <typename T>
T __quickSort_selection(T arr[], int l, int r, int m) {

	if (l == r)
		return arr[l];


	int p = __partition_selection(arr, l, r);
	if (m < p)
		return __quickSort_selection(arr, l, p - 1, m);
	else if (m > p)
		return __quickSort_selection(arr, p + 1, r, m);
	else
		return arr[p];
}


template <typename T>
T quickSort_selection(T arr[], int n,int m) {
	assert(m >= 0 && m < n);
	srand(time(NULL));
	T res = __quickSort_selection(arr, 0, n - 1, m-1);
	return res;
}