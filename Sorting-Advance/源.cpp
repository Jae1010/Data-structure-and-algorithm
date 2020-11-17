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

 /*    ����2 ���Խ������������
     ˫·���������㷨Ҳ�������ɴ���������������
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


     ����3 ���Դ��ڰ���������ͬԪ�ص�����
     ʹ��˫���������, ���ǵĿ��������㷨�������ɵĴ����������Ԫ�ص�����
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