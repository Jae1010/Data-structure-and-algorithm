#pragma once
#include <iostream>

typedef int Rank; //秩
#define ListNodePosi(T) ListNode<T>* //列表节点位置

template <typename T>
struct ListNode
{
	T data;		//数值
	ListNodePosi(T) pred;	//前驱
	ListNodePosi(T) succ;	//后继
	ListNode() {}
	ListNode(T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL) :
		data(e), pred(p), succ(s) {}
	ListNodePosi(T) insertAsPred(T const& e); //紧靠当前节点之前插入新节点
	ListNodePosi(T) insertAsSucc(T const& e); //紧随当前节点之后插入新节点
};

template <typename T> class List {
private:
	int _size;  //规模
	ListNodePosi(T) header; //头哨兵
	ListNodePosi(T) trailer;  //尾哨兵

protected:
	void init(); //列表创建初始化
	int clear(); //清除所有节点
	void copyNodes(ListNodePosi(T) p, int n); //复制列表中自位置p起的n项
	void merge(ListNodePosi(T)& p, int n, List<T>& L, ListNodePosi(T) q, int m); //有序列表区间归并
	void mergeSort(ListNodePosi(T)& p, int n); //对从p开始连续的n个节点归并排序
	void selectionSort1(ListNodePosi(T) p, int n); //对从p开始连续的n个节点选择排序
	void selectionSort2(ListNodePosi(T) p, int n); //对从p开始连续的n个节点选择排序
	void insertionSort(ListNodePosi(T) p, int n); //对从p开始连续的n个节点插入排序

public:
	List() { init(); }//默认
	List(List<T> const& L);//复制构造
	List(List<T> const& L, Rank r, int n); //复制列表L中自第r项起的n项
	List(ListNodePosi(T) p, int n); //复制列表中自位置p起的n项
	~List();
	//只读访问接口
	Rank size() const { return _size; } //规模
	Rank rank(ListNodePosi(T) p);  //返回当前的秩
	bool empty() const { return _size <= 0; } //判空
	T& operator[](Rank r) const; //重载，支持寻秩访问，效率低
	ListNodePosi(T) first() const { return header->succ; }
	ListNodePosi(T) last() const { return trailer->pred; }
	bool valid(ListNodePosi(T) p) const { //判断位置p是否对外合法
		return p && (trailer != p) && (header != p);
	}
	int disordered() const; //判断列表是否已排序
	ListNodePosi(T) find(T const& e) const //无序列表查找
	{
		return find(e, _size, trailer);
	}
	ListNodePosi(T) find(T const& e, int n, ListNodePosi(T) p) const; //无序区间查找
	ListNodePosi(T) search(T const& e) const //有序列表查找
		{ return search(e, _size, trailer); }
	ListNodePosi(T) search(T const& e, int n, ListNodePosi(T) p) const; //有序区间查找
	ListNodePosi(T) selectMax(ListNodePosi(T) p, int n); //在p及其前n-1个后继中选出最大者
	ListNodePosi(T) selectMax() { return selectMax(header->succ, _size); }//整体最大者

	//可写访问接口
	ListNodePosi(T) insertAsFirst(T const& e); //将e当作首节点插入
	ListNodePosi(T) insertAsLast(T const& e); //将e当作末节点插入
	ListNodePosi(T) insertBefore(ListNodePosi(T) p, T const& e); //将e当作p的前驱插入
	ListNodePosi(T) insertAfter(ListNodePosi(T) p, T const& e); //将e当作p的后继插入
	T remove(ListNodePosi(T) p); //删除合法位置p处的节点,返回被删除节点
	void merge(List<T>& L) { merge(first(), size, L, L.first(), L._size); }//全列表归并
	void sort(ListNodePosi(T) p, int n); //列表区间排序
	void sort() { sort(first(), _size); } //列表整体排序
	int deduplicate(); //无序去重
	int uniquify(); //有序去重
	void reverse(); //前后倒置
	//遍历
	void traverse(void (*)(T&)); //遍历，依次实施visit操作（函数指针，只读或局部性修改）
	template < typename VST> //操作器
	void traverse(VST&); //遍历，依次实施visit操作（函数对象，可全局性修改）
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

template < typename T> //列表内部方法：复制列表中自位置p起的n项
void List<T>::copyNodes(ListNodePosi(T) p, int n) {
	init();
	while ( n-- )
	{
		insertAsLast(p->data);
		p = p->succ;
	}
}
template <typename T>
List<T>::List(List<T> const& L) { //整体复制列表
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

template <typename T> void List<T>::traverse(void (*visit)(T&)) //利用函数指针机制的遍历
{ for (ListNodePosi(T) p = header->succ; p != trailer; p = p->succ) visit(p->data); }

template <typename T> template < typename VST> //元素类型、操作器
void List<T>::traverse(VST & visit) //利用函数对象机制的遍历
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
}  //失败时，返回区间左边界的前驱（可能是header） ——调用者可通过valid()判断成功不否

template <typename T> void List<T>::sort(ListNodePosi(T) p, int n) { //列表区间排序
	//switch (rand() % 3) { //随机选择排序算法。可根据具体问题的特点灵活选择或扩充
	//case 1: insertionSort(p, n); break; //插入排序
	//case 2: selectionSort(p, n); break; //选择排序
	//default: mergeSort(p, n); break; //归并排序
	//}
	mergeSort(p, n);
}


template <typename T>//插入排序
void List<T>::insertionSort(ListNodePosi(T) p, int n) {//对从p开始连续的n个节点插入排序
	for (int i = 0; i < n; ++i) {
		insertAfter(search(p->data, i, p), p->data);
		p = p->succ;
		remove(p->pred);
	}
}


template <typename T>//选择排序  a区间为有序区间，b区间为无序区间
void List<T> ::selectionSort1(ListNodePosi(T) p, int n) {
	ListNodePosi(T) stable = insertBefore(p, 0);  //这种方法需要一个不能被删除的参照
	ListNodePosi(T) head = stable->pred;		//曾引发0xDDDDDDDD错误--引用的内存/对象已被删除

	for (int i = n; i > 0; --i) { //问题解决
		ListNodePosi(T) max = selectMax(stable->succ, i);//以stable为参照，逐步找到当前区间的最大值
		insertAfter(head, remove(max));
	}
	remove(stable);
}

template < typename T> //选择排序   a区间为无序区间，b区间为有序区间
void List<T>::selectionSort2(ListNodePosi(T) p, int n) { 
	ListNodePosi(T) head = p->pred; ListNodePosi(T) tail = p;
	for (int i = 0; i < n; i++) tail = tail->succ; 
	while (1 < n) { //在至少还剩两个节点之前，在待排序区间内
		ListNodePosi(T) max = selectMax(head->succ, n); //找出最大者
		insertBefore(tail, remove(max)); 
		tail = tail->pred; n--;
		
	}
}

template < typename T> //从起始于位置p的n个元素中选出最大者
ListNodePosi(T) List<T>::selectMax(ListNodePosi(T) p, int n) {
	ListNodePosi(T) max = p;
	for (int i = 1; i < n; ++i) {
		if ((p = p->succ)->data >= max->data)
			max = p;
	}
	return max;
}

template < typename T> //有序列表的归并：当前列表中自p起的n个元素，与列表L中自q起的m个元素归并
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

template < typename T> //列表的归并排序算法：对起始于位置p的n个元素排序
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