#pragma once
#include "../BST.h"

template <typename T>
class Splay :public BST<T> {
protected:
	BinNodePosi(T) splay(BinNodePosi(T) v); //将节点v伸展至根
public:
	BinNodePosi(T)& search(const T& e); //查找（重写）
	BinNodePosi(T) insert(const T& e); //插入（重写）
	bool remove(const T& e); //删除（重写）
};

template <typename NodePosi> inline //在节点*p与*lc（可能为空）之间建立父（左）子关系
void attachAsLChild(NodePosi p, NodePosi lc) { p->lChild = lc; if (lc) lc->parent = p; }
template <typename NodePosi> inline //在节点*p与*rc（可能为空）之间建立父（右）子关系
void attachAsRChild(NodePosi p, NodePosi rc) { p->rChild = rc; if (rc) rc->parent = p; }

template <typename T>
BinNodePosi(T) Splay<T>::splay(BinNodePosi(T) v) {
	if (!v) return NULL;
	BinNodePosi(T) p;
	BinNodePosi(T) g;
	while ((p = v->parent) && (g = p->parent))
	{
		BinNodePosi(T) gg = g->parent; //每轮之后都以原曾祖父（ great-grand parent）为父
		if (IsLChild(*v))
			if (IsLChild(*p)) { //zig-zig
				attachAsLChild(g, p->rChild); attachAsLChild(p, v->rChild);
				attachAsRChild(p, g); attachAsRChild(v, p);
			}
			else { //zig-zag
				attachAsLChild(p, v->rChild); attachAsRChild(g, v->lChild);
				attachAsLChild(v, g); attachAsRChild(v, p);
			}
		else if (IsRChild(*p)) { //zag-zag
			attachAsRChild(g, p->lChild); attachAsRChild(p, v->lChild);
			attachAsLChild(p, g); attachAsLChild(v, p);
		}
		else { //zag-zig
			attachAsRChild(p, v->lChild); attachAsLChild(g, v->rChild);
			attachAsRChild(v, g); attachAsLChild(v, p);
		}
		if (!gg) v->parent = NULL;
		else
		{
			(g == gg->lChild) ? attachAsLChild(gg, v) : attachAsRChild(gg, v);
		}
		updateHeight(g); updateHeight(p); updateHeight(v);
	}
	if (p = v->parent) {
		if (IsLChild(*v)) {
			attachAsLChild(p, v->rChild); attachAsRChild(v, p);
		}
		else
		{
			attachAsRChild(p, v->lChild); attachAsLChild(v, p);
		}
		updateHeight(p); updateHeight(v);
	}
	v->parent = NULL;
	return v;
}

template <typename T> BinNodePosi(T)& Splay<T>::search(const T& e) { //在伸展树中查找关键码e
	BinNodePosi(T) p = searchIn(_root, e, _hot = NULL);
	_root = splay((p ? p : _hot));
	return _root;
}

template <typename T>
BinNodePosi(T) Splay<T>::insert(const T& e) {
	if (!_root) { _size++; return _root = new BinNode<T>(e); }
	if (e == search(e)->data) return _root;
	_size++; BinNodePosi(T) t = _root;
	if (_root->data < e) {
		t->parent = _root = new BinNode<T>(e, NULL, t, t->rChild);
		if (HasRChild(*t))
		{
			t->rChild->parent = _root;
			t->rChild = NULL;
		}
	}
	else
	{
		t->parent = _root = new BinNode<T>(e, NULL, t->lChild, t);
		if (HasLChild(*t))
		{
			t->lChild->parent = _root;
			t->lChild = NULL;
		}
	}
	updateHeightAbove(t); //更新t及其祖先（实际上叧有_root一个）的高度
	return _root; //新节点必然置于树根，返回之
}

template <typename T>
bool Splay<T>::remove(const T& e) {
	if (!_root || e != search(e)->data) return false;
	BinNodePosi(T) w = _root;
	if (!HasLChild(*_root)) {
		_root = _root->rChild;
		if (_root)
			_root->parent = NULL;
	}
	else if (!HasRChild(*_root)) {
		_root = _root->lChild;
		if (_root)
			_root->parent = NULL;
	}
	else
	{
		BinNodePosi(T) lTree = _root->lChild;
		lTree->parent = NULL;
		_root->lChild = NULL;
		_root = _root->rChild;
		_root->parent = NULL;
		search(w->data);
		_root->lChild = lTree;
		lTree->parent = _root;
	}
	release(w->data);
	release(w);
	_size--;
	if(_root)
		updateHeight(_root);
	return true;
}
