#pragma once
#include "BinNode.h"
#include "../Stack/Stack.h"
#include "../Queue/Queue.h"

template <typename T> class BinTree {
protected:
	int _size;	//�_ģ
	BinNodePosi(T) _root;	//���ڵ�
	virtual int updateHeight(BinNodePosi(T) x); //���½ڵ�x�ĸ߶�
	void updateHeightAbove(BinNodePosi(T) x); //���½ڵ�x�������ȵĸ߶�
public:
	BinTree() :_size(0), _root(NULL) {}
	~BinTree() { if (0 < _size) remove(_root); }
	int size()const { return _size; }
	bool empty()const { return !_root }
	BinNodePosi(T) root() const { return _root; }
	BinNodePosi(T) insertAsRoot(T const& e); //������ڵ�
	BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const& e); //e��Ϊx�����ӣ�ԭ�ޣ�����
	BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const& e); //e��Ϊx���Һ��ӣ�ԭ�ޣ�����
	BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T>* &T); //T��Ϊx����������
	BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T>* &T); //T��Ϊx����������
	int remove(BinNodePosi(T) x); //ɾ����λ��x���ڵ�Ϊ�������������ظ�����ԭ�ȵĹ�ģ
	BinTree<T>* secede(BinNodePosi(T) x); //������x�ӵ�ǰ����ժ�����Խ���ת��Ϊһ�ö�������
	template < typename VST> //������
	void travLevel(VST & visit) { if (_root) _root->travLevel(visit); } //�ִα���
	template < typename VST> //������
	void travPre(VST & visit) { if (_root) _root->travPre(visit); } //�������
	template < typename VST> //������
	void travIn(VST & visit) { if (_root) _root->travIn(visit); } //�������
	template < typename VST> //������
	void travPost(VST & visit) { if (_root) _root->travPost(visit); } //�������
	// �Ƚ������е�����������һ���������в��䣩
	bool operator<(BinTree<T> const& t) { return _root && t._root && lt(_root, t._root); }
	bool operator==(BinTree<T> const& t) { return _root && t._root && (_root == t._root); }


};

template <typename T> 
int BinTree<T>::updateHeight(BinNodePosi(T) x) { //���½ڵ�x�߶�
	return x->hight = 1 + max(stature(x->lChild), stature(x->rChild));
}

template <typename T>
void BinTree<T> ::updateHeightAbove(BinNodePosi(T) x) {//����v�����ȵĸ߶�
	while (x)
	{
		updateHeight(x);  
		x = x->parent;
	}
}

template <typename T>//��e�������ڵ����յĶ�����
BinNodePosi(T) BinTree<T>::insertAsRoot(T const &e) {
	_size = 1;
	return _root = new BinNode<T>(e);
}

template <typename T>//e����Ϊx������
BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x, T const& e) {
	_size++;
	x->insertAsLC(e);
	updateHeightAbove(x);
	return x->lChild;
}

template <typename T>//e����Ϊx���Һ���
BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x, T const& e) {
	_size++;
	x->insertAsRC(e);
	updateHeightAbove(x);
	return x->rChild;
}

template <typename T>//���������������㷨����S�����ڵ�x�����������룬 S�����ÿ�
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

template <typename T>//���������������㷨����S�����ڵ�x�����������룬 S�����ÿ�
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

template < typename T> //ɾ����������λ��x���Ľڵ㼰���������ر�ɾ���ڵ����ֵ
int BinTree<T>::remove(BinNodePosi(T) x) {
	FromParentTo(*x) = nullptr;
	updateHeight(x->parent);
	int n = removeAt(x);
	_size -= n;
	return n;
}

template < typename T> //ɾ����������λ��x���Ľڵ㼰���������ر�ɾ���ڵ����ֵ
static int removeAt(BinNodePosi(T) x) { 
	if (!x) return 0; //�ݹ��������
	int n = 1 + removeAt(x->lChild) + removeAt(x->rChild); //�ݹ��ͷ���������
	release(x->data); release(x); return n; //�ͷű�ժ���ڵ㣬�����س����ڵ�����
}

template < typename T> //���������������㷨��������x�ӵ�ǰ����ժ���������װΪһ�ö�����������
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

template < typename T, typename VST> //Ԫ�����͡�������
void travPre_R(BinNodePosi(T) x, VST& visit) { //��������������㷨���ݹ�棩
	if (!x) return;
	visit(x->data);
	travPre_R(x->lChild, visit);
	travPre_R(x->rChild, visit);
}

template < typename T, typename VST> //Ԫ�����͡�������
void travPost_R(BinNodePosi(T) x, VST & visit) { //��������������㷨���ݹ�棩
	if (!x) return;
	travPost_R(x->lChild, visit);
	travPost_R(x->rChild, visit);
	visit(x->data);
}

template < typename T, typename VST> //Ԫ�����͡�������
void travIn_R(BinNodePosi(T) x, VST & visit) { //��������������㷨���ݹ�棩
	if (!x) return;
	travIn_R(x->lChild, visit);
	visit(x->data);
	travIn_R(x->rChild, visit);
}

template < typename T, typename VST> //Ԫ�����͡�������
static void visitAlongLeftBranch(BinNodePosi(T) x, VST& visit, Stack<BinNodePosi(T)>& S) {
	while (x)
	{
		visit(x->data);
		if(x->rChild)
			S.push(x->rChild);
		x = x->lChild;
	}
}

template < typename T, typename VST> //Ԫ�����͡�������
void travPre_I2(BinNodePosi(T) x, VST & visit) { //��������������㷨��������#2��
	Stack<BinNodePosi(T)> S;
	while (true)
	{
		visitAlongLeftBranch(x, visit, S);
		if (S.empty()) break;
		x = S.pop();
	}
	
}

template < typename T> 
static void goAlongLeftBranch(BinNodePosi(T) x, Stack<BinNodePosi(T)>& S) {
	while (x)
	{
		S.push(x);
		x = x->lChild;
	}
}

template < typename T, typename VST> //Ԫ�����͡�������
void travIn_I1(BinNodePosi(T) x, VST& visit) { //��������������㷨��������#1��
	Stack<BinNodePosi(T)> S;
	while (true)
	{
		goAlongLeftBranch(x, S);
		if (S.empty()) break;
		x = S.pop();
		visit(x->data);
		x = x->rChild;
	}
}

template <typename T> 
BinNodePosi(T) BinNode<T>::succ() { //��λ�ڵ�vde ֱ�Ӻ��
	BinNodePosi(T) s = this;
	if (rChild) {
		s = rChild;
		while (HasLChild(*s))
		{
			s = s->lChild;
		}
	}
	else
	{
		while (IsRChild(*s))
		{
			s = s->parent;
		}
		s = s->parent;
	}
	return s;
}

template < typename T, typename VST> //Ԫ�����͡�������
void travIn_I3(BinNodePosi(T) x, VST& visit) { //��������������㷨��������#3�����踨��ջ��
	bool backtrack = false;
	while (true)
	{
		if (!backtrack && HasLChild(*x))
			x = x->lChild;
		else
		{
			visit(x->data);
			if (HasRChild(*x)) {
				x = x->rChild;
				backtrack = false;
			}
			else
			{
				if (!(x = x->succ())) break;
				backtrack = true;
			}
		}
	}
}

template < typename T> //����Sջ���ڵ�Ϊ���m�����У��҄b������ɼ�Ҷ�ڵ�
static void gotoHLVFL(Stack<BinNodePosi(T)>& S) {
	while (BinNodePosi(T) x = S.top())
	{
		if (HasLChild(*x)) {
			if (HasRChild(*x))
			{
				S.push(x->rChild);
			}			
			S.push(x->lChild);
		}
		else
		{
			S.push(x->rChild);
		}
	}
	S.pop();
}


template < typename T, typename VST>
void travPost_I(BinNodePosi(T) x, VST & visit) { //�������ĺ�������������棩
	Stack<BinNodePosi(T)> S;
	if (x) S.push(x);
	while (!S.empty())
	{
		if (S.top() != x->parent)
			gotoHLVFL(S);
		x = S.pop();
		visit(x->data);
	}
}

//������ȱ����ֳƲ�α���
template <typename T> template < typename VST> //Ԫ�����͡�������
void BinNode<T>::travLevel(VST& visit) {
	Queue<BinNodePosi(T)> Q;
	Q.enqueue(this);
	while (!Q.empty())
	{
		BinNodePosi(T) x = Q.dequeue(); visit(x->data);
		if (HasLChild(*x)) Q.enqueue(x->lChild);
		if (HasRChild(*x)) Q.enqueue(x->rChild);
	}
}


