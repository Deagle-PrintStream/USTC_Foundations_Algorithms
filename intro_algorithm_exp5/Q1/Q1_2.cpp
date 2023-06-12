/*
Edmonds-Karp ALG
*/
#include <stdio.h>
#include <queue>

inline const int read_uint(void)
{
	int x = 0;
	char ch = getchar();
	while (ch == '\n' || ch == ' ')
		ch = getchar();
	while (ch >= '0' && ch <= '9')
		x = x * 10 + ch - '0', ch = getchar();
	return x;
}

class Graph
{
private:
	const int edges; /*size of edges E*/
	int *pre;	/*pre node of each edge*/
	int **adjMat; /*adjacency matrix for graph*/

private:
	/*return true if `from` and `to` are reachable*/
	inline const bool BFS(int from, int to);	

public:
	explicit Graph(int _edges);
	~Graph();
	/*add a new edge, update the adjacency matrix*/
	inline void add_edge(int from, int to, int val);
	/*calculate the max flow from `from` to `to`*/
	inline const int get_max_flow(int from, int to);
};

Graph::Graph(int _edges):edges(_edges+1)
{
	pre = new int[edges];
	adjMat = new int *[edges];
	for (int i = 0; i < edges; i++)
	{
		adjMat[i] = new int[edges];
		for (int j = 0; j < edges; j++)
		{
			adjMat[i][j] = 0;
		}
	}
}

Graph::~Graph()
{
	delete[] pre;
	for (int i = 0; i < edges; i++)
	{
		delete[] adjMat[i];
	}
	delete[] adjMat;
}

const bool Graph::BFS(int from, int to)
{
	for (int i = 0; i < edges; i++)
	{
		pre[i] = -1;
	}
	pre[from] = from;

	std::queue<int> Q;
	Q.push(from);
	while (Q.empty()==false)
	{

		int u = Q.front();
		Q.pop();
		for (int i = 1; i < edges; i++)
		{
			if (adjMat[u][i] > 0 && pre[i] == -1)
			{
				pre[i] = u;
				Q.push( i);
				if (i == to)
				{
					return true;
				}
			}
		}
	}
	return false;
}

void Graph::add_edge(int from, int to, int val)
{
	adjMat[from][to] = val;
}

const int Graph::get_max_flow(int from, int to)
{
	int max_flow = 0;
	while (BFS(from, to)==true)
	{
		int cost = adjMat[pre[to]][to];
		for (int u = to; u != from; u = pre[u])
		{
			int new_c=adjMat[pre[u]][u];
			if(new_c<cost){
				cost=new_c;
			}
		}
		max_flow += cost;
		for (int u = to; u != from; u = pre[u])
		{
			adjMat[pre[u]][u] -= cost;
			adjMat[u][pre[u]] += cost;
		}
	}
	return max_flow;
}

int main()
{
	int n = 0, m = 0;
	scanf("%d %d\n", &n, &m);
	Graph G(n);
	int u, v, w;
	for (int i = 0; i < m; i++)
	{
		u = read_uint();
		v = read_uint();
		w = read_uint();
		G.add_edge(u, v, w);
	}
	int start = 0, end = 0;
	scanf("%d %d\n", &start, &end);
	printf("%d", G.get_max_flow(start, end));
	return 0;
}
