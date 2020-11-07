#pragma once
#include "../BST.h"

#define Balanced(x) (stature((x).lChild) == stature((x).rChild))  //����ƽ������
#define BalFac(x) (stature((x).lChild) - stature((x).rChild))//ƽ������
#define AvlBalanced(x) ((-2 < BalFac(x)) && (BalFac(x) < 2))//AVLƽ������

template <typename T> class AVL :public BST<T> {
public:
	BinNodePosi(T) insert(const T& e); //���루��д��
	bool remove(const T& e); //ɾ������д��
	// BST::search()������ӿڿ�ֱ������
};

/******************************************************************************************
 * �����Һ�����ȡ�����ߣ����ȸߣ����븸��pͬ��������
 * ��AVLƽ�����ǰ�����ȷ���ع�����
 ******************************************************************************************/
#define tallerChild(x) (\
	stature((x)->lChild) > stature((x)->rChild) ? (x)->lChild : (\
	stature((x)->rChild) > stature((x)->lChild) ? (x)->rChild : (\
	IsLChild(*x) ? (x)->lChild : (x)->rChild \
	)\
	)\
)


template <typename T> BinNodePosi(T) AVL<T>::insert(const T& e) { 
	BinNodePosi(T) & x = search(e); if (x) return x; //ȷ��Ŀ��ڵ㲻���ڣ������_hot�����ã�
	x = new BinNode<T>(e, _hot); _size++; //�����ڵ�x���˺��丸_hot�������ߣ��游����ʧ�⣩
	for (BinNodePosi(T) g = _hot; g; g = g->parent) { //��x֮���������ϣ�������������g
		if (!AvlBalanced(*g)) { //һ������gʧ�⣬�򣨲��á�3 + 4���㷨��ʹ֮����
			 FromParentTo(*g) = rotateAt(tallerChild(tallerChild(g))); //������������ԭ����
			break; //g����󣬾ֲ������߶ȱ�Ȼ��ԭ�������������ˣ��ʵ����漴����
		}
		else //���� g��Ȼƽ�⣩��ֻ��򵥵�
			updateHeight(g); //������߶ȣ�ע�⣺����gδʧ�⣬�߶���������ӣ�
	} //��������һ�ε�����������������������ȫ���߶ȱ�Ȼ��ԭ
	return x; //�����½ڵ�
} //����e�Ƿ������ԭ���У�����ʱ����x->data == e

template <typename T>
bool AVL<T>::remove(const T& e) {
	BinNodePosi(T)& x = search(e);
	if (!x)
		return false;
	removeAt(x, _hot);
	for (BinNodePosi(T) g = _hot; g; g = g->parent) {
		if(!AvlBalanced(*g))
			g = FromParentTo(*g) = rotateAt(tallerChild(tallerChild(g))); //������������ԭ����
		updateHeight(g);
	}
	return true;
}