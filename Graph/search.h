#pragma once
#include"Graph.h"
class DephthFristSearch
{
public:
	DephthFristSearch(Graph G, int s);
	~DephthFristSearch();
	void dfs(const Graph&, int s);
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
	const int*pathTo(int v)const; 
private:
	int *_cost;//s到相应节点的权重
	bool *_marked;
	int _count;
	int *_edgeTo;
	int _s;//起点
	DepthFristPaths(const DepthFristPaths&);
	const DepthFristPaths& operator=(const DepthFristPaths&);
	void dfs(const Graph&, int v);
};