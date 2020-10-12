#include <iostream>
#include "Vector.h"


void printVector(Vector<int> &v) {
	for (int i = 0; i < v.size(); ++i)
		cout << v[i] << " ";
	cout << endl;
}

int main() {

	int ele[10] = { 1,2,3,4,1,5,4,8,2,3 };
	Vector<int> v(ele, 10);
	int i = v.insert(1);
	
	printVector(v);
	v.remove(5);
	int n = v.disordered();
	cout << "ÄæÐòÊýÎª£º" << n << endl;
	printVector(v);
	int j = v.deduplicate();
	printVector(v);
	cout << j << endl;
	return 0;
}