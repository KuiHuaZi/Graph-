#pragma once
#include <vector>
#include<string>
#include<iostream>
#include <stdarg.h>
using namespace std;
struct Edge
{
	int _weight;
	int _v;//边指向的另外一个节点
	Edge *_next;//下一条边
	Edge(int v, int weight, Edge*next)
	{
		_v = v;
		_weight = weight;
		_next = next;
	}
	Edge()//默认构造尾链点
	{
		_v = -1;
		_weight = -1;
		_next = nullptr;
	}

};
struct Vertex
{
	int degree;
	Edge * adj;
	Vertex()
	{
		degree = 0;
		adj = nullptr;
	}
};
class Graph
{
public:
	Graph(int numOfV);//创建一个含有v个顶点但不含边的图
	Graph(istream &in);//从标准输入流读入一副图，先V，后E，然后顶点对
	int V() { return _v; }
	int E() { return _e; }
	void addEdge(int v, int w,int weight);//添加一条变v-w
	const Vertex &adj(int v)const;//顶点v的邻居节点
	friend ostream &operator <<(ostream&out, Graph &G);
	~Graph();
	void removeVertex(int v);
	void removeEdge(int v, int w);
private:
	int _v;
	int _e;
	Vertex *_vtables;
	void removeEdgeFromVtables(int v, int w);
	Graph(const Graph&);
	const Graph &operator =(const Graph &);
	
};
ostream &operator <<(ostream&out, Graph &G);
int log(const char* fmt, ...);
