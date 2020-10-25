#pragma once
#include "BinNode.h"

template <typename T> class BinTree {
protected:
	int _size;	//觃模
	BinNodePosi(T) _root;	//根节点
	virtual int updateHeight(BinNodePosi(T) x); //更新节点x的高度
	void updateHeightAbove(BinNodePosi(T) x); //更新节点x及其祖先的高度
public:
	BinTree() :_size(0), _root(NULL) {}
	~BinTree() { if (0 < _size) remove(_root); }
	int size()const { return _size; }
	bool empty()const { return !_root }
	BinNodePosi(T) root() const { return _root; }
	BinNodePosi(T) insertAsRoot(T const& e); //插入根节点
	BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const& e); //e作为x的左孩子（原无）插入
	BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const& e); //e作为x的右孩子（原无）插入
	BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T>* &T); //T作为x左子树接入
	BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T>* &T); //T作为x右子树接入
	int remove(BinNodePosi(T) x); //删除以位置x处节点为根的子树，返回该子树原先的规模
	BinTree<T>* secede(BinNodePosi(T) x); //将子树x从当前树中摘除，幵将其转换为一棵独立子树
	template < typename VST> //操作器
	void travLevel(VST & visit) { if (_root) _root->travLevel(visit); } //局次遍历
	template < typename VST> //操作器
	void travPre(VST & visit) { if (_root) _root->travPre(visit); } //先序遍历
	template < typename VST> //操作器
	void travIn(VST & visit) { if (_root) _root->travIn(visit); } //中序遍历
	template < typename VST> //操作器
	void travPost(VST & visit) { if (_root) _root->travPost(visit); } //后序遍历
	// 比较器、判等器（各列其一，其余自行补充）
	bool operator<(BinTree<T> const& t) { return _root && t._root && lt(_root, t._root); }
	bool operator==(BinTree<T> const& t) { return _root && t._root && (_root == t._root); }


};

template <typename T> 
int BinTree<T>::updateHeight(BinNodePosi(T) x) { //更新节点x高度
	return x->hight = 1 + max(stature(x->lChild), stature(x->rChild));
}

template <typename T>
void BinTree<T> ::updateHeightAbove(BinNodePosi(T) x) {//更新v及祖先的高度
	while (x)
	{
		updateHeight(x);  
		x = x->parent;
	}
}

template <typename T>//将e作作根节点插入空的二叉树
BinNodePosi(T) BinTree<T>::insertAsRoot(T const &e) {
	_size = 1;
	return _root = new BinNode<T>(e);
}

template <typename T>//e插入为x的左孩子
BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x, T const& e) {
	_size++;
	x->insertAsLC(e);
	updateHeightAbove(x);
	return x->lChild;
}

template <typename T>//e插入为x的右孩子
BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x, T const& e) {
	_size++;
	x->insertAsRC(e);
	updateHeightAbove(x);
	return x->rChild;
}

template <typename T>//二叉树子树接入算法：将S当作节点x的左子树接入， S本身置空
BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T) x, BinTree<T>* &S) {
	if (x->lChild = S->_root) {
		x->lChild->parent = x;
		_size += S->_size;
		updateHeightAbove(x);
		S->_root = nullptr;
		S->_size = 0;
		release(S);
		S = nullptr;
	}
	return x;
}

template <typename T>//二叉树子树接入算法：将S当作节点x的右子树接入， S本身置空
BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T) x, BinTree<T>*& S) {
	if (x->rChild = S->_root) {
		x->rChild->parent = x;
		_size += S->_size;
		updateHeightAbove(x);
		S->_root = nullptr;
		S->_size = 0;
		release(S);
		S = nullptr;
	}
	return x;
}

template < typename T> //删除二叉树中位置x处的节点及其后代，返回被删除节点的数值
int BinTree<T>::remove(BinNodePosi(T) x) {
	FromParentTo(*x) = nullptr;
	updateHeight(x->parent);
	int n = removeAt(x);
	_size -= n;
	return n;
}

template < typename T> //删除二叉树中位置x处的节点及其后代，返回被删除节点的数值
static int removeAt(BinNodePosi(T) x) { 
	if (!x) return 0; //递归基：空树
	int n = 1 + removeAt(x->lChild) + removeAt(x->rChild); //递归释放左、右子树
	release(x->data); release(x); return n; //释放被摘除节点，并返回初除节点总数
}

template < typename T> //二叉树子树分离算法：将子树x从当前树中摘除，将其封装为一棵独立子树返回
BinTree<T>* BinTree<T>::secede(BinNodePosi(T) x) {
	FromParentTo(*x) = nullptr;
	updateHeightAbove(x->parent);
	BinTree<T>* S = new BinTree<T>;
	S->_root = x;
	x->parent = nullptr;
	S->_size = x->size();
	_size -= S->_size;
	return S;
}

