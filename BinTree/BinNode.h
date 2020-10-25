#pragma once
#define BinNodePosi(T) BinNode<T>* //节点位置
#define stature(p) ((p) ? (p)->height : -1) //节点高度（与“空树高度为-1”的约定相统一）
typedef enum { RB_RED, RB_BLACK } RBColor; //节点颜色


//二叉树节点模板类
template <typename T> struct BinNode {
	T data; //数值
	BinNodePosi(T) parent;  //父节点
	BinNodePosi(T) lChild;  //左孩子
	BinNodePosi(T) rChild;	//右孩子
	int hight;	//高度
	int npl;	//Null Path Length（左式堆，也可直接用height代替）
	RBColor color;
	//构造函数
	BinNode() : parent(NULL), lChild(NULL), rChild(NULL), height(0), npl(1), color(RB_RED) { }
	BinNode(T e, BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL, BinNodePosi(T) rc = NULL,
		int h = 0, int l = 1, RBColor c = RB_RED)
		: data(e), parent(p), lChild(lc), rChild(rc), height(h), npl(l), color(c) { }

	//操作接口
	int size();
	BinNodePosi(T) insertAsLC(T const&); //作为当前节点的左孩子插入新节点
	BinNodePosi(T) insertAsRC(T const&); //作为当前节点的右孩子插入新节点
	BinNodePosi(T) succ(); //取当前节点的直接后继
	template <typename VST> void travLevel(VST&); //子树层次遍历
	template <typename VST> void travPre(VST&); //子树先序遍历
	template <typename VST> void travIn(VST&); //子树中序遍历
	template <typename VST> void travPost(VST&); //子树后序遍历
	//比较器判等器
	bool operator<(BinNode const& bn) { return data < bn.data; }
	bool operator==(BinNode const& bn) { return data == bn.data; }

};
template <typename T>
BinNodePosi(T) BinNode<T>::insertAsLC(T const&)//作为当前节点的左孩子插入新节点
{
	return lChild = new BinNode(e, this);
}
template <typename T>
BinNodePosi(T) BinNode<T>::insertAsRC(T const&)//作为当前节点的右孩子插入新节点
{
	return IsRChild = new BinNode(e, this);
}

template <typename T> template < typename VST> //元素类型、操作器
void BinNode<T>::travIn(VST & visit) { //二叉树中序遍历算法统一入口
	switch (rand() % 5) { //此处暂随机选择以做测试，共五种选择
		case 1: travIn_I1(this, visit); break; //迭代版#1
		case 2: travIn_I2(this, visit); break; //迭代版#2
		case 3: travIn_I3(this, visit); break; //迭代版#3
		case 4: travIn_I4(this, visit); break; //迭代版#4  travIn_I4留作习题[5-17]
		default: travIn_R(this, visit); break; //递归版
	}
}



/******************************************************************************************
 * BinNode状态与性质的判断
 ******************************************************************************************/
#define IsRoot(x) (!((x).parent))
#define IsLChild(x) (!IsRoot(x)&&(&(x) == (x).parent->lChild))
#define IsRChild(x) (!IsRoot(x) && (&(x) == (x).parent->rChild))
#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ((x).lChild)
#define HasRChild(x) ((x).rChild)
#define HasChild(x) (HasLChild(x) || HasRChild(x))
#define HasBothChild(x) (HasLChild(x) && HasRChild(x)) 
#define IsLeaf(x) (!HasChild(x))

 /******************************************************************************************
  * 与BinNode具有特定关系的节点及指针
  ******************************************************************************************/
#define sibling(p) (\
	IsLChild(*(p))?\
		(p)->parent->rChild : \
		(p)->parent->lChild \
)  //兄弟

#define uncle(x) ( \
	IsLChild(*((x)->parent)) ? \
		(x)->parent->parent->rChild : \
		(x)->parent->parent->lChild \
)  //叔叔

#define FromParentTo(x) ( \
 IsRoot(x) ? _root : ( \
 IsLChild(x) ? (x).parent->lChild : (x).parent->rChild \
 )\
) //来自父亲的指针