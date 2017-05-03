#pragma once
#include <vector>
#include<string>
#include<iostream>
#include <stdarg.h>
using namespace std;
struct Edge
{
	int _weight;
	int _v;//��ָ�������һ���ڵ�
	Edge *_next;//��һ����
	Edge(int v, int weight, Edge*next)
	{
		_v = v;
		_weight = weight;
		_next = next;
	}
	Edge()//Ĭ�Ϲ���β����
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
