#include <iostream>
using namespace std;
#include "Vector.h"

int main() {

	int ele[10] = { 1,2,3,4,5,6,7,8,9,10 };
	Vector<int> v(ele, 10);
	//v.insert(1);
	for (int i = 0; i < v.size(); ++i)
		cout << v[i] << " ";
	cout << endl;
	return 0;
}