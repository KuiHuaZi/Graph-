#include "Graph.h"
#include"search.h"
//int degree(Graph& G, int v)
//{
//	int degree = 0;
//	degree = G.adj(v).degree;
//	return degree;
//}
//int maxDegree(Graph &G)
//{
//	int max = 0;
//	for (int v = 0; v < G.V(); v++)
//	{
//		if (degree(G, v) > max)max = degree(G, v);
//
//	}
//	return max;
//}
//double avgDegree(Graph &G)
//{
//	return 2 * G.E() / G.V();
//}
//int numberOfSelfloops()
//{
//	int count = 0;
//	for(int v = 0; v < G.V(); v++)
//	{
//		const Vertex &vertex = G.adj(v);
//		const Edge *tmp = vertex.
//		for (int i = 0; i < vertex.degree; i++)
//		{
//			if (tmp->_v == v)
//				count++;
//				tmp = tmp->_next;
//		}
//	}
//	return count / 2;
//}
Vertex::Vertex(int v)
{
	log("Vertex():begin!\n");
	_v = v;
	_degree = 0;
	_adj = nullptr;
	log("Vertex():end!\n");
}
void Vertex::addEdge(int src, int dest, int weight)
{
	//if (_v == -1)_v = src;//权宜之计！
	log("Vertex(%d):addEgde( src = %d, dest = %d, weight = %d ):begin！\n", _v, src, dest, weight);
	if (src != _v)
	{
		log("Error:The source of Edge is not this Vertex！\n");
		return;
	}
	Edge *old = _adj;
	_adj = new Edge(_v, dest, weight, old);//从头开始插入边
	_degree++;
	log("Vertex(%d):addEgde( src = %d, dest = %d, weight = %d ):end！\n", _v, src, dest, weight);
}

bool Vertex::removeEdge(int dest)
{
	Edge *current = _adj;
	Edge *pre = nullptr;
	while (current != nullptr&&current->getDest() != dest)
	{
		pre = current;
		current = current->_next;
	}
	if (current != nullptr)
	{
		if (pre == nullptr)//说明要移除邻接表的第一个边,即_adj指向的那条边
		{
			_adj = current->_next;
			log("[Vertex(%d).removeEdge(%d)]:remove frist Edge in _adj success!\n", _v, dest);
		}
		else
		{
			pre->_next = current->_next;

			log("[Vertex(%d).removeEdge(%d)]:remove Edge in _adj success!\n", _v, dest);
		}
		delete current;
		current = nullptr;
		--_degree;
		return true;
	}
	else
	{
		log("[Vertex(%d).removeEdge(%d)]:No this edge in _adj!\n", _v, dest);
		return false;
	}
}

Vertex::~Vertex()
{
	log("[~Vertex(%d)]:begin!\n", _v);
	while (_adj != nullptr)
	{
		removeEdge(_adj->_dest);//每次都把邻接表中的第一条边移除，直到_adj为空
	}
	log("[~Vertex(%d)]:end!\n", _v);
}




ostream &operator <<(ostream&out, const Vertex &V)
{
	out << "Vertex:" << V._v << " ,degree :" << V._degree << endl;
	Edge *tmp = V._adj;
	while (tmp!=nullptr)
	{
		out << *tmp;
		tmp = tmp->getNext();
	}
	return out;
}
ostream &operator<<(ostream&out, const Edge &E)
{
	out<<"<"<<E._src<<" -- "<<E._dest<<" ,weight: "<<E._weight<<" >\n";
	return out;
}
ostream &operator <<(ostream&out, Graph &G)
{
	out << G._v << " vertices, " << G._e << " edges\n";
	for (int v = 0; v < G.V(); v++)
	{
		out << G._vtables[v];
	}
	return out;
}

Graph::Graph(int v)//构造一个点数目为v，边数目为0的图。
{
	log("[Graph(int %d)]begin!\n",v);
	_v = v;
	_e = 0;
	_vtables.resize(_v);//先给每个点分配存储其度和指向邻接表的指针的空间。默认degree=0，adj = nullptr；
	log("[Graph(int %d)]end!\n",v);
}
Graph::Graph(istream &in)//从输入流读取图，输入格式为两个整数（v，e），然后+e组整数，一组整数为三个，分别是源，目的，权重
{
	log("[Graph(istream &in)]begin!\n");
	int E;
	cin >> _v >>E;
	log("input:_v:%d E:%d\n", _v, E);
	_vtables.resize(_v);
	for (int i = 1; i <= E; i++)
	{
		int v, w,weight;
		cin >> v >> w>>weight;
		log("input:src:%d  dest:%d  weight:%d\n ", v, w, weight);
		_vtables[v]._v = v;
		_vtables[w]._v = w;
		addEdge(v, w,weight);
	}
	cin >> _numMustNode;
	log("input:_numMustNode: %d : ", _numMustNode);
	_mustNode.resize(_numMustNode);
	for (int i = 0; i <_numMustNode; i++)
	{
		int v;
		cin >> v;
		log("  %d\n", v);
		_mustNode[i] = v;
	}

	cin >> _numMustEdge;
	log("input:_numMustEdge: %d :", _numMustEdge);
	for (int i = 0; i < _numMustEdge; i++)
	{
		int u, v,weight;
		cin >> u >> v>>weight;
		log("mustEdge:%d--%d weight:%d \n", u, v,weight);
		//_weightHaveToAdd += weight;
		removeEdge(u, v);//在必须经过的边的中间添加一个节点：删除必经的边，然后添加一个节点，用这个节点将原必经的边的两个端点连上
		_vtables.insert(_vtables.end(), Vertex(_v + 1));
		addEdge(_v + i, u, weight);
		addEdge(_v + i, v, 0);
		//将新加的点和必经边的两个端点都添加进_mustNode中。
		_mustNode.push_back(_v + i);
		vector<int>::iterator it;
		it = find(_mustNode.begin(), _mustNode.end(), u);//
		if (it != _mustNode.end())_mustNode.push_back(u);
		it = find(_mustNode.begin(), _mustNode.end(), v);
		if (it != _mustNode.end())_mustNode.push_back(v);
	}
	log("\n");
	cin >> _noEdgeNum;
	log("input:_noEdgeNum:%d", _noEdgeNum);
	for (int i = 0; i < _noEdgeNum; i++)
	{
		int u, v;
		cin >> u >> v;
		log("noEdge:%d--%d  ", u, v);
		removeEdge(u, v);
	}
	log("\n");
	cin >> _source >> _end;
	log("input:_source:%d  ,_end:%d  \n", _source, _end);
	cin >> _Maxnumpoints;
	log("input:_Maxnumpoints:%d\n", _Maxnumpoints);
	log("[Graph(istream &in)]end!\n");
}
void Graph::addEdge(int v, int w,int weight)
{
	log("[addEdge( v:%d  w:%d  weight:%d )]begin!\n",v,w,weight);
	if (v >= _v || w >=_v)
	{
		log("[addEdge]input out of range\n");
		return;
	}
	if(v == w)_vtables[v].addEdge(v, w, weight);
	else
	{
		_vtables[v].addEdge(v, w, weight);
		_vtables[w].addEdge(w, v, weight);
	}
	//Edge *oldhead = _vtables[v].adj;//每次都从头插入链点，将邻接表的指针指向当前要插入的边，然后将当前要插入的边指向原来的链表头
	//_vtables[v].adj = new Edge(w, weight, oldhead);//edge构造函数会将执行“当前要插入的边指向原来的链表头”这个操作
	//if (_vtables[v].adj == nullptr)
	//{
	//	log("[addEdge]not have enough memory\n");
	//}
	//_vtables[v].degree++;
	//log("[addEdge]:add success:Edge:%d -- %d  weight: %d\n", v, w, weight);
	//oldhead = _vtables[w].adj;
	//_vtables[w].adj = new Edge(v, weight, oldhead);
	//if (_vtables[w].adj == nullptr)
	//{
	//	log("[addEdge]not have enough memory\n");
	//}
	//_vtables[w].degree++;
	//log("[addEdge]:add success:Edge:%d -- %d  weight: %d\n", w, v, weight);
	//_e++;
	log("[addEdge( v:%d  w:%d  weight:%d )]end!\n", v, w, weight);
}
const Vertex& Graph::adj(int v)const//返回表示顶点v的结构体的引用，结构体中adj指针指向邻接表的第一条边，若指向null表示没有边
{
	if (v >= _v)
	{
		log("[adj]input out of range\n");
		static Vertex t;
		return t;
	}
	return _vtables[v];
}
void Graph::removeVertex(int v)//先不考虑
{
	//if (v >= _v)
	//{
	//	log("[removeVertex]input out of range\n");
	//	return;
	//}
	//log("[removeVertex]removeVertex:%d\n", v);
	//_vtables[v].degree = 0;
	// 
	//while (_vtables[v].adj !=nullptr)
	//{
	//	log("[removeVertex]adj:%d\n", _vtables[v].adj);
	//	removeEdge(v, _vtables[v].adj->_v);//移边操作自然会将adj中的边删除，所以不需要adj = ajd-》next；
	//}
}
void Graph::removeEdge(int v, int w)
{
	if (v >= _v || w >= _v)
	{
		log("[removeEdge]input out of range\n");
		return;
	}
	log("[removeEdge(v:%d  w:%d)]begin!\n",v,w);
	_vtables[v].removeEdge(w);
	_vtables[w].removeEdge(v);
	//Edge *tmp = _vtables[v].adj;
	//Edge *preTmp = _vtables[v].adj;
	//while (tmp != nullptr&&tmp->_v!=w)
	//{
	//	preTmp = tmp;
	//	tmp = tmp->_next;
	//}
	//if (tmp != nullptr)
	//{
	//	preTmp->_next = tmp->_next;
	//	delete tmp;
	//	tmp = nullptr;
	//}
	//else
	//{
	//	log("The Edge:%d -- %d do not exit\n", v, w);
	//	return;
	//}

	//tmp = _vtables[w].adj;
	//preTmp = _vtables[w].adj;
	//while (tmp != nullptr&&tmp->_v != v)
	//{
	//	preTmp = tmp;
	//	tmp = tmp->_next;
	//}
	//if (tmp != nullptr)
	//{
	//	preTmp->_next = tmp->_next;
	//	delete tmp;
	//	tmp = nullptr;
	//}
	//else
	//{
	//	log("The Edge:%d -- %d do not exit\n", w, v);
	//	return;
	//}

}
Graph::~Graph()
{
	log("[~Graph]begin\n");
	for (int i = 0; i < _v; i++)
	{
		
		removeVertex(i);
	}

	log("[~Graph]end\n");
}

int log(const char* format, ...)
{

	va_list vp;
	va_start(vp, format);
	int result = vprintf(format, vp);
	va_end(vp);
	return result;

}
void GraphMain()
{
	Graph t(cin);
	cout << t;
}
int main()
{
	Graph g(cin);//根据输入来构造图，同时记录下其必须要经过的点，记录下起止节点，删除不能经过的边，在必须经过的边的中间添加一个节点，同时将必经边的端点和
	//这个添加的点都加进必经的点。

	//其和两边顶点的权重为0（在最后得出结果的时候将权重加上,同时节点的限制要放宽，一个边放宽一个）
	//对所有必须经过的节点（包括起止节点），求出其与所有点之间的最短路（包括点数最少的路和权重最少的路）（使用广度优先遍历，同时记录其消耗）
	vector<BFS> leastNumPointsCostPath;
	for (int i = 0; i < g._mustNode.size(); i++)
	{
		leastNumPointsCostPath.push_back(BFS(g, g._mustNode[i]));//将必经节点到所有节点的点数最短路算出来
	}
	BFS sourceTo(g, g._source);// endTo(g, g._end);//将起止节点到所有节点的点数最短路算出来
	vector< vector<int> > paths;//用来存储不同排列的路径
	vector<int> pathsCostPoints;//用来存储对应路径的cost
	vector<int> pathsCostWeight;//用来存储对应路径的权重
	int maxPointNum = g._Maxnumpoints; //+ g._numMustEdge;不需要是因为在算点开销的时候，不会计算这个点，所以不需要放宽限制//因为在每一条必经的边都添加了一个不存在的点，所以节点限制要放宽
	sort(g._mustNode.begin(), g._mustNode.end());
	int pathId = 0, bestCost = 100000;
	do 
	{
		int costPoints = 0, costWeight = 0;
		
		costPoints += sourceTo.costTo(g._mustNode[0]);
		costWeight += sourceTo.weightTo(g._mustNode[0]);
		vector<int>path(*sourceTo.pathTo(g._mustNode[0]));
		for (int i = 0; i < g._mustNode.size()-1; i++)
		{
			for (int j = 0; j < leastNumPointsCostPath.size(); j++)//找到点_mustNode[i]的bfs的结果，然后把_mustNode[i]到_mustNode[i+1]的路径添加进去
			{
				if (leastNumPointsCostPath[j]._s == g._mustNode[i])
				{
					costPoints += leastNumPointsCostPath[j].costTo(g._mustNode[i+1] );
					costWeight += leastNumPointsCostPath[j].weightTo(g._mustNode[i+1] );
					path.insert(path.end(), (*leastNumPointsCostPath[j].pathTo(g._mustNode[i+1])).begin()+1, (*leastNumPointsCostPath[j].pathTo(g._mustNode[i + 1])).end());//将点i到i+1的路径添加进path里，去除第一个节点，因为会和之前路径结束点重合
					break;
				}
			}
			if (costPoints > maxPointNum)//此时节点数目超过限制。
			{
				costPoints = -1;
				costWeight = -1;
				//path = { -1 };
				break;
			}
			
		}
		//添加最后一个_mustNode到end顶点的路径和花销
		if (costPoints != -1)//说明此路无意义，直接计算下一个排列
		{

			continue;
		}
		//else if((costPoints+=leastNumPointsCostPath[leastNumPointsCostPath.size()-1].costTo(g._end))>maxPointNum)//如果加上排列里最后一个点到终点的开销超过了限制
		//{
		//	continue;
		//}
		else
		{
			for (int j = 0; j < leastNumPointsCostPath.size(); j++)//找到点_mustNode[i]的bfs的结果，然后把_mustNode[i]到_mustNode[i+1]的路径添加进去
			{
				if (leastNumPointsCostPath[j]._s == g._mustNode[g._mustNode.size()-1])//找最后一个节点
				{
					costPoints += leastNumPointsCostPath[j].costTo(g._end);
					if (costPoints > maxPointNum)
					{
						break;//大于节点限制，直接跳出去，不把路径添加。
					}
					pathsCostPoints.push_back(costPoints);
					costWeight += leastNumPointsCostPath[j].weightTo(g._end);
					pathsCostWeight.push_back(costWeight);
					path.insert(path.end(), (*leastNumPointsCostPath[j].pathTo(g._end)).begin() + 1, (*leastNumPointsCostPath[j].pathTo(g._end)).end());//将_mustNode里的最后一个节点到_end节点的路径添加进去
					paths.push_back(path);
					break;
				}
			}

		}
		
		


	} while (next_permutation(g._mustNode.begin(),g._mustNode.end()));
	//对所有必进节点进行全排列，按照顺序，找出其中满足节点数目小于要求的路
	for (int i = 0; i < paths.size(); i++)
	{
		log("paths:\n costPoints:%d \n costWeight:%d \n", pathsCostPoints[i], pathsCostWeight[i]);
		for (int j = 0; j < paths[i].size(); j++)
		{
			cout << paths[i][j] << "---";
		}
		cout << endl;
	}

	//求出其权重。对于每个解都用边/路替换去求出满足条件的最优解，然后返回出最优解。
}
