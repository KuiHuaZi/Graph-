#include "Graph.h"
int degree(Graph G, int v)
{
	int degree = 0;
	degree = G.adj(v).degree;
	return degree;
}
int maxDegree(Graph G)
{
	int max = 0;
	for (int v = 0; v < G.V(); v++)
	{
		if (degree(G, v) > max)max = degree(G, v);

	}
	return max;
}
double avgDegree(Graph G)
{
	return 2 * G.E() / G.V();
}
int numberOfSelfloops(Graph G)
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
ostream &operator <<(ostream&out, Graph G)
{
	out << G._v << " vertices, " << G._e << " edges\n";
	for (int v = 0; v < G.V(); v++)
	{
		out << v << ":";
		const Vertex &vertex = G.adj(v);
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
Graph::Graph(int v)
{
	_v = v;
	_e = 0;
	_vtables = new Vertex[_v];
}
Graph::Graph(istream &in)
{
	int E;
	cin >> _v >>E;
	_vtables = new Vertex[_v];
	for (int i = 0; i <= E; i++)
	{
		int v, w,weight;
		cin >> v >> w>>weight;
		addEdge(v, w,weight);
	}

}
void Graph::addEdge(int v, int w,int weight)//到底有没有哨兵节点？
{
	Edge *tmp = _vtables[v].adj;
	_vtables[v].adj = new Edge(w, weight, tmp);
	_vtables[v].degree++;
	tmp = _vtables[w].adj;
	_vtables[w].adj = new Edge(v, weight, tmp);
	_vtables[w].degree++;
}
const Vertex& Graph::adj(int v)
{
	if (v > _v)printf("input v bigger than _v\n");
	return _vtables[v];
}
void Graph::removeVertex(int v)
{
	Edge *adj = _vtables[v].adj;
	while (adj !=nullptr)
	{
		removeEdge(adj->_v, v);//移边操作自然会将adj中的边删除，所以不需要adj = ajd-》next；
	}
}
void Graph::removeEdge(int v, int w)
{
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
	//	printf("The Edge:%d -- %d do not exit\n", v, w);
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
	//	printf("The Edge:%d -- %d do not exit\n", w, v);
	//	return;
	//}

}
void Graph::removeEdgeFromVtables(int vtables, int dest)
{
	Edge *tmp = _vtables[vtables].adj;
	Edge *preTmp = _vtables[vtables].adj;
	while (tmp != nullptr&&tmp->_v != dest)
	{
		preTmp = tmp;
		tmp = tmp->_next;
	}
	if (tmp != nullptr)
	{
		preTmp->_next = tmp->_next;
		delete tmp;
		tmp = nullptr;
	}
	else
	{
		printf("The Edge:%d -- %d do not exit\n", vtables, dest);
		return;
	}
}
Graph::~Graph()
{
	for (int i = 0; i < _v; i++)
	{
		removeVertex(i);
	}
}
