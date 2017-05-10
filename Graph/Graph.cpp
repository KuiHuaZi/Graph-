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
Vertex::Vertex(int v)
{
	log("Vertex():begin!\n");
	_v = v;
	_degree = 0;
	_adj = nullptr;
	log("Vertex():end!\n");
}
void Vertex::addEdge(int src, int dest, int weight)
{
	//if (_v == -1)_v = src;//Ȩ��֮�ƣ�
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
	_vtables.resize(_v);//�ȸ�ÿ�������洢��Ⱥ�ָ���ڽӱ��ָ��Ŀռ䡣Ĭ��degree=0��adj = nullptr��
	log("[Graph(int %d)]end!\n",v);
}
Graph::Graph(istream &in)//����������ȡͼ�������ʽΪ����������v��e����Ȼ��+e��������һ������Ϊ�������ֱ���Դ��Ŀ�ģ�Ȩ��
{
	log("[Graph(istream &in)]begin!\n");
	int E;
	cin >> _v >>E;
	log("input:_v:%d E:%d\n", _v, E);
	_vtables.resize(_v);
	for (int i = 1; i <= E; i++)
	{
		int v, w,weight;
		cin >> v >> w>>weight;
		log("input:src:%d  dest:%d  weight:%d\n ", v, w, weight);
		_vtables[v]._v = v;
		_vtables[w]._v = w;
		addEdge(v, w,weight);
	}
	cin >> _numMustNode;
	log("input:_numMustNode: %d : ", _numMustNode);
	_mustNode.resize(_numMustNode);
	for (int i = 0; i <_numMustNode; i++)
	{
		int v;
		cin >> v;
		log("  %d\n", v);
		_mustNode[i] = v;
	}

	cin >> _numMustEdge;
	log("input:_numMustEdge: %d :", _numMustEdge);
	for (int i = 0; i < _numMustEdge; i++)
	{
		int u, v,weight;
		cin >> u >> v>>weight;
		log("mustEdge:%d--%d weight:%d \n", u, v,weight);
		//_weightHaveToAdd += weight;
		removeEdge(u, v);//�ڱ��뾭���ıߵ��м����һ���ڵ㣺ɾ���ؾ��ıߣ�Ȼ�����һ���ڵ㣬������ڵ㽫ԭ�ؾ��ıߵ������˵�����
		_vtables.insert(_vtables.end(), Vertex(_v + 1));
		addEdge(_v + i, u, weight);
		addEdge(_v + i, v, 0);
		//���¼ӵĵ�ͱؾ��ߵ������˵㶼��ӽ�_mustNode�С�
		_mustNode.push_back(_v + i);
		vector<int>::iterator it;
		it = find(_mustNode.begin(), _mustNode.end(), u);//
		if (it != _mustNode.end())_mustNode.push_back(u);
		it = find(_mustNode.begin(), _mustNode.end(), v);
		if (it != _mustNode.end())_mustNode.push_back(v);
	}
	log("\n");
	cin >> _noEdgeNum;
	log("input:_noEdgeNum:%d", _noEdgeNum);
	for (int i = 0; i < _noEdgeNum; i++)
	{
		int u, v;
		cin >> u >> v;
		log("noEdge:%d--%d  ", u, v);
		removeEdge(u, v);
	}
	log("\n");
	cin >> _source >> _end;
	log("input:_source:%d  ,_end:%d  \n", _source, _end);
	cin >> _Maxnumpoints;
	log("input:_Maxnumpoints:%d\n", _Maxnumpoints);
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
	Graph g(cin);//��������������ͼ��ͬʱ��¼�������Ҫ�����ĵ㣬��¼����ֹ�ڵ㣬ɾ�����ܾ����ıߣ��ڱ��뾭���ıߵ��м����һ���ڵ㣬ͬʱ���ؾ��ߵĶ˵��
	//�����ӵĵ㶼�ӽ��ؾ��ĵ㡣

	//������߶����Ȩ��Ϊ0�������ó������ʱ��Ȩ�ؼ���,ͬʱ�ڵ������Ҫ�ſ�һ���߷ſ�һ����
	//�����б��뾭���Ľڵ㣨������ֹ�ڵ㣩������������е�֮������·�������������ٵ�·��Ȩ�����ٵ�·����ʹ�ù�����ȱ�����ͬʱ��¼�����ģ�
	vector<BFS> leastNumPointsCostPath;
	for (int i = 0; i < g._mustNode.size(); i++)
	{
		leastNumPointsCostPath.push_back(BFS(g, g._mustNode[i]));//���ؾ��ڵ㵽���нڵ�ĵ������·�����
	}
	BFS sourceTo(g, g._source);// endTo(g, g._end);//����ֹ�ڵ㵽���нڵ�ĵ������·�����
	vector< vector<int> > paths;//�����洢��ͬ���е�·��
	vector<int> pathsCostPoints;//�����洢��Ӧ·����cost
	vector<int> pathsCostWeight;//�����洢��Ӧ·����Ȩ��
	int maxPointNum = g._Maxnumpoints; //+ g._numMustEdge;����Ҫ����Ϊ����㿪����ʱ�򣬲����������㣬���Բ���Ҫ�ſ�����//��Ϊ��ÿһ���ؾ��ı߶������һ�������ڵĵ㣬���Խڵ�����Ҫ�ſ�
	sort(g._mustNode.begin(), g._mustNode.end());
	int pathId = 0, bestCost = 100000;
	do 
	{
		int costPoints = 0, costWeight = 0;
		
		costPoints += sourceTo.costTo(g._mustNode[0]);
		costWeight += sourceTo.weightTo(g._mustNode[0]);
		vector<int>path(*sourceTo.pathTo(g._mustNode[0]));
		for (int i = 0; i < g._mustNode.size()-1; i++)
		{
			for (int j = 0; j < leastNumPointsCostPath.size(); j++)//�ҵ���_mustNode[i]��bfs�Ľ����Ȼ���_mustNode[i]��_mustNode[i+1]��·����ӽ�ȥ
			{
				if (leastNumPointsCostPath[j]._s == g._mustNode[i])
				{
					costPoints += leastNumPointsCostPath[j].costTo(g._mustNode[i+1] );
					costWeight += leastNumPointsCostPath[j].weightTo(g._mustNode[i+1] );
					path.insert(path.end(), (*leastNumPointsCostPath[j].pathTo(g._mustNode[i+1])).begin()+1, (*leastNumPointsCostPath[j].pathTo(g._mustNode[i + 1])).end());//����i��i+1��·����ӽ�path�ȥ����һ���ڵ㣬��Ϊ���֮ǰ·���������غ�
					break;
				}
			}
			if (costPoints > maxPointNum)//��ʱ�ڵ���Ŀ�������ơ�
			{
				costPoints = -1;
				costWeight = -1;
				//path = { -1 };
				break;
			}
			
		}
		//������һ��_mustNode��end�����·���ͻ���
		if (costPoints != -1)//˵����·�����壬ֱ�Ӽ�����һ������
		{

			continue;
		}
		//else if((costPoints+=leastNumPointsCostPath[leastNumPointsCostPath.size()-1].costTo(g._end))>maxPointNum)//����������������һ���㵽�յ�Ŀ�������������
		//{
		//	continue;
		//}
		else
		{
			for (int j = 0; j < leastNumPointsCostPath.size(); j++)//�ҵ���_mustNode[i]��bfs�Ľ����Ȼ���_mustNode[i]��_mustNode[i+1]��·����ӽ�ȥ
			{
				if (leastNumPointsCostPath[j]._s == g._mustNode[g._mustNode.size()-1])//�����һ���ڵ�
				{
					costPoints += leastNumPointsCostPath[j].costTo(g._end);
					if (costPoints > maxPointNum)
					{
						break;//���ڽڵ����ƣ�ֱ������ȥ������·����ӡ�
					}
					pathsCostPoints.push_back(costPoints);
					costWeight += leastNumPointsCostPath[j].weightTo(g._end);
					pathsCostWeight.push_back(costWeight);
					path.insert(path.end(), (*leastNumPointsCostPath[j].pathTo(g._end)).begin() + 1, (*leastNumPointsCostPath[j].pathTo(g._end)).end());//��_mustNode������һ���ڵ㵽_end�ڵ��·����ӽ�ȥ
					paths.push_back(path);
					break;
				}
			}

		}
		
		


	} while (next_permutation(g._mustNode.begin(),g._mustNode.end()));
	//�����бؽ��ڵ����ȫ���У�����˳���ҳ���������ڵ���ĿС��Ҫ���·
	for (int i = 0; i < paths.size(); i++)
	{
		log("paths:\n costPoints:%d \n costWeight:%d \n", pathsCostPoints[i], pathsCostWeight[i]);
		for (int j = 0; j < paths[i].size(); j++)
		{
			cout << paths[i][j] << "---";
		}
		cout << endl;
	}

	//�����Ȩ�ء�����ÿ���ⶼ�ñ�/·�滻ȥ����������������Ž⣬Ȼ�󷵻س����Ž⡣
}
