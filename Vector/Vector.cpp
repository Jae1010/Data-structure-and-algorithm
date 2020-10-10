#include  "Vector.h"
#include <ctime>

template <typename T>
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi) {
	_elem = new T[_capacity = 2 * (hi - lo)]; //分配空间
	_size = 0;	//规模清0
	while (lo < hi)
	{
		_elem[_size++] = A[lo++];
	}
}
//=重载
template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T> const& V) {
	if (_elem) delete[] _elem; //释放原有内容
	copyFrom(V, V._elem, V.size());	//整体复制
	return *this; //返回当前对象的引用，以便链式赋值
}

//扩容
template <typename T>
void Vector<T>::expand() {
	if (_size < _capacity) return;
	if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;
	T* oldElem = _elem;
	_elem = new T[_capacity <<= 1]; //容量加倍
	for (int i = 0; i < _size; ++i)
		_elem[i] = oldElem[i];
	delete[] oldElem;
}

//缩容
template <typename T>
void Vector<T>::shrink() {
	if (_capacity < DEFAULT_CAPACITY << 1) return;//不能收缩到DEFAULT_CAPACITY以下
	if (_size << 2 > _capacity) return; //以25%为界
	T* oldElem = _elem;
	_elem = new T[_capacity >>= 1];   //容量减半
	for (int i = 0; i < _size; ++i)
		_elem[i] = oldElem[i];
	delete[] oldElem;
}

//重载下标操作符
template <typename T>
T& Vector<T>::operator[](Rank r) const {
	return _elem[r];
}


//随机置乱向量，使各元素等概率出现于每一位置
template <typename T>
void permute(Vector<T>& V) {
	srand((unsigned int)time(NULL));
	for (int i = V.size(); i > 0; --i)
		swap(V[i - 1], V[rand() % i]);
}


template <typename T>
void Vector<T>::unsort(Rank lo, Rank hi) {
	srand((unsigned int)time(NULL));
	for (int i = hi; i > lo; --i)
		swap(_elem[i - 1], _elem[rand() % i + lo]);
}

//template <typename T>
//void Vector<T>::unsort(Rank lo, Rank hi) {
//	srand((unsigned int)time(NULL));
//	T* V = _elem + lo;
//	for (int i = hi- lo; i > 0; --i)
//		swap(V[i - 1], V[rand() % i]);
//}



