#pragma once
#include <iostream>

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
	Rank insert(T const& e) { insert(_size, e); }  //Ĭ����ΪĩԪ�ز���
	void sort(Rank lo, Rank hi); //��[lo, hi)����
	void sort() { sort(0, _size); } //��������
	void unsort(Rank lo, Rank hi); //��[lo, hi)����
	int deduplicate(); //����ȥ��
	int uniquify(); //����ȥ��

	//����
	void traverse(void (*)(T&)); //������ʹ�ú���ָ�룬ֻ�����߾ֲ����޸ģ�
	template <typename VST> void traverse(VST&); //������ʹ�ú������󣬿�ȫ�����޸ģ�
};