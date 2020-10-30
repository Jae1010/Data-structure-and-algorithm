#pragma once
#include"Graph.h"

template <typename Tv>//顶点对象
struct Vertex
{
	Tv data; //数据
	int inDegree, outDegree; //入度、出度
	VStatus status;	//状态
	int dTime, fTime; //时间标签
	int parent; int priority; //在遍历树中的父节点、优先级数
	Vertex(Tv const& d = (Tv)0) : //构造新顶点
		data(d), inDegree(0), outDegree(0), status(UNDISCOVERED),
		dTime(-1), fTime(-1), parent(-1), priority(INT_MAX) {} 
};

template <typename Te> struct Edge {
	Te data; int weight; EStatus status; //数据、权重、状态
	Edge(Te const& d, int w) : data(d), weight(w), status(UNDETERMINED) {} //构造新边
};

template < typename Tv, typename Te> //顶点类型、边类型
class GraphMatrix : public Graph<Tv, Te> {
private:
	Vector<Vertex<Tv>> V;	//顶点集（向量）
	Vector<Vector<Edge<Te>*>> E;	//边集（邻接矩阵）
public:
	GraphMatrix() {
		n = e = 0;
	}
	~GraphMatrix() {
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++)
				delete E[j][k];
	}

// 顶点的基本操作：查询第i个顶点（ 0 <= i < n）
	Tv& vertex(int i) override { return V[i].data; } //读取数据
	int inDegree(int i) override { return V[i].inDegree; } //入度
	int outDegree(int i) override { return V[i].outDegree; } //出度
	int firstNbr(int i) override { return nextNbr(i, n); } //首个邻接顶点
	int nextNbr(int i, int j) override//相对于顶点j的下一邻接顶点
		{ while ((-1 < j) && (!exists(i, --j))); return j; } //逆向线性试探
	VStatus& status(int i) override { return V[i].status; } //状态
	int& dTime(int i) override { return V[i].dTime; } //时间标签dTime
	int& fTime(int i) override { return V[i].fTime; } //时间标签fTime
	int& parent(int i) override { return V[i].parent; } //在遍历树中的父亲
	int& priority(int i) override { return V[i].priority; } //在遍历树中的优先级数

 // 顶点的动态操作
	int insert(Tv const& vertex) override { //插入顶点，返回编号
		for (int j = 0; j < n; j++) 
			E[j].insert(NULL); 
		n++; //各顶点预留一条潜在的关联边
		E.insert(Vector<Edge<Te>*>(n, n, (Edge<Te>*) NULL)); //创建新顶点对应的边向量
		return V.insert(Vertex<Tv>(vertex)); //顶点向量增加一个顶点
	}
	Tv remove(int i) override { //删除第i个顶点及其关联边（ 0 <= i < n）
		for (int j = 0; j < n; j++) //所有出边
			if (exists(i, j)) { delete E[i][j]; V[j].inDegree--; } //逐条删除
		E.remove(i); n--; //删除第i行
		for (int j = 0; j < n; j++) //所有出边
			if (exists(j, i)) { delete E[j].remove(i); V[j].outDegree--; } //逐条删除
		Tv vBak = vertex(i); V.remove(i); //删除顶点i
		return vBak; //返回被删除顶点的信息
	}

// 边的确认操作
	bool exists(int i, int j) override//边(i, j)是否存在
		{ return (0 <= i) && (i < n) && (0 <= j) && (j < n) && E[i][j] != NULL; }

// 边的基本操作：查询顶点i与j之间的联边（ 0 <= i, j < n且exists(i, j)）
	EStatus& status(int i, int j) override{ return E[i][j]->status; } //边(i, j)的状态
	Te& edge(int i, int j) override{ return E[i][j]->data; } //边(i, j)的数据
	int& weight(int i, int j) override{ return E[i][j]->weight; } //边(i, j)的权重

// 边的动态操作
	void insert(Te const& edge, int w, int i, int j) override{ //插入权重为w的边e = (i, j)
		if (exists(i, j)) return; //确保该边尚不存在
		E[i][j] = new Edge<Te>(edge, w); //创建新边
		e++;		//更新边计数
		V[i].outDegree++; 
		V[j].inDegree++; //更新关联顶点的度数
	}
	Te remove(int i, int j) override{ //删除顶点i和j之间的联边（ exists(i, j)）
		Te eBak = edge(i, j);
		delete E[i][j]; 
		E[i][j] = NULL; //备份后删除边记录
		e--;		//更新边计数
		V[i].outDegree--; 
		V[j].inDegree--; //更新关联顶点的度数
		return eBak; //返回被删除边的信息
	}
};


template < typename Tv, typename Te> //广度优先搜索BFS算法（全图）
void Graph<Tv, Te>::bfs(int s) { //assert: 0 <= s < n
	reset();
	int clock = 0;
	int v = s; //初始化
	do //逐一检查所有顶点
		if (UNDISCOVERED == status(v)) //一旦遇到尚未发现的顶点
			BFS(v, clock); //即从该顶点出发启动一次BFS
	while (s != (v = (++v % n))); //按序号检查，故不漏不重
}


template < typename Tv, typename Te> //广度优先搜索BFS算法（单个连通域）
void Graph<Tv, Te> ::BFS(int v, int& clock) {
	Queue<int> Q;	//引入辅助队列
	status(v) = DISCOVERED;
	Q.enqueue(v);	//初始化起点
	while (!Q.empty()) //在Q变空之前，不断
	{
		int v = Q.dequeue();
		dTime(v) = ++clock;		//取出队首顶点v
		for (int u = firstNbr(v); -1 < u; u = nextNbr(v)) {
			if (status(u) == UNDISCOVERED)//若u尚未被发现，则
			{
				status(v) = DISCOVERED;//则发现该顶点
				Q.enqueue(v);
				status(v, u) = TREE;//引入树边拓展支撑树
				parent(u) = v;
			}
			else//若u已被发现，或者甚至已访问完毕，则
			{
				status(v, u) = CROSS; //将(v, u)归类于跨边
			}
		}
		status(v) = VISITED;  //至此，当前顶点访问完毕
	}
}

template <typename Tv, typename Te> //深度优先搜索DFS算法（全图）
void Graph<Tv, Te>::dfs(int s) {
	reset();
	int clock = 0;
	int v = s;//初始化
	do  //逐一检查
	{
		if (UNDISCOVERED == status(v))
			DFS(v, clock);
	} while (s != (v = (++v % n);
}

template<typename Tv, typename Te> //深度优先搜索DFS算法（单个连通域）
void Graph<Tv, Te>::DFS(int v, int& clock) {
	status(v) = DISCOVERED;
	dTime(v) = ++clock;
	for (int u = firstNbr(v); -1 < u; u = nextNbr(v)) {//枚举所有的邻居u
		switch (status(u))//并视其状态分别处理
		{
		case UNDISCOVERED://u尚未发现，意味着支撑树可在此拓展
			status(v, u) = TREE;
			parent(u) = v;
			DFS(u, clock);
			break;
		case DISCOVERED://u已被发现但尚未访问完毕，应属被后代指向的祖先
			status(v, u) = BACKWARD;
			break;
		default://u已访问完毕（ VISITED， 有向图），则视承袭关系分为前向边或跨边
			status(v, u) = dTime(v) < dTime(u) ? FORWARD : CROSS;
			break;
		}
	}
	status(v) = VISITED;
	fTime(v) = ++clock;  //至此，当前顶点v访问完毕
}

template <typename Tv, typename Te> //基于DFS的拓扑排序算法
Stack<Tv>* Graph<Tv, Te>::tSort(int s) {
	reset();
	int clock = 0;
	int v = s;
	Stack<Tv>* S= new Stack<Tv>; //用栈记录排序顶点
	do
	{
		if (UNDISCOVERED == status(v))
			if(!TSort(v, clock, S))  //发现有环，不能做拓扑排序
				while (!S->empty()) 
				{
					S->pop();   //清空栈
				}
		break;		//直接退出
	} while (s != (v = (++v % n)));
}


template <typename Tv, typename Te> //基于DFS的拓扑排序算法（单趟）
bool Graph<Tv, Te>::TSort(int v, int& clock, Stack<Tv>* S) {
	dTime(v) = ++clock;
	status(v) = DISCOVERED;
	for (int u = firstNbr(v); -1 < u; u = nextNbr(v)) {
		switch (status(u))
		{
		case UNDISCOVERED:
			parent(u) = v;
			status(v, u) = TREE;
			if (!TSort(u, clock, S))//从顶点u处出发深入搜索
				return false; //若u及其后代不能拓扑排序（则全图亦必如此），故返回并报告
		case DISCOVERED:
			status(v, u) = BACKWARD;//一旦发现后向边（非DAG），则
			return false;//不必深入，故返回并报告
		default:
			status(v, u) = dTime(v) < dTime(u) ? FORWARD : CROSS;
			break;
		}
	}
	status(v) = VISITED;
	S->push(v);
	return true;
}

