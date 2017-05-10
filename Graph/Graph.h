#pragma once
#include <vector>
#include<string>
#include<iostream>
#include <stdarg.h>
using namespace std;
class Vertex;
class Edge
{
	friend class Vertex;
	friend ostream &operator<<(ostream&out, const Edge &E);
	//friend class Graph;
public:
	Edge(int src,int dest, int weight, Edge*next)
	{
		_src = src;
		_dest = dest;
		_weight = weight;
		_next = next;
	}
	Edge()//默认构造尾链点
	{
		_src = -1;
		_dest = -1;
		_weight = -1;
		_next = nullptr;
	}
	Edge& operator =(const Edge&e)
	{

		_src = e._src;
		_dest = e._dest;
		_weight = e._weight;
		_next = e._next;
		return *this;
	}
	int getDest() const{ return _dest; }
	int getSrc() const{ return _src; }
	int getWeight() const{ return _weight; }
	Edge *getNext() const { return _next; }
	int lessThan(const Edge &that)const
	{
		if (_weight < that._weight)return 1;
		else if (_weight > that._weight)return -1;
		else return 0;
	}
	int _weight;
	int _dest;//边指向的另外一个节点
	Edge *_next;//下一条边
	int _src;
private:

};
class Vertex
{
	//friend class Graph;
	friend ostream &operator <<(ostream&out, const Vertex &V);
public:
	int _v;
	Vertex(int v = -1);
	void addEdge(int src, int dest, int weight);
	bool removeEdge(int dest);
	~Vertex();
	int _degree;
	Edge * _adj;
private:
	//Vertex(const Vertex&);
	//Vertex &operator = (const Vertex&);

	
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
	int numberOfSelfloops();
	int _source;
	int _end;
	int _numMustNode;
	int _numMustEdge;
	int _noEdgeNum;
	int _Maxnumpoints;
	vector<int> _mustNode;
	int _weightHaveToAdd;
private:
	int _v;
	int _e;
	vector<Vertex> _vtables;
	Graph(const Graph&);
	const Graph &operator =(const Graph &);
	
};
ostream &operator <<(ostream&out, const Graph &G);
ostream &operator <<(ostream&out, const Vertex &V);
ostream &operator<<(ostream&out, const Edge &E);
int log(const char* fmt, ...);
