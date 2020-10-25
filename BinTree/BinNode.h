#pragma once
#define BinNodePosi(T) BinNode<T>* //�ڵ�λ��
#define stature(p) ((p) ? (p)->height : -1) //�ڵ�߶ȣ��롰�����߶�Ϊ-1����Լ����ͳһ��
typedef enum { RB_RED, RB_BLACK } RBColor; //�ڵ���ɫ


//�������ڵ�ģ����
template <typename T> struct BinNode {
	T data; //��ֵ
	BinNodePosi(T) parent;  //���ڵ�
	BinNodePosi(T) lChild;  //����
	BinNodePosi(T) rChild;	//�Һ���
	int hight;	//�߶�
	int npl;	//Null Path Length����ʽ�ѣ�Ҳ��ֱ����height���棩
	RBColor color;
	//���캯��
	BinNode() : parent(NULL), lChild(NULL), rChild(NULL), height(0), npl(1), color(RB_RED) { }
	BinNode(T e, BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL, BinNodePosi(T) rc = NULL,
		int h = 0, int l = 1, RBColor c = RB_RED)
		: data(e), parent(p), lChild(lc), rChild(rc), height(h), npl(l), color(c) { }

	//�����ӿ�
	int size();
	BinNodePosi(T) insertAsLC(T const&); //��Ϊ��ǰ�ڵ�����Ӳ����½ڵ�
	BinNodePosi(T) insertAsRC(T const&); //��Ϊ��ǰ�ڵ���Һ��Ӳ����½ڵ�
	BinNodePosi(T) succ(); //ȡ��ǰ�ڵ��ֱ�Ӻ��
	template <typename VST> void travLevel(VST&); //������α���
	template <typename VST> void travPre(VST&); //�����������
	template <typename VST> void travIn(VST&); //�����������
	template <typename VST> void travPost(VST&); //�����������
	//�Ƚ����е���
	bool operator<(BinNode const& bn) { return data < bn.data; }
	bool operator==(BinNode const& bn) { return data == bn.data; }

};
template <typename T>
BinNodePosi(T) BinNode<T>::insertAsLC(T const&)//��Ϊ��ǰ�ڵ�����Ӳ����½ڵ�
{
	return lChild = new BinNode(e, this);
}
template <typename T>
BinNodePosi(T) BinNode<T>::insertAsRC(T const&)//��Ϊ��ǰ�ڵ���Һ��Ӳ����½ڵ�
{
	return IsRChild = new BinNode(e, this);
}

template <typename T> template < typename VST> //Ԫ�����͡�������
void BinNode<T>::travIn(VST & visit) { //��������������㷨ͳһ���
	switch (rand() % 5) { //�˴������ѡ���������ԣ�������ѡ��
		case 1: travIn_I1(this, visit); break; //������#1
		case 2: travIn_I2(this, visit); break; //������#2
		case 3: travIn_I3(this, visit); break; //������#3
		case 4: travIn_I4(this, visit); break; //������#4  travIn_I4����ϰ��[5-17]
		default: travIn_R(this, visit); break; //�ݹ��
	}
}



/******************************************************************************************
 * BinNode״̬�����ʵ��ж�
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
  * ��BinNode�����ض���ϵ�Ľڵ㼰ָ��
  ******************************************************************************************/
#define sibling(p) (\
	IsLChild(*(p))?\
		(p)->parent->rChild : \
		(p)->parent->lChild \
)  //�ֵ�

#define uncle(x) ( \
	IsLChild(*((x)->parent)) ? \
		(x)->parent->parent->rChild : \
		(x)->parent->parent->lChild \
)  //����

#define FromParentTo(x) ( \
 IsRoot(x) ? _root : ( \
 IsLChild(x) ? (x).parent->lChild : (x).parent->rChild \
 )\
) //���Ը��׵�ָ��