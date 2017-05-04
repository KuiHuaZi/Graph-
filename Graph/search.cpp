#include"search.h"
DephthFristSearch::DephthFristSearch(Graph &G, int s)
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
	for (int i = 0; i < G.V(); i++)
	{
		_edgeTo[i] = -1;
	}
	_edgeTo[s] = _s;
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

const vector<int>*DepthFristPaths::pathTo(int v)//返回的容器里只有一个元素的话，那么要么是源点，要么就是不可达。
{
	if (!hasPathTo(v))
	{
		cout << "no path to:v!\n";
		return nullptr;
	}
	vector<int> *path = new vector<int>;
	for(int x=v;x!=_s;x=_edgeTo[x])
	{
		path->insert(path->begin(), x);
	}
	path->insert(path->begin(), _s);
	return path;

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
int searchMain()
{
	Graph g(cin);
	int s;
	cin >> s;
	DepthFristPaths path(g, s);
	for (int v = 0; v < g.V(); v++)
	{
		if (path.hasPathTo(v))
		{
			const vector<int> *tmp = path.pathTo(v);
			for (int x : *tmp)
			{
				if (x == s)cout << "s:" << s;
				else
				{
					cout << "-" << x;
				}
			}
			cout << "  cost:"<<path.costOfpathTo(v) <<endl;
			delete tmp;
		}
	}
	return 1;
}