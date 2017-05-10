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
	Edge()//Ĭ�Ϲ���β����
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
	int _dest;//��ָ�������һ���ڵ�
	Edge *_next;//��һ����
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
	Graph(int numOfV);//����һ������v�����㵫�����ߵ�ͼ
	Graph(istream &in);//�ӱ�׼����������һ��ͼ����V����E��Ȼ�󶥵��
	int V() { return _v; }
	int E() { return _e; }
	void addEdge(int v, int w,int weight);//���һ����v-w
	const Vertex &adj(int v)const;//����v���ھӽڵ�
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
