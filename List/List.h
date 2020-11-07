#pragma once
#include <iostream>

typedef int Rank; //��
#define ListNodePosi(T) ListNode<T>* //�б�ڵ�λ��

template <typename T>
struct ListNode
{
	T data;		//��ֵ
	ListNodePosi(T) pred;	//ǰ��
	ListNodePosi(T) succ;	//���
	ListNode() {}
	ListNode(T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL) :
		data(e), pred(p), succ(s) {}
	ListNodePosi(T) insertAsPred(T const& e); //������ǰ�ڵ�֮ǰ�����½ڵ�
	ListNodePosi(T) insertAsSucc(T const& e); //���浱ǰ�ڵ�֮������½ڵ�
};

template <typename T> class List {
private:
	int _size;  //��ģ
	ListNodePosi(T) header; //ͷ�ڱ�
	ListNodePosi(T) trailer;  //β�ڱ�

protected:
	void init(); //�б�����ʼ��
	int clear(); //������нڵ�
	void copyNodes(ListNodePosi(T) p, int n); //�����б�����λ��p���n��
	void merge(ListNodePosi(T)& p, int n, List<T>& L, ListNodePosi(T) q, int m); //�����б�����鲢
	void mergeSort(ListNodePosi(T)& p, int n); //�Դ�p��ʼ������n���ڵ�鲢����
	void selectionSort1(ListNodePosi(T) p, int n); //�Դ�p��ʼ������n���ڵ�ѡ������
	void selectionSort2(ListNodePosi(T) p, int n); //�Դ�p��ʼ������n���ڵ�ѡ������
	void insertionSort(ListNodePosi(T) p, int n); //�Դ�p��ʼ������n���ڵ��������

public:
	List() { init(); }//Ĭ��
	List(List<T> const& L);//���ƹ���
	List(List<T> const& L, Rank r, int n); //�����б�L���Ե�r�����n��
	List(ListNodePosi(T) p, int n); //�����б�����λ��p���n��
	~List();
	//ֻ�����ʽӿ�
	Rank size() const { return _size; } //��ģ
	Rank rank(ListNodePosi(T) p);  //���ص�ǰ����
	bool empty() const { return _size <= 0; } //�п�
	T& operator[](Rank r) const; //���أ�֧��Ѱ�ȷ��ʣ�Ч�ʵ�
	ListNodePosi(T) first() const { return header->succ; }
	ListNodePosi(T) last() const { return trailer->pred; }
	bool valid(ListNodePosi(T) p) const { //�ж�λ��p�Ƿ����Ϸ�
		return p && (trailer != p) && (header != p);
	}
	int disordered() const; //�ж��б��Ƿ�������
	ListNodePosi(T) find(T const& e) const //�����б����
	{
		return find(e, _size, trailer);
	}
	ListNodePosi(T) find(T const& e, int n, ListNodePosi(T) p) const; //�����������
	ListNodePosi(T) search(T const& e) const //�����б����
		{ return search(e, _size, trailer); }
	ListNodePosi(T) search(T const& e, int n, ListNodePosi(T) p) const; //�����������
	ListNodePosi(T) selectMax(ListNodePosi(T) p, int n); //��p����ǰn-1�������ѡ�������
	ListNodePosi(T) selectMax() { return selectMax(header->succ, _size); }//���������

	//��д���ʽӿ�
	ListNodePosi(T) insertAsFirst(T const& e); //��e�����׽ڵ����
	ListNodePosi(T) insertAsLast(T const& e); //��e����ĩ�ڵ����
	ListNodePosi(T) insertBefore(ListNodePosi(T) p, T const& e); //��e����p��ǰ������
	ListNodePosi(T) insertAfter(ListNodePosi(T) p, T const& e); //��e����p�ĺ�̲���
	T remove(ListNodePosi(T) p); //ɾ���Ϸ�λ��p���Ľڵ�,���ر�ɾ���ڵ�
	void merge(List<T>& L) { merge(first(), size, L, L.first(), L._size); }//ȫ�б�鲢
	void sort(ListNodePosi(T) p, int n); //�б���������
	void sort() { sort(first(), _size); } //�б���������
	int deduplicate(); //����ȥ��
	int uniquify(); //����ȥ��
	void reverse(); //ǰ����
	//����
	void traverse(void (*)(T&)); //����������ʵʩvisit����������ָ�룬ֻ����ֲ����޸ģ�
	template < typename VST> //������
	void traverse(VST&); //����������ʵʩvisit�������������󣬿�ȫ�����޸ģ�
};

template <typename T>
void List<T>::init() {
	header = new ListNode<T>;
	trailer = new ListNode<T>;
	header->succ = trailer;
	header->pred = NULL;
	trailer->pred = header;
	trailer->succ = NULL;
	_size = 0;
}

template <typename T>
T& List<T>::operator[](Rank r) const{
	ListNodePosi(T) p = first();
	while ( r-- > 0 )
	{
		p = p->succ;
	}
	return p->data;
}

template <typename T>
Rank List<T>::rank(ListNodePosi(T) p) {
	Rank n = 0;
	while (p->pred != header)
	{
		n++;
		p = p->pred;
	}
	return n;
}

template <typename T>
ListNodePosi(T) List<T>::find(T const& e, int n, ListNodePosi(T) p) const {
	while (n-- > 0)
	{
		p = p->pred;
		if (p->data == e)
			return p;
	}
	return NULL;
}

template <typename T>
ListNodePosi(T) ListNode<T>::insertAsPred(T const& e) {
	ListNodePosi(T) p = new ListNode<T>(e, pred, this);
	pred->succ = p;
	pred = p;
	return p;
}

template <typename T>
ListNodePosi(T) ListNode<T>::insertAsSucc(T const& e) {
	ListNodePosi(T) p = new ListNode<T>(e, this, succ);
	succ->pred = p;
	succ = p;
	return p;
}


template <typename T> 
ListNodePosi(T) List<T>::insertAsFirst(T const& e) {
	_size++;
	return header->insertAsSucc(e);
}

template <typename T> 
ListNodePosi(T) List<T>::insertAsLast(T const& e) {
	_size++;
	return trailer->insertAsPred(e);
}

template <typename T> 
ListNodePosi(T) List<T>::insertBefore(ListNodePosi(T) p, T const& e) {
	_size++;
	return p->insertAsPred(e);
}

template <typename T> 
ListNodePosi(T) List<T>::insertAfter(ListNodePosi(T) p, T const& e) {
	_size++;
	return p->insertAsSucc(e);
}

template < typename T> //�б��ڲ������������б�����λ��p���n��
void List<T>::copyNodes(ListNodePosi(T) p, int n) {
	init();
	while ( n-- )
	{
		insertAsLast(p->data);
		p = p->succ;
	}
}
template <typename T>
List<T>::List(List<T> const& L) { //���帴���б�
	copyNodes(L.first(), L._size);
}

template <typename T>
List<T>::List(ListNodePosi(T) p, int n) {
	copyNodes(p, n);
}

template <typename T>
List<T>::List(List<T> const& L, Rank r, int n) {
	copyNodes(find(L[r]), n);
}

template <typename T> 
T List<T>::remove(ListNodePosi(T) p) {
	T oldData = p->data;
	p->pred->succ = p->succ;
	p->succ->pred = p->pred;
	delete p;
	_size--;
	return oldData;
}

template <typename T>
int List<T>::clear() {
	int oldSize = _size;
	while (_size)
	{
		remove(header->succ);
	}
	return oldSize;
}

template <typename T>
List<T>::~List() {
	clear();
	delete header;
	delete trailer;
}

template <typename T>
int List<T>::deduplicate() {
	if (_size < 2) return 0;
	int oldSize = _size;
	ListNodePosi(T) p = first();
	Rank i = 0;
	while (p != trailer)
	{
		if (find(p->data, i, p)) {
			remove(p);
		}
		++i;
		p = p->succ;
	}
	return oldSize - _size;
}

template <typename T> void List<T>::traverse(void (*visit)(T&)) //���ú���ָ����Ƶı���
{ for (ListNodePosi(T) p = header->succ; p != trailer; p = p->succ) visit(p->data); }

template <typename T> template < typename VST> //Ԫ�����͡�������
void List<T>::traverse(VST & visit) //���ú���������Ƶı���
{ for (ListNodePosi(T) p = header->succ; p != trailer; p = p->succ) visit(p->data); }


template <typename T> 
int List<T>::uniquify() {
	if (_size < 2) return 0;
	int oldSize = _size;
	ListNodePosi(T) s = header;
	ListNodePosi(T) f = first();
	for (; f != trailer; s = f, f = f->succ) {
		if (s->data == f->data) {
			remove(f);
			f = s;
		}
	}
	return oldSize - _size;
}

template <typename T>
ListNodePosi(T) List<T>::search(T const& e, int n, ListNodePosi(T) p) const{
	while (n-- >= 0) {
		if (((p = p->pred)->data) <= e)
			break;
	}
	return p;
}  //ʧ��ʱ������������߽��ǰ����������header�� ���������߿�ͨ��valid()�жϳɹ�����

template <typename T> void List<T>::sort(ListNodePosi(T) p, int n) { //�б���������
	//switch (rand() % 3) { //���ѡ�������㷨���ɸ��ݾ���������ص����ѡ�������
	//case 1: insertionSort(p, n); break; //��������
	//case 2: selectionSort(p, n); break; //ѡ������
	//default: mergeSort(p, n); break; //�鲢����
	//}
	mergeSort(p, n);
}


template <typename T>//��������
void List<T>::insertionSort(ListNodePosi(T) p, int n) {//�Դ�p��ʼ������n���ڵ��������
	for (int i = 0; i < n; ++i) {
		insertAfter(search(p->data, i, p), p->data);
		p = p->succ;
		remove(p->pred);
	}
}


template <typename T>//ѡ������  a����Ϊ�������䣬b����Ϊ��������
void List<T> ::selectionSort1(ListNodePosi(T) p, int n) {
	ListNodePosi(T) stable = insertBefore(p, 0);  //���ַ�����Ҫһ�����ܱ�ɾ���Ĳ���
	ListNodePosi(T) head = stable->pred;		//������0xDDDDDDDD����--���õ��ڴ�/�����ѱ�ɾ��

	for (int i = n; i > 0; --i) { //������
		ListNodePosi(T) max = selectMax(stable->succ, i);//��stableΪ���գ����ҵ���ǰ��������ֵ
		insertAfter(head, remove(max));
	}
	remove(stable);
}

template < typename T> //ѡ������   a����Ϊ�������䣬b����Ϊ��������
void List<T>::selectionSort2(ListNodePosi(T) p, int n) { 
	ListNodePosi(T) head = p->pred; ListNodePosi(T) tail = p;
	for (int i = 0; i < n; i++) tail = tail->succ; 
	while (1 < n) { //�����ٻ�ʣ�����ڵ�֮ǰ���ڴ�����������
		ListNodePosi(T) max = selectMax(head->succ, n); //�ҳ������
		insertBefore(tail, remove(max)); 
		tail = tail->pred; n--;
		
	}
}

template < typename T> //����ʼ��λ��p��n��Ԫ����ѡ�������
ListNodePosi(T) List<T>::selectMax(ListNodePosi(T) p, int n) {
	ListNodePosi(T) max = p;
	for (int i = 1; i < n; ++i) {
		if ((p = p->succ)->data >= max->data)
			max = p;
	}
	return max;
}

template < typename T> //�����б�Ĺ鲢����ǰ�б�����p���n��Ԫ�أ����б�L����q���m��Ԫ�ع鲢
void List<T>::merge(ListNodePosi(T)& p, int n, List<T>& L, ListNodePosi(T) q, int m) {
	ListNodePosi(T) head = p->pred;
	while (m > 0) {
		while (n > 0)
		{
			if (p->data > q->data) {
				insertAfter(head, q->data);
				q = q->succ;
				L.remove(q->pred);
				m--;
			}
			else {
				insertAfter(head, p->data);
				p = p->succ;
				remove(p->pred);
				n--;
			}
		}
		insertAfter(head, q->data);
		q = q->succ;
		L.remove(q->pred);
		m--;
	}
	p = head->succ;
}

template < typename T> //�б�Ĺ鲢�����㷨������ʼ��λ��p��n��Ԫ������
void List<T>::mergeSort(ListNodePosi(T)& p, int n) {
	if (n < 2) return;
	int m = n >> 1;
	ListNodePosi(T) q = p;
	for (int i = 0; i < m; ++i)
		q = q->succ;
	mergeSort(p, m);
	mergeSort(q, n - m);
	merge(p, m, *this, q, n - m);
}