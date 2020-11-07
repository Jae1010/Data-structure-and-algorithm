#include <iostream>
using namespace std;

#include "List.h"

template <typename T>
void prindList(List<T>& l) {
	for (int i = 0; i < l.size(); ++i)
		cout << l[i] << " ";
	cout << endl;
}

int main() {
	List<int> l;
	l.insertAsFirst(5);
	l.insertAsFirst(8);
	l.insertAsFirst(3);
	l.insertAsFirst(2);
	l.insertAsFirst(10);
	//l.insertAsFirst(6);
	//l.insertAsFirst(20);
	//l.insertAsFirst(25);
	//l.insertAsFirst(14);
	//l.insertAsFirst(4);
	//l.insertAsFirst(5);
	prindList(l);
	cout << "************************" << endl;
	l.sort();
	prindList(l);
	return 0;
}