#include <iostream>
#include <algorithm>
#include "SortTestHelper.h"
#include "InsertionSort.h"
//#include "MergeSort.h"
#include "MergeSort-Advance.h"
#include "QuickSort-Advance.h"
#include "QuickSort2.h"
#include "QuickSort3.h"

using namespace std;

int main() {
	
	int n = 1000000;

	int* arr1 = SortTestHelper::generateRandomArray(n, 0, n);
	int* arr2 = SortTestHelper::copyArray(arr1, n);
	int* arr3 = SortTestHelper::copyArray(arr1, n);

	SortTestHelper::testSort("Merge Sort", mergeSort, arr1, n);
	//SortTestHelper::testSort("Quick Sort", quickSort, arr2, n);
    SortTestHelper::testSort("Quick Sort3", quickSort3, arr3, n);
	//SortTestHelper::printArray(arr1, n);

	delete[] arr1;
	delete[] arr2;
	delete[] arr3;

 /*    测试2 测试近乎有序的数组
     双路快速排序算法也可以轻松处理近乎有序的数组
    int swapTimes = 100;
    cout << "Test for nearly ordered array, size = " << n << ", swap time = " << swapTimes << endl;
    arr1 = SortTestHelper::generateNearlyOrderedArray(n, swapTimes);
    arr2 = SortTestHelper::copyArray(arr1, n);
    arr3 = SortTestHelper::copyArray(arr1, n);

    SortTestHelper::testSort("Merge Sort", mergeSort, arr1, n);
    SortTestHelper::testSort("Quick Sort", quickSort, arr2, n);
    SortTestHelper::testSort("Quick Sort2", quickSort2, arr3, n);

    delete[] arr1;
    delete[] arr2;
    delete[] arr3;

    cout << endl;


     测试3 测试存在包含大量相同元素的数组
     使用双快速排序后, 我们的快速排序算法可以轻松的处理包含大量元素的数组
    cout << "Test for random array, size = " << n << ", random range [0,10]" << endl;
    arr1 = SortTestHelper::generateRandomArray(n, 0, 10);
    arr2 = SortTestHelper::copyArray(arr1, n);
    arr3 = SortTestHelper::copyArray(arr1, n);

    SortTestHelper::testSort("Merge Sort", mergeSort, arr1, n);
    SortTestHelper::testSort("Quick Sort", quickSort, arr2, n);
    SortTestHelper::testSort("Quick Sort3", quickSort3, arr3, n);

    delete[] arr1;
    delete[] arr2;
    delete[] arr3;*/

	return 0;
}