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
class BFSwithNoWeight
{
public:
	BFSwithNoWeight(Graph &G, int s);
	~BFSwithNoWeight();
	void bfs(Graph&G, int s);
	bool hasPathTo(int v);
	const vector<int> *pathTo(int v);
	int costTo(int v);
private:
	int *_cost;
	int *_edgeTo;
	bool *_marked;
	int _s;
};
int BFSwithNoWeightMain();