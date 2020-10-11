#include  "Vector.h"
#include <ctime>

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


//ɾ����Ԫ��
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
void Vector<T>::traverse(VST & visit) //���ú���������Ƶı���
{ for (int i = 0; i < _size; i++) visit(_elem[i]); }

