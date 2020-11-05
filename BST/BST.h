#pragma once
#include <iostream>
using namespace std;
#include "../BinTree/BinTree.h"

template <typename T>
class BST :public BinTree<T> {
protected:
	BinNodePosi(T) _hot; //BST::search()最后访问的非空（除非树空）的节点位置
	BinNodePosi(T) connect34( //按照“3 + 4”结构，联接3个节点及四棵子树
		BinNodePosi(T), BinNodePosi(T), BinNodePosi(T),
		BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T));
	BinNodePosi(T) rotateAt(BinNodePosi(T) x); //对x及其父亲、祖父做统一旋转调整

//基本接口：以virtual修饰，强制要求所有派生类（ BST发种）根据各自的规则对其重写
public:
	virtual BinNodePosi(T)& search(const T& e); //查找
	virtual BinNodePosi(T) insert(const T & e); //插入
	virtual bool remove(const T & e); //删除
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

template <typename T> BinNodePosi(T) BST<T>::insert(const T& e) { //将关键码e插入BST树中
	BinNodePosi(T)& x = search(e);
	if(x)
		return x;
	x = new BinNode<T>(e, _hot);
	_size++;
	updateHeightAbove(x);
	return x;
}

/******************************************************************************************
* BST节点删除算法：删除位置x所指的节点（全局静态模板函数，适用于AVL、 Splay、 RedBlack等各种BST）
* x由此前的查找确定，并经确认非NULL后方调用本函数，故必删除成功
* 与searchIn不同，调用之前不必将hot置空
* 返回值指向实际被删除节点的接替者， hot指向实际被删除节点的父亲——二者均有可能是NULL
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

template <typename T> bool BST<T>::remove(const T& e) { //从BST树中删除关键码e
	BinNodePosi(T)& x = search(e);
	if (!x)
		return false;
	removeAt(x, _hot);
	_size--;
	updateHeightAbove(_hot);
	return true;
}