#pragma once
#include "../BST.h"

#define Balanced(x) (stature((x).lChild) == stature((x).rChild))  //理想平衡条件
#define BalFac(x) (stature((x).lChild) - stature((x).rChild))//平衡因子
#define AvlBalanced(x) ((-2 < BalFac(x)) && (BalFac(x) < 2))//AVL平衡条件

template <typename T> class AVL :public BST<T> {
public:
	BinNodePosi(T) insert(const T& e); //插入（重写）
	bool remove(const T& e); //删除（重写）
	// BST::search()等其余接口可直接沿用
};

/******************************************************************************************
 * 在左、右孩子中取更高者，若等高，则与父亲p同侧者优先
 * 在AVL平衡调整前，借此确定重构方案
 ******************************************************************************************/
#define tallerChild(x) (\
	stature((x)->lChild) > stature((x)->rChild) ? (x)->lChild : (\
	stature((x)->rChild) > stature((x)->lChild) ? (x)->rChild : (\
	IsLChild(*x) ? (x)->lChild : (x)->rChild \
	)\
	)\
)


template <typename T> BinNodePosi(T) AVL<T>::insert(const T& e) { 
	BinNodePosi(T) & x = search(e); if (x) return x; //确认目标节点不存在（留意对_hot的设置）
	x = new BinNode<T>(e, _hot); _size++; //创建节点x（此后，其父_hot可能增高，祖父可能失衡）
	for (BinNodePosi(T) g = _hot; g; g = g->parent) { //从x之父出发向上，逐层检查各代祖先g
		if (!AvlBalanced(*g)) { //一旦发现g失衡，则（采用“3 + 4”算法）使之复衡
			 FromParentTo(*g) = rotateAt(tallerChild(tallerChild(g))); //将该子树联至原父亲
			break; //g复衡后，局部子树高度必然复原；其祖先亦必如此，故调整随即结束
		}
		else //否则（ g依然平衡），只需简单地
			updateHeight(g); //更新其高度（注意：即便g未失衡，高度亦可能增加）
	} //至多另需一次调整；若果真做过调整，则全树高度必然复原
	return x; //返回新节点
} //无论e是否存在于原树中，返回时总有x->data == e

template <typename T>
bool AVL<T>::remove(const T& e) {
	BinNodePosi(T)& x = search(e);
	if (!x)
		return false;
	removeAt(x, _hot);
	for (BinNodePosi(T) g = _hot; g; g = g->parent) {
		if(!AvlBalanced(*g))
			g = FromParentTo(*g) = rotateAt(tallerChild(tallerChild(g))); //将该子树联至原父亲
		updateHeight(g);
	}
	return true;
}