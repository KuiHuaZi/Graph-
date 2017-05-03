#include"search.h"
DephthFristSearch::DephthFristSearch(Graph G, int s)
{
	_marked = new bool[G.V()]();
	dfs(G, s);
}

DephthFristSearch::~DephthFristSearch()
{
	delete[]_marked;
}

void DephthFristSearch::dfs(const Graph &G, int v)
{
	_marked[v] = true;
	_count++;
	const Vertex &ver = G.adj(v);
	Edge *e = ver.adj;
	while (e!=nullptr)
	{
		if (!marked(e->_v))
		{
			dfs(G, e->_v);
		}
		e = e->_next;
	}

}
