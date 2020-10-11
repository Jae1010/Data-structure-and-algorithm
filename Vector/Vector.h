#pragma once
#include <iostream>
using namespace std;
#include <ctime>

typedef int Rank;
#define DEFAULT_CAPACITY 3 //vectorĬ�ϳ�ʼ������ʵ��Ӧ���п�����Ϊ����

template <typename T> class Vector {
protected:
	Rank _size;    //��ģ
	int _capacity; //����
	T* _elem;	   //������		
	void copyFrom(T const* A, Rank lo, Rank hi);  //���c��������A[lo, hi)
	void expand();  //�ռ䲻��ʱ����
	void shrink();  //װ�����ӹ�Сʱѹ��
	bool bubble(Rank lo, Rank hi); //ɨ�轻��
	void bubbleSort(Rank lo, Rank hi); //���������㷨
	Rank max(Rank lo, Rank hi); //ѡȡ���Ԫ��
	void selectionSort(Rank lo, Rank hi); //ѡ�������㷨
	void merge(Rank lo, Rank mi, Rank hi); //�鲢�㷨
	void mergeSort(Rank lo, Rank hi); //�鲢�����㷨
	Rank partition(Rank lo, Rank hi); //��㹹���㷨
	void quickSort(Rank lo, Rank hi); //���������㷨
	void heapSort(Rank lo, Rank hi); //������

public:
	//���캯��
	Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0) { //����Ϊc����ģΪs������Ԫ�س�ʼΪv
		_elem = new T[_capacity = c];
		for (_size = 0; _size < s; _elem[_size++] = v);
	}
	Vector(T const* A, Rank lo, Rank hi) { copyFrom(A, lo, hi); }//�������临��
	Vector(T const* A, Rank n) { copyFrom(A, 0, n); }	//�������帴��
	Vector(Vector<T> const& V, Rank lo, Rank hi) { copyFrom(V._elem, lo, hi); } //�������临��
	Vector(Vector<T> const& V) { copyFrom(V._elem, 0, V._size); }  //�������帴��

	//��������
	~Vector() { delete[] _elem; }  //�ͷ��ڲ��ռ�

	//ֻ�����ʽӿ�
	Rank size() const { return _size; } //��ģ
	bool empty() const { return !_size; } //�Ƿ�Ϊ��
	int disordered() const; //�ж������Ƿ�������
	Rank find(T const& e, Rank lo, Rank hi) const;  //���������������
	Rank find(T const& e) const { find(e, 0, _size); }  //���������������
	Rank search(T const& e, Rank lo, Rank hi) const; //���������������
	Rank search(T const& e) const  //���������������
	{
		return (_size <= 0) ? -1 : search(e, 0, _size);
	}

	//��д���ʽӿ�
	T& operator[](Rank r) const;  //�����±������������������������ʽ���ø�Ԫ��
	Vector<T>& operator= (Vector<T> const&);  //���ظ�ֵ���������Ա�ֱ�ӿ�¡����
	T remove(Rank r); //ɾ����Ϊr��Ԫ��
	int remove(Rank lo, Rank hi); //ɾ�������ȼ�[lo, hi)֮�ڵ�Ԫ��
	Rank insert(Rank r, T const& e); //����Ԫ��
	Rank insert(T const& e) { Rank i = insert(_size, e); return i; }  //Ĭ����ΪĩԪ�ز���
	void sort(Rank lo, Rank hi); //��[lo, hi)����
	void sort() { sort(0, _size); } //��������
	void unsort(Rank lo, Rank hi); //��[lo, hi)����
	int deduplicate(); //����ȥ��
	int uniquify(); //����ȥ��

	//����
	void traverse(void (*)(T&)); //������ʹ�ú���ָ�룬ֻ�����߾ֲ����޸ģ�
	template <typename VST> void traverse(VST&); //������ʹ�ú������󣬿�ȫ�����޸ģ�
};


template <typename T>
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi) {
	_elem = new T[_capacity = 2 * (hi - lo)]; //����ռ�
	_size = 0;	//��ģ��0
	while (lo < hi)
	{
		_elem[_size++] = A[lo++];
	}
}
//=����
template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T> const& V) {
	if (_elem) delete[] _elem; //�ͷ�ԭ������
	copyFrom(V, V._elem, V.size());	//���帴��
	return *this; //���ص�ǰ��������ã��Ա���ʽ��ֵ
}

//����
template <typename T>
void Vector<T>::expand() {
	if (_size < _capacity) return;
	if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;
	T* oldElem = _elem;
	_elem = new T[_capacity <<= 1]; //�����ӱ�
	for (int i = 0; i < _size; ++i)
		_elem[i] = oldElem[i];
	delete[] oldElem;
}

//����
template <typename T>
void Vector<T>::shrink() {
	if (_capacity < DEFAULT_CAPACITY << 1) return;//����������DEFAULT_CAPACITY����
	if (_size << 2 > _capacity) return; //��25%Ϊ��
	T* oldElem = _elem;
	_elem = new T[_capacity >>= 1];   //��������
	for (int i = 0; i < _size; ++i)
		_elem[i] = oldElem[i];
	delete[] oldElem;
}

//�����±������
template <typename T>
T& Vector<T>::operator[](Rank r) const {
	return _elem[r];
}


//�������������ʹ��Ԫ�صȸ��ʳ�����ÿһλ��
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

template <typename T> // ����������˳����ң��������һ��Ԫ��e��λ�ã�ʧ��ʱ������lo - 1
Rank Vector<T>::find(T const& e, Rank lo, Rank hi) const {
	//while ((lo < hi--) && (e != _elem[hi]));
	while (lo < hi--)  //���ж��Ԫ�أ��������������
	{
		if (e == _elem[hi])
			return hi;
	}
	return hi;
}

//����Ԫ��
template <typename T>
Rank Vector<T>::insert(Rank r, T const& e) {
	expand();
	for (int i = _size; i > r; --i)
		_elem[i] = _elem[i - 1];
	_elem[r] = e;
	++_size;
	return r;
}

//ɾ������Ԫ��
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


//ɾ������Ԫ��
template <typename T>
T Vector<T>::remove(Rank r) {
	T e = _elem[r];
	remove(r, r + 1);
	return e;
}

template <typename T>
int Vector<T>::deduplicate() { //ɾ�������������ظ�Ԫ��
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
int Vector<T>::uniquify() {//ɾ�������������ظ�Ԫ�أ�˫ָ�룩
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


template <typename T> template < typename VST> //Ԫ�����͡�������
void Vector<T>::traverse(VST& visit) //���ú���������Ƶı���
{
	for (int i = 0; i < _size; i++) visit(_elem[i]);
}