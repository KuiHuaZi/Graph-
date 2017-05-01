#include "Graph.h"
int degree(Graph& G, int v)
{
	int degree = 0;
	degree = G.adj(v).degree;
	return degree;
}
int maxDegree(Graph &G)
{
	int max = 0;
	for (int v = 0; v < G.V(); v++)
	{
		if (degree(G, v) > max)max = degree(G, v);

	}
	return max;
}
double avgDegree(Graph &G)
{
	return 2 * G.E() / G.V();
}
int numberOfSelfloops(Graph &G)
{
	int count = 0;
	for(int v = 0; v < G.V(); v++)
	{
		const Vertex &vertex = G.adj(v);
		const Edge *tmp = vertex.adj;
		for (int i = 0; i < vertex.degree; i++)
		{
			if (tmp->_v == v)
				count++;
				tmp = tmp->_next;
		}
	}
	return count / 2;
}
ostream &operator <<(ostream&out, Graph &G)
{
	out << G._v << " vertices, " << G._e << " edges\n";
	for (int v = 0; v < G.V(); v++)
	{
		out << v << ":degree: ";
		const Vertex &vertex = G.adj(v);
		out << vertex.degree;
		const Edge *tmp = vertex.adj;
		for (int i = 0; i < vertex.degree; i++)
		{
			out << tmp->_v << " weight: " << tmp->_weight << "\n";
			tmp = tmp->_next;
		}
		out << "\n";
	}
	return out;
}

Graph::Graph(int v)//构造一个点数目为v，边数目为0的图。
{
	log("[:Graph(int v)]begin!\n");
	_v = v;
	_e = 0;
	_vtables = new Vertex[_v];//先给每个点分配存储其度和指向邻接表的指针的空间。默认degree=0，adj = nullptr；
	log("[:Graph(int v)]end!\n");
}
Graph::Graph(istream &in)//从输入流读取图，输入格式为两个整数（v，e），然后+e组整数，一组整数为三个，分别是源，目的，权重
{
	log("[:Graph(istream &in)]begin!\n");
	int E;
	cin >> _v >>E;
	log("input:_v:%d E:%d\n", _v, E);
	_vtables = new Vertex[_v];
	for (int i = 1; i <= E; i++)
	{
		int v, w,weight;
		cin >> v >> w>>weight;
		log("input:src:%d  dest:%d  weight:%d\n ", v, w, weight);
		addEdge(v, w,weight);
	}
	log("[:Graph(istream &in)]end!\n");
}
void Graph::addEdge(int v, int w,int weight)//到底有没有哨兵节点？没有
{
	log("[addEdge]begin!\n");
	if (v >= _v || w >=_v)
	{
		log("[addEdge]input out of range\n");
		return;
	}
	Edge *oldhead = _vtables[v].adj;//每次都从头插入链点，将邻接表的指针指向当前要插入的边，然后将当前要插入的边指向原来的链表头
	_vtables[v].adj = new Edge(w, weight, oldhead);//edge构造函数会将执行“当前要插入的边指向原来的链表头”这个操作
	if (_vtables[v].adj == nullptr)
	{
		log("[addEdge]not have enough memory\n");
	}
	_vtables[v].degree++;
	log("[addEdge]:add success:Edge:%d -- %d  weight: %d\n", v, w, weight);
	oldhead = _vtables[w].adj;
	_vtables[w].adj = new Edge(v, weight, oldhead);
	if (_vtables[w].adj == nullptr)
	{
		log("[addEdge]not have enough memory\n");
	}
	_vtables[w].degree++;
	log("[addEdge]:add success:Edge:%d -- %d  weight: %d\n", w, v, weight);
	_e++;
	log("[addEdge]end!\n");
}
const Vertex& Graph::adj(int v)//返回表示顶点v的结构体的引用，结构体中adj指针指向邻接表的第一条边，若指向null表示没有边
{
	if (v >= _v)
	{
		log("[adj]input out of range\n");
		static Vertex t;
		return t;
	}
	return _vtables[v];
}
void Graph::removeVertex(int v)
{
	if (v >= _v)
	{
		log("[removeVertex]input out of range\n");
		return;
	}
	log("[removeVertex]removeVertex:%d\n", v);
	_vtables[v].degree = 0;
	 
	while (_vtables[v].adj !=nullptr)
	{
		log("[removeVertex]adj:%d\n", _vtables[v].adj);
		removeEdge(v, _vtables[v].adj->_v);//移边操作自然会将adj中的边删除，所以不需要adj = ajd-》next；
	}
}
void Graph::removeEdge(int v, int w)
{
	if (v >= _v || w >= _v)
	{
		log("[removeEdge]input out of range\n");
		return;
	}
	log("[removeEdge]v:%d  w:%d  \n",v,w);
	removeEdgeFromVtables(v, w);
	removeEdgeFromVtables(w, v);
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
void Graph::removeEdgeFromVtables(int vtables, int dest)
{
	Edge *tmp = _vtables[vtables].adj;
	Edge *preTmp = nullptr;
	while (tmp != nullptr&&tmp->_v != dest)
	{
		preTmp = tmp;
		tmp = tmp->_next;
	}
	if (tmp != nullptr)
	{
		if (preTmp == nullptr)
		{
			_vtables[vtables].adj = tmp->_next;
			delete tmp;
			tmp = nullptr;
			log("[removeEdgeFromVtables]remove success: %d -- %d \n", vtables, dest);
		}
		else
		{
			preTmp->_next = tmp->_next;
			delete tmp;
			tmp = nullptr;
			log("[removeEdgeFromVtables]remove success: %d -- %d \n", vtables, dest);
		}

	}
	else
	{
		log("[removeEdgeFromVtables]The Edge:%d -- %d do not exit\n", vtables, dest);
		return;
	}
}
Graph::~Graph()
{
	log("[~Graph]begin\n");
	for (int i = 0; i < _v; i++)
	{
		
		removeVertex(i);
	}
	delete[] _vtables;

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
	while (true)
	{
		GraphMain();
	}
}
