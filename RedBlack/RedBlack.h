#pragma once
#include "../BST/BST.h"
template <typename T>
class RedBlack :public BST<T> {
protected:
	void solveDoubleRed(BinNodePosi(T) x); //˫������
	void solveDoubleBlack(BinNodePosi(T) x); //˫������
	int updateHeight(BinNodePosi(T) x); //���½ڵ�x�ĸ߶�
public:
	BinNodePosi(T) insert(const T & e); //���루��д��
	bool remove(const T & e); //ɾ������д��
	// BST::search()������ӿڿ�ֱ������
};