#include "Graph.h"
#include"search.h"
//int degree(Graph& G, int v)
//{
//	int degree = 0;
//	degree = G.adj(v).degree;
//	return degree;
//}
//int maxDegree(Graph &G)
//{
//	int max = 0;
//	for (int v = 0; v < G.V(); v++)
//	{
//		if (degree(G, v) > max)max = degree(G, v);
//
//	}
//	return max;
//}
//double avgDegree(Graph &G)
//{
//	return 2 * G.E() / G.V();
//}
//int numberOfSelfloops()
//{
//	int count = 0;
//	for(int v = 0; v < G.V(); v++)
//	{
//		const Vertex &vertex = G.adj(v);
//		const Edge *tmp = vertex.
//		for (int i = 0; i < vertex.degree; i++)
//		{
//			if (tmp->_v == v)
//				count++;
//				tmp = tmp->_next;
//		}
//	}
//	return count / 2;
//}
Vertex::Vertex()
{
	log("Vertex():begin!\n");
	_v = -1;
	_degree = 0;
	_adj = nullptr;
	log("Vertex():end!\n");
}
void Vertex::addEdge(int src, int dest, int weight)
{
	if (_v == -1)_v = src;//Ȩ��֮�ƣ�
	log("Vertex(%d):addEgde( src = %d, dest = %d, weight = %d ):begin��\n", _v, src, dest, weight);
	if (src != _v)
	{
		log("Error:The source of Edge is not this Vertex��\n");
		return;
	}
	Edge *old = _adj;
	_adj = new Edge(_v, dest, weight, old);//��ͷ��ʼ�����
	_degree++;
	log("Vertex(%d):addEgde( src = %d, dest = %d, weight = %d ):end��\n", _v, src, dest, weight);
}

bool Vertex::removeEdge(int dest)
{
	Edge *current = _adj;
	Edge *pre = nullptr;
	while (current != nullptr&&current->getDest() != dest)
	{
		pre = current;
		current = current->_next;
	}
	if (current != nullptr)
	{
		if (pre == nullptr)//˵��Ҫ�Ƴ��ڽӱ�ĵ�һ����,��_adjָ���������
		{
			_adj = current->_next;
			log("[Vertex(%d).removeEdge(%d)]:remove frist Edge in _adj success!\n", _v, dest);
		}
		else
		{
			pre->_next = current->_next;

			log("[Vertex(%d).removeEdge(%d)]:remove Edge in _adj success!\n", _v, dest);
		}
		delete current;
		current = nullptr;
		--_degree;
		return true;
	}
	else
	{
		log("[Vertex(%d).removeEdge(%d)]:No this edge in _adj!\n", _v, dest);
		return false;
	}
}

Vertex::~Vertex()
{
	log("[~Vertex(%d)]:begin!\n", _v);
	while (_adj != nullptr)
	{
		removeEdge(_adj->_dest);//ÿ�ζ����ڽӱ��еĵ�һ�����Ƴ���ֱ��_adjΪ��
	}
	log("[~Vertex(%d)]:end!\n", _v);
}




ostream &operator <<(ostream&out, const Vertex &V)
{
	out << "Vertex:" << V._v << " ,degree :" << V._degree << endl;
	Edge *tmp = V._adj;
	while (tmp!=nullptr)
	{
		out << *tmp;
		tmp = tmp->getNext();
	}
	return out;
}
ostream &operator<<(ostream&out, const Edge &E)
{
	out<<"<"<<E._src<<" -- "<<E._dest<<" ,weight: "<<E._weight<<" >\n";
	return out;
}
ostream &operator <<(ostream&out, Graph &G)
{
	out << G._v << " vertices, " << G._e << " edges\n";
	for (int v = 0; v < G.V(); v++)
	{
		out << G._vtables[v];
	}
	return out;
}

Graph::Graph(int v)//����һ������ĿΪv������ĿΪ0��ͼ��
{
	log("[Graph(int %d)]begin!\n",v);
	_v = v;
	_e = 0;
	_vtables = new Vertex[_v];//�ȸ�ÿ�������洢��Ⱥ�ָ���ڽӱ��ָ��Ŀռ䡣Ĭ��degree=0��adj = nullptr��
	log("[Graph(int %d)]end!\n",v);
}
Graph::Graph(istream &in)//����������ȡͼ�������ʽΪ����������v��e����Ȼ��+e��������һ������Ϊ�������ֱ���Դ��Ŀ�ģ�Ȩ��
{
	log("[Graph(istream &in)]begin!\n");
	int E;
	cin >> _v >>E;
	log("input:_v:%d E:%d\n", _v, E);
	_vtables = new Vertex[_v];
	for (int i = 1; i <= E; i++)
	{
		int v, w,weight;
		cin >> v >> w>>weight;
		log("input:src:%d  dest:%d  weight:%d\n ", v, w, weight);
		addEdge(v, w,weight);
	}
	log("[Graph(istream &in)]end!\n");
}
void Graph::addEdge(int v, int w,int weight)
{
	log("[addEdge( v:%d  w:%d  weight:%d )]begin!\n",v,w,weight);
	if (v >= _v || w >=_v)
	{
		log("[addEdge]input out of range\n");
		return;
	}
	if(v == w)_vtables[v].addEdge(v, w, weight);
	else
	{
		_vtables[v].addEdge(v, w, weight);
		_vtables[w].addEdge(w, v, weight);
	}
	//Edge *oldhead = _vtables[v].adj;//ÿ�ζ���ͷ�������㣬���ڽӱ��ָ��ָ��ǰҪ����ıߣ�Ȼ�󽫵�ǰҪ����ı�ָ��ԭ��������ͷ
	//_vtables[v].adj = new Edge(w, weight, oldhead);//edge���캯���Ὣִ�С���ǰҪ����ı�ָ��ԭ��������ͷ���������
	//if (_vtables[v].adj == nullptr)
	//{
	//	log("[addEdge]not have enough memory\n");
	//}
	//_vtables[v].degree++;
	//log("[addEdge]:add success:Edge:%d -- %d  weight: %d\n", v, w, weight);
	//oldhead = _vtables[w].adj;
	//_vtables[w].adj = new Edge(v, weight, oldhead);
	//if (_vtables[w].adj == nullptr)
	//{
	//	log("[addEdge]not have enough memory\n");
	//}
	//_vtables[w].degree++;
	//log("[addEdge]:add success:Edge:%d -- %d  weight: %d\n", w, v, weight);
	//_e++;
	log("[addEdge( v:%d  w:%d  weight:%d )]end!\n", v, w, weight);
}
const Vertex& Graph::adj(int v)const//���ر�ʾ����v�Ľṹ������ã��ṹ����adjָ��ָ���ڽӱ�ĵ�һ���ߣ���ָ��null��ʾû�б�
{
	if (v >= _v)
	{
		log("[adj]input out of range\n");
		static Vertex t;
		return t;
	}
	return _vtables[v];
}
void Graph::removeVertex(int v)//�Ȳ�����
{
	//if (v >= _v)
	//{
	//	log("[removeVertex]input out of range\n");
	//	return;
	//}
	//log("[removeVertex]removeVertex:%d\n", v);
	//_vtables[v].degree = 0;
	// 
	//while (_vtables[v].adj !=nullptr)
	//{
	//	log("[removeVertex]adj:%d\n", _vtables[v].adj);
	//	removeEdge(v, _vtables[v].adj->_v);//�Ʊ߲�����Ȼ�Ὣadj�еı�ɾ�������Բ���Ҫadj = ajd-��next��
	//}
}
void Graph::removeEdge(int v, int w)
{
	if (v >= _v || w >= _v)
	{
		log("[removeEdge]input out of range\n");
		return;
	}
	log("[removeEdge(v:%d  w:%d)]begin!\n",v,w);
	_vtables[v].removeEdge(w);
	_vtables[w].removeEdge(v);
	//Edge *tmp = _vtables[v].adj;
	//Edge *preTmp = _vtables[v].adj;
	//while (tmp != nullptr&&tmp->_v!=w)
	//{
	//	preTmp = tmp;
	//	tmp = tmp->_next;
	//}
	//if (tmp != nullptr)
	//{
	//	preTmp->_next = tmp->_next;
	//	delete tmp;
	//	tmp = nullptr;
	//}
	//else
	//{
	//	log("The Edge:%d -- %d do not exit\n", v, w);
	//	return;
	//}

	//tmp = _vtables[w].adj;
	//preTmp = _vtables[w].adj;
	//while (tmp != nullptr&&tmp->_v != v)
	//{
	//	preTmp = tmp;
	//	tmp = tmp->_next;
	//}
	//if (tmp != nullptr)
	//{
	//	preTmp->_next = tmp->_next;
	//	delete tmp;
	//	tmp = nullptr;
	//}
	//else
	//{
	//	log("The Edge:%d -- %d do not exit\n", w, v);
	//	return;
	//}

}
Graph::~Graph()
{
	log("[~Graph]begin\n");
	for (int i = 0; i < _v; i++)
	{
		
		removeVertex(i);
	}
	delete[] _vtables;

	log("[~Graph]end\n");
}

int log(const char* format, ...)
{

	va_list vp;
	va_start(vp, format);
	int result = vprintf(format, vp);
	va_end(vp);
	return result;

}
void GraphMain()
{
	Graph t(cin);
	cout << t;
}
int main()
{
	while (true)
	{
		BFSwithNoWeightMain();
	}
}
