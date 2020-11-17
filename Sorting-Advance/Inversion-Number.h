#pragma once
#include <iostream>
#include <algorithm>
#include "InsertionSort.h"

using namespace std;


// ��arr[l...mid]��arr[mid+1...r]�����ֽ��й鲢
template<typename T>
long long  __merge_inversion(T arr[], int l, int mid, int r) {

	T* aux = new T[r - l + 1];
	for (int i = l; i <= r; i++)
		aux[i - l] = arr[i];

	long long num = 0;
	// ��ʼ����iָ����벿�ֵ���ʼ����λ��l��jָ���Ұ벿����ʼ����λ��mid+1
	int i = l, j = mid + 1;
	for (int k = l; k <= r; k++) {
		if (i > mid) {// �����벿��Ԫ���Ѿ�ȫ���������
			arr[k] = aux[j - l];
			++j;
		}
		else if (j > r) {// ����Ұ벿��Ԫ���Ѿ�ȫ���������
			arr[k] = aux[i - l];
			++i;
		}
		else if (aux[i - l] > aux[j - l]) {// ��벿����ָԪ�� > �Ұ벿����ָԪ��
			arr[k] = aux[j - l];
			++j;
			num += (long long)(mid - i + l);
		}
		else           // ��벿����ָԪ�� <= �Ұ벿����ָԪ��
		{
			arr[k] = aux[i - l];
			++i;
		}
	}
	delete[] aux;
	return num;
}

// �ݹ�ʹ�ù鲢����,��arr[l...r]�ķ�Χ��������
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