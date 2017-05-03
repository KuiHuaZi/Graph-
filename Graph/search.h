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