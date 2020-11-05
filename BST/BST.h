#pragma once
#include <iostream>
using namespace std;
#include "../BinTree/BinTree.h"

template <typename T>
class BST :public BinTree<T> {
protected:
	BinNodePosi(T) _hot; //BST::search()�����ʵķǿգ��������գ��Ľڵ�λ��
	BinNodePosi(T) connect34( //���ա�3 + 4���ṹ������3���ڵ㼰�Ŀ�����
		BinNodePosi(T), BinNodePosi(T), BinNodePosi(T),
		BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T));
	BinNodePosi(T) rotateAt(BinNodePosi(T) x); //��x���丸�ס��游��ͳһ��ת����

//�����ӿڣ���virtual���Σ�ǿ��Ҫ�����������ࣨ BST���֣����ݸ��ԵĹ��������д
public:
	virtual BinNodePosi(T)& search(const T& e); //����
	virtual BinNodePosi(T) insert(const T & e); //����
	virtual bool remove(const T & e); //ɾ��
};

template <typename T>
static BinNodePosi(T)& searchIn(BinNodePosi(T)& v, const T& e, BinNodePosi(T)& hot) {
	if (!v || (e == v->data)) return v;
	hot = v;
	return searchIn(((e < v->data) ? v->lChild : v->rChild), e, hot);
}

template <typename T>
BinNodePosi(T)& BST<T>::search(const T& e) {
	return searchIn(_root, e, _hot = NULL);
}

template <typename T> BinNodePosi(T) BST<T>::insert(const T& e) { //���ؼ���e����BST����
	BinNodePosi(T)& x = search(e);
	if(x)
		return x;
	x = new BinNode<T>(e, _hot);
	_size++;
	updateHeightAbove(x);
	return x;
}

/******************************************************************************************
* BST�ڵ�ɾ���㷨��ɾ��λ��x��ָ�Ľڵ㣨ȫ�־�̬ģ�庯����������AVL�� Splay�� RedBlack�ȸ���BST��
* x�ɴ�ǰ�Ĳ���ȷ��������ȷ�Ϸ�NULL�󷽵��ñ��������ʱ�ɾ���ɹ�
* ��searchIn��ͬ������֮ǰ���ؽ�hot�ÿ�
* ����ֵָ��ʵ�ʱ�ɾ���ڵ�Ľ����ߣ� hotָ��ʵ�ʱ�ɾ���ڵ�ĸ��ס������߾��п�����NULL
******************************************************************************************/

template <typename T> static BinNodePosi(T) removeAt(BinNodePosi(T)& x, BinNodePosi(T)& hot) {
	BinNodePosi(T) w = x;
	BinNodePosi(T) succ = NULL;
	if (!HasLChild(*x))
		succ = x = x->rChild;
	else if (!HasRChild(*x))
		succ = x = x->lChild;
	else {
		w = w->succ();
		swap(x->data, w->data);
		BinNodePosi(T) u = w->parent;
		((u == x) ? u->rChild : u->lChild) = succ = w->rChild;
	}
	hot = w->parent;
	if (succ)
		succ->parent = hot;
	release(w->data);
	release(w);
	return succ;
}

template <typename T> bool BST<T>::remove(const T& e) { //��BST����ɾ���ؼ���e
	BinNodePosi(T)& x = search(e);
	if (!x)
		return false;
	removeAt(x, _hot);
	_size--;
	updateHeightAbove(_hot);
	return true;
}