#include <iostream>
#include <algorithm>
#include "Student.h"
#include "SortTestHelper.h"
#include "SelectionSort.h"
#include "InsertionSort.h"
#include "BubbleSrot.h"
using namespace std;


int main() {
	/*int a[10] = { 10,9,8,7,6,5,4,3,2,1 };
	selectionsort(a, 10);
	printarr(a, 10);

	float b[4] = { 4.5,9.6,2.6,4.1 };
	selectionsort(b, 4);
	printarr(b, 4);
	student d[4] = { {"d", 90}, {"c",100}, {"b", 95}, {"a", 95} };
	selectionsort(d, 4);
	printarr(d, 4);*/
	int n = 10000;
	//int* arr = SortTestHelper::generateNearlyOrderedArray(n, 0);
	int* arr = SortTestHelper::generateRandomArray(n, 0, n);
	int* arr1 = SortTestHelper::copyArray(arr, n);
	int* arr2 = SortTestHelper::copyArray(arr, n);
	int* arr3 = SortTestHelper::copyArray(arr, n);
	int* arr4 = SortTestHelper::copyArray(arr, n);
	SortTestHelper::testSort("Selection Sort", selectionSort, arr, n);
	SortTestHelper::testSort("Insertion Sort", insertionSort, arr1, n);

	SortTestHelper::testSort("Bubble Sort", bubbleSort, arr2, n);
	SortTestHelper::testSort("Bubble Sort1", bubbleSort1, arr3, n);
	SortTestHelper::testSort("Bubble Sort2", bubbleSort2, arr4, n);

	delete[] arr1;
	delete[] arr2;
	delete[] arr;
	delete[] arr3;
	delete[] arr4;
	return 0;

}