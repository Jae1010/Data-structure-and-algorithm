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

template <typename T> // 无序向量的顺序查找：返回最后一个元素e的位置；失败时，返回lo - 1
Rank Vector<T>::find(T const& e, Rank lo, Rank hi) const {
	//while ((lo < hi--) && (e != _elem[hi]));
	while (lo < hi--)  //命中多个元素，将返回秩最大者
	{
		if (e == _elem[hi])
			return hi;
	}
	return hi;
}

//插入元素
template <typename T>
Rank Vector<T>::insert(Rank r, T const& e) {
	expand();
	for (int i = _size; i > r; --i)
		_elem[i] = _elem[i - 1];
	_elem[r] = e;
	return r;
}

//删除区间元素
template <typename T>
int Vector<T>::remove(Rank lo, Rank hi) {
	if (hi == lo) return 0;
	if (lo < 0 || hi > _size) return 0;
	while (hi < _size)
	{
		_elem[lo++] = _elem[hi++];
	}
	_size = lo;
	shrink();
	return hi - lo;
}


//删除单元素
template <typename T>
T Vector<T>::remove(Rank r) {
	T e = _elem[r];
	remove(r, r + 1);
	return e;
}

template <typename T> 
int Vector<T>::deduplicate() { //删除无序向量中重复元素
	int oldSize = _size;
	Rank i = 1;
	while (i < _size)
	{
		if (find(_elem[i], 0, i) < 0)
			++i;
		else
			remove(i);
	}
	return oldSize - _size;
}

template <typename T>
int Vector<T>::uniquify() {//删除有序向量中重复元素（双指针）
	int oldSize = _size;
	int slowIndex = 0;
	for (int fastIndex = 0; fastIndex < _size; ++fastIndex)
		if (_elem[fastIndex] != _elem[fastIndex + 1])
			_elem[++slowIndex] = _elem[fastIndex + 1];
	return oldSize - slowIndex - 1;
}

template <typename T>
void Vector<T>::traverse(void (*visit) (T&)) {
	for (int i = 0; i < _size; i++) visit(_elem[i]);
}


template <typename T> template < typename VST> //元素类型、操作器
void Vector<T>::traverse(VST & visit) //利用函数对象机制的遍历
{ for (int i = 0; i < _size; i++) visit(_elem[i]); }

