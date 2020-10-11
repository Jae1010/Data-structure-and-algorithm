#pragma once
#include <iostream>
using namespace std;
#include <ctime>

typedef int Rank;
#define DEFAULT_CAPACITY 3 //vector默认初始容量（实际应用中可设置为更大）

template <typename T> class Vector {
protected:
	Rank _size;    //规模
	int _capacity; //容量
	T* _elem;	   //数据区		
	void copyFrom(T const* A, Rank lo, Rank hi);  //复刢数组区间A[lo, hi)
	void expand();  //空间不足时扩容
	void shrink();  //装填因子过小时压缩
	bool bubble(Rank lo, Rank hi); //扫描交换
	void bubbleSort(Rank lo, Rank hi); //起泡排序算法
	Rank max(Rank lo, Rank hi); //选取最大元素
	void selectionSort(Rank lo, Rank hi); //选择排序算法
	void merge(Rank lo, Rank mi, Rank hi); //归并算法
	void mergeSort(Rank lo, Rank hi); //归并排序算法
	Rank partition(Rank lo, Rank hi); //轴点构造算法
	void quickSort(Rank lo, Rank hi); //快速排序算法
	void heapSort(Rank lo, Rank hi); //堆排序

public:
	//构造函数
	Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0) { //容量为c、规模为s、所有元素初始为v
		_elem = new T[_capacity = c];
		for (_size = 0; _size < s; _elem[_size++] = v);
	}
	Vector(T const* A, Rank lo, Rank hi) { copyFrom(A, lo, hi); }//数组区间复制
	Vector(T const* A, Rank n) { copyFrom(A, 0, n); }	//数组整体复制
	Vector(Vector<T> const& V, Rank lo, Rank hi) { copyFrom(V._elem, lo, hi); } //向量区间复制
	Vector(Vector<T> const& V) { copyFrom(V._elem, 0, V._size); }  //向量整体复制

	//析构函数
	~Vector() { delete[] _elem; }  //释放内部空间

	//只读访问接口
	Rank size() const { return _size; } //规模
	bool empty() const { return !_size; } //是否为空
	int disordered() const; //判断向量是否已排序
	Rank find(T const& e, Rank lo, Rank hi) const;  //无序向量区间查找
	Rank find(T const& e) const { find(e, 0, _size); }  //无序向量整体查找
	Rank search(T const& e, Rank lo, Rank hi) const; //有序向量区间查找
	Rank search(T const& e) const  //有序向量区间查找
	{
		return (_size <= 0) ? -1 : search(e, 0, _size);
	}

	//可写访问接口
	T& operator[](Rank r) const;  //重载下标操作符，可以类似于数组形式引用各元素
	Vector<T>& operator= (Vector<T> const&);  //重载赋值操作符，以便直接克隆向量
	T remove(Rank r); //删除秩为r的元素
	int remove(Rank lo, Rank hi); //删除秩在秩间[lo, hi)之内的元素
	Rank insert(Rank r, T const& e); //插入元素
	Rank insert(T const& e) { Rank i = insert(_size, e); return i; }  //默认作为末元素插入
	void sort(Rank lo, Rank hi); //对[lo, hi)排序
	void sort() { sort(0, _size); } //整体排序
	void unsort(Rank lo, Rank hi); //对[lo, hi)置乱
	int deduplicate(); //无序去重
	int uniquify(); //有序去重

	//遍历
	void traverse(void (*)(T&)); //遍历（使用函数指针，只读或者局部性修改）
	template <typename VST> void traverse(VST&); //遍历（使用函数对象，可全局性修改）
};


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
	++_size;
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


//删除单个元素
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
void Vector<T>::traverse(VST& visit) //利用函数对象机制的遍历
{
	for (int i = 0; i < _size; i++) visit(_elem[i]);
}