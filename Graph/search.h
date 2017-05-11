#pragma once
#include"Graph.h"
#include<queue>
using namespace std;
class DephthFristSearch
{
public:
	DephthFristSearch(Graph &G, int s);
	~DephthFristSearch();
	void dfs(const Graph &G, int s);
	bool marked(int w) { return _marked[w]; }
	int count() { return _count; }
private:
	bool *_marked;
	int _count;
	DephthFristSearch(const DephthFristSearch&);
	const DephthFristSearch& operator=(const DephthFristSearch&);
};
class DepthFristPaths
{
public:
	DepthFristPaths(Graph &G, int s);
	~DepthFristPaths();
	bool hasPathTo(int v)const;
	const vector<int>*pathTo(int v); 
	int costOfpathTo(int v) { return _cost[v]; }
private:
	int *_cost;//s到相应节点的权重
	bool *_marked;
	int _count;
	int *_edgeTo;
	int _s;//起点
	DepthFristPaths(const DepthFristPaths&);
	const DepthFristPaths& operator=(const DepthFristPaths&);
	void dfs(const Graph&G, int v);
};
int searchMain();
class BFS
{
public:
	BFS(Graph &G, int s);
	BFS()
	{
		log("BFS:mo ren gouzhao\n");
	}
	~BFS();
	void bfs(Graph&G, int s);
	bool hasPathTo(int v);
	vector<int> *pathTo(int v);
	int costTo(int v);
	int weightTo(int v)
	{
		return _costOfweight[v];
	}
	int _s;
	BFS& operator =(const BFS& b)
	{
		_numOfv = b._numOfv;
		_s = b._s;
		_cost = new int[_numOfv];
		_edgeTo = new int[_numOfv];
		_costOfweight = new int[_numOfv];
		_marked = new bool[_numOfv];
		for (int i = 0; i < _numOfv; i++)
		{
			_cost[i] = b._cost[i];
			_edgeTo[i] = b._edgeTo[i];
			_costOfweight[i] = b._costOfweight[i];
			_marked[i] = b._marked[i];
		}
		log("BFS =:end!\n");
		return *this;
	}
private:
	int _numOfv;
	int *_cost;
	int *_edgeTo;
	bool *_marked;
	int *_costOfweight;
	
};
int BFSMain();