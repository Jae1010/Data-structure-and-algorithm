#pragma once
#include"Graph.h"

template <typename Tv>//�������
struct Vertex
{
	Tv data; //����
	int inDegree, outDegree; //��ȡ�����
	VStatus status;	//״̬
	int dTime, fTime; //ʱ���ǩ
	int parent; int priority; //�ڱ������еĸ��ڵ㡢���ȼ���
	Vertex(Tv const& d = (Tv)0) : //�����¶���
		data(d), inDegree(0), outDegree(0), status(UNDISCOVERED),
		dTime(-1), fTime(-1), parent(-1), priority(INT_MAX) {} 
};

template <typename Te> struct Edge {
	Te data; int weight; EStatus status; //���ݡ�Ȩ�ء�״̬
	Edge(Te const& d, int w) : data(d), weight(w), status(UNDETERMINED) {} //�����±�
};

template < typename Tv, typename Te> //�������͡�������
class GraphMatrix : public Graph<Tv, Te> {
private:
	Vector<Vertex<Tv>> V;	//���㼯��������
	Vector<Vector<Edge<Te>*>> E;	//�߼����ڽӾ���
public:
	GraphMatrix() {
		n = e = 0;
	}
	~GraphMatrix() {
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++)
				delete E[j][k];
	}

// ����Ļ�����������ѯ��i�����㣨 0 <= i < n��
	Tv& vertex(int i) override { return V[i].data; } //��ȡ����
	int inDegree(int i) override { return V[i].inDegree; } //���
	int outDegree(int i) override { return V[i].outDegree; } //����
	int firstNbr(int i) override { return nextNbr(i, n); } //�׸��ڽӶ���
	int nextNbr(int i, int j) override//����ڶ���j����һ�ڽӶ���
		{ while ((-1 < j) && (!exists(i, --j))); return j; } //����������̽
	VStatus& status(int i) override { return V[i].status; } //״̬
	int& dTime(int i) override { return V[i].dTime; } //ʱ���ǩdTime
	int& fTime(int i) override { return V[i].fTime; } //ʱ���ǩfTime
	int& parent(int i) override { return V[i].parent; } //�ڱ������еĸ���
	int& priority(int i) override { return V[i].priority; } //�ڱ������е����ȼ���

 // ����Ķ�̬����
	int insert(Tv const& vertex) override { //���붥�㣬���ر��
		for (int j = 0; j < n; j++) 
			E[j].insert(NULL); 
		n++; //������Ԥ��һ��Ǳ�ڵĹ�����
		E.insert(Vector<Edge<Te>*>(n, n, (Edge<Te>*) NULL)); //�����¶����Ӧ�ı�����
		return V.insert(Vertex<Tv>(vertex)); //������������һ������
	}
	Tv remove(int i) override { //ɾ����i�����㼰������ߣ� 0 <= i < n��
		for (int j = 0; j < n; j++) //���г���
			if (exists(i, j)) { delete E[i][j]; V[j].inDegree--; } //����ɾ��
		E.remove(i); n--; //ɾ����i��
		for (int j = 0; j < n; j++) //���г���
			if (exists(j, i)) { delete E[j].remove(i); V[j].outDegree--; } //����ɾ��
		Tv vBak = vertex(i); V.remove(i); //ɾ������i
		return vBak; //���ر�ɾ���������Ϣ
	}

// �ߵ�ȷ�ϲ���
	bool exists(int i, int j) override//��(i, j)�Ƿ����
		{ return (0 <= i) && (i < n) && (0 <= j) && (j < n) && E[i][j] != NULL; }

// �ߵĻ�����������ѯ����i��j֮������ߣ� 0 <= i, j < n��exists(i, j)��
	EStatus& status(int i, int j) override{ return E[i][j]->status; } //��(i, j)��״̬
	Te& edge(int i, int j) override{ return E[i][j]->data; } //��(i, j)������
	int& weight(int i, int j) override{ return E[i][j]->weight; } //��(i, j)��Ȩ��

// �ߵĶ�̬����
	void insert(Te const& edge, int w, int i, int j) override{ //����Ȩ��Ϊw�ı�e = (i, j)
		if (exists(i, j)) return; //ȷ���ñ��в�����
		E[i][j] = new Edge<Te>(edge, w); //�����±�
		e++;		//���±߼���
		V[i].outDegree++; 
		V[j].inDegree++; //���¹�������Ķ���
	}
	Te remove(int i, int j) override{ //ɾ������i��j֮������ߣ� exists(i, j)��
		Te eBak = edge(i, j);
		delete E[i][j]; 
		E[i][j] = NULL; //���ݺ�ɾ���߼�¼
		e--;		//���±߼���
		V[i].outDegree--; 
		V[j].inDegree--; //���¹�������Ķ���
		return eBak; //���ر�ɾ���ߵ���Ϣ
	}
};


template < typename Tv, typename Te> //�����������BFS�㷨��ȫͼ��
void Graph<Tv, Te>::bfs(int s) { //assert: 0 <= s < n
	reset();
	int clock = 0;
	int v = s; //��ʼ��
	do //��һ������ж���
		if (UNDISCOVERED == status(v)) //һ��������δ���ֵĶ���
			BFS(v, clock); //���Ӹö����������һ��BFS
	while (s != (v = (++v % n))); //����ż�飬�ʲ�©����
}


template < typename Tv, typename Te> //�����������BFS�㷨��������ͨ��
void Graph<Tv, Te> ::BFS(int v, int& clock) {
	Queue<int> Q;	//���븨������
	status(v) = DISCOVERED;
	Q.enqueue(v);	//��ʼ�����
	while (!Q.empty()) //��Q���֮ǰ������
	{
		int v = Q.dequeue();
		dTime(v) = ++clock;		//ȡ�����׶���v
		for (int u = firstNbr(v); -1 < u; u = nextNbr(v)) {
			if (status(u) == UNDISCOVERED)//��u��δ�����֣���
			{
				status(v) = DISCOVERED;//���ָö���
				Q.enqueue(v);
				status(v, u) = TREE;//����������չ֧����
				parent(u) = v;
			}
			else//��u�ѱ����֣����������ѷ�����ϣ���
			{
				status(v, u) = CROSS; //��(v, u)�����ڿ��
			}
		}
		status(v) = VISITED;  //���ˣ���ǰ����������
	}
}

template <typename Tv, typename Te> //�����������DFS�㷨��ȫͼ��
void Graph<Tv, Te>::dfs(int s) {
	reset();
	int clock = 0;
	int v = s;//��ʼ��
	do  //��һ���
	{
		if (UNDISCOVERED == status(v))
			DFS(v, clock);
	} while (s != (v = (++v % n);
}

template<typename Tv, typename Te> //�����������DFS�㷨��������ͨ��
void Graph<Tv, Te>::DFS(int v, int& clock) {
	status(v) = DISCOVERED;
	dTime(v) = ++clock;
	for (int u = firstNbr(v); -1 < u; u = nextNbr(v)) {//ö�����е��ھ�u
		switch (status(u))//������״̬�ֱ���
		{
		case UNDISCOVERED://u��δ���֣���ζ��֧�������ڴ���չ
			status(v, u) = TREE;
			parent(u) = v;
			DFS(u, clock);
			break;
		case DISCOVERED://u�ѱ����ֵ���δ������ϣ�Ӧ�������ָ�������
			status(v, u) = BACKWARD;
			break;
		default://u�ѷ�����ϣ� VISITED�� ����ͼ�������ӳ�Ϯ��ϵ��Ϊǰ��߻���
			status(v, u) = dTime(v) < dTime(u) ? FORWARD : CROSS;
			break;
		}
	}
	status(v) = VISITED;
	fTime(v) = ++clock;  //���ˣ���ǰ����v�������
}

template <typename Tv, typename Te> //����DFS�����������㷨
Stack<Tv>* Graph<Tv, Te>::tSort(int s) {
	reset();
	int clock = 0;
	int v = s;
	Stack<Tv>* S= new Stack<Tv>; //��ջ��¼���򶥵�
	do
	{
		if (UNDISCOVERED == status(v))
			if(!TSort(v, clock, S))  //�����л�����������������
				while (!S->empty()) 
				{
					S->pop();   //���ջ
				}
		break;		//ֱ���˳�
	} while (s != (v = (++v % n)));
}


template <typename Tv, typename Te> //����DFS�����������㷨�����ˣ�
bool Graph<Tv, Te>::TSort(int v, int& clock, Stack<Tv>* S) {
	dTime(v) = ++clock;
	status(v) = DISCOVERED;
	for (int u = firstNbr(v); -1 < u; u = nextNbr(v)) {
		switch (status(u))
		{
		case UNDISCOVERED:
			parent(u) = v;
			status(v, u) = TREE;
			if (!TSort(u, clock, S))//�Ӷ���u��������������
				return false; //��u��������������������ȫͼ�����ˣ����ʷ��ز�����
		case DISCOVERED:
			status(v, u) = BACKWARD;//һ�����ֺ���ߣ���DAG������
			return false;//�������룬�ʷ��ز�����
		default:
			status(v, u) = dTime(v) < dTime(u) ? FORWARD : CROSS;
			break;
		}
	}
	status(v) = VISITED;
	S->push(v);
	return true;
}

