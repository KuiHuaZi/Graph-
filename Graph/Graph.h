#pragma once
#include <vector>
#include<string>
#include<iostream>
using namespace std;
class Graph
{
public:
	Graph(int numOfV);//����һ������v�����㵫�����ߵ�ͼ
	Graph(istream in);//�ӱ�׼����������һ��ͼ����V����E��Ȼ�󶥵��
	int V() { return _v; }
	int E() { return _e; }
	void addEdge(int v, int w);//���һ����v-w
	vector<int>adj(int v);//����v���ھӽڵ�
	friend ostream &operator <<(ostream&out, Graph G);
private:
	int _v;
	int _e;
};
ostream &operator <<(ostream&out, Graph G);
