#pragma once
#include <vector>
#include<string>
#include<iostream>
using namespace std;
class Graph
{
public:
	Graph(int numOfV);//创建一个含有v个顶点但不含边的图
	Graph(istream in);//从标准输入流读入一副图，先V，后E，然后顶点对
	int V() { return _v; }
	int E() { return _e; }
	void addEdge(int v, int w);//添加一条变v-w
	vector<int>adj(int v);//顶点v的邻居节点
	friend ostream &operator <<(ostream&out, Graph G);
private:
	int _v;
	int _e;
};
ostream &operator <<(ostream&out, Graph G);
