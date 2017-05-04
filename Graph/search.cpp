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
	Edge *e = ver._adj;
	while (e!=nullptr)
	{
		if (!marked(e->_dest))
		{
			dfs(G, e->_dest);
		}
		e = e->_next;
	}

}

DepthFristPaths::DepthFristPaths(Graph & G, int s)
{
	_marked = new bool[G.V()]();
	_edgeTo = new int[G.V()]();
	_cost = new int[G.V()]();
	_s = s;
	dfs(G, s);
}

DepthFristPaths::~DepthFristPaths()
{
	delete[]_marked;
	delete[]_edgeTo;
	delete[]_cost;
}

bool DepthFristPaths::hasPathTo(int v)const
{
	return _marked[v];
}

const int * DepthFristPaths::pathTo(int v)const
{


	return nullptr;
}

void DepthFristPaths::dfs(const Graph &G, int v)
{
	_marked[v] = true;
	_count++;
	const Vertex &ver = G.adj(v);
	Edge *e = ver._adj;
	while (e != nullptr)
	{
		if (!_marked[e->_dest])
		{
			_edgeTo[e->_dest] = e->_src;
			_cost[e->_dest] = _cost[e->_src] + e->_weight;
			dfs(G, e->_dest);
		}
		e = e->_next;
	}

}
