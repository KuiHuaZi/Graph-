#include "Graph.h"
int degree(Graph G, int v)
{
	int degree = 0;
	degree = G.adj(v).size();
	return degree;
}
int maxDegree(Graph G)
{
	int max = 0;
	for (int v = 0; v < G.V(); v++)
	{
		if (degree(G, v) > max)max = degree(G, v);

	}
	return max;
}
double avgDegree(Graph G)
{
	return 2 * G.E() / G.V();
}
int numberOfSelfloops(Graph G)
{
	int count = 0;
	for(int v = 0; v < G.V(); v++)
	{
		for (int w : G.adj(v))
		{
			if (w == v)
			{
				count++;
			}
		}
	}
	return count / 2;
}
ostream &operator <<(ostream&out, Graph G)
{
	out << G._v << " vertices, " << G._e << " edges\n";
	for (int v = 0; v < G.V(); v++)
	{
		out << v << ":";
		for (int w : G.adj(v))
		{
			out << w << " ";
		}
		out << "\n";
	}
	return out;
}
