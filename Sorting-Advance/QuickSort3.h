#pragma once
#include <iostream>
#include <algorithm>
#include "InsertionSort.h"
#include <ctime>



template <typename T>
void __quickSort3(T arr[], int l, int r) {


	if (r - l <= 15) {
		insertionSort(arr, l, r);
		return;
	}

	//partition
	swap(arr[l], arr[rand() % (r - l + 1) + l]);

	T v = arr[l];

	int lt = l; //arr[l+1, lt] < v
	int gt = r + 1; //arr[gt, r] > v
	int i = l + 1;
	while (i < gt) {
		if (arr[i] < v) {
			swap(arr[i], arr[lt + 1]);
			i++;
			lt++;
		}
		else if (arr[i] > v) {
			swap(arr[i], arr[gt - 1]);
			gt--;
		}
		else {
			i++;
		}
	}

	swap(arr[l], arr[lt]);

	__quickSort3(arr, l, lt - 1);
	__quickSort3(arr, gt, r);
}


template <typename T>
void quickSort3(T arr[], int n) {
	srand(time(NULL));
	__quickSort3(arr, 0, n - 1);
}