#include <stdio.h>
#include <vector>

class Graph
{
private:
  /*amount of vertices*/
  const int n;
  /*amount of edges, flexible since later new edgs may be added*/
  int m;
  /*adjacent table of vertex*/
  std::vector<std::vector<int>> adj;
  /*used in DFS to mark if one vertex has been visited*/
  std::vector<bool> visited;

public:
  Graph(int n, int m);
  ~Graph();
  /*add a new edge between u and v*/
  inline void add_edge(int u, int v);
  /*check if u and v are reachable whereby DFS Alg.
  @retval true for connected, false for not*/
  inline const bool find_path(int u, int v);
  /*reset visited[]*/
  inline void reset_visited();
};

Graph::Graph(int _n, int _m) : n(_n), m(_m)
{
  adj.resize(n + 1);
  visited.resize(n + 1, false);
}

Graph::~Graph(void)
{
  adj.clear();
  visited.clear();
}

void Graph::add_edge(int u, int v)
{
  adj[u].push_back(v);
  m++;
}

const bool Graph::find_path(int u, int v)
{
  visited[u] = true;
  bool flag = false;
  if (u == v)
    return true;

  for (int i = 0; i < adj[u].size(); i++)
  {
    if (visited[adj[u][i]] == false)
    {
      flag = find_path(adj[u][i], v);
    }
    if (flag == true)
      return true;
  }
  return flag;
}

void Graph::reset_visited()
{
  for (int i = 1; i <= n; i++)
    visited[i] = false;
}

inline const int read_int(void)
{
  int x = 0;
  char ch = getchar();
  while (ch == '\n' || ch == ' ')
    ch = getchar();
  while (ch >= '0' && ch <= '9')
    x = x * 10 + ch - '0', ch = getchar();
  return x;
}

/*add a new edge into graph*/
inline void add_edge(Graph &G)
{
  int u = read_int();
  int v = read_int();
  G.add_edge(u, v);
}

/*check if u and v are reachable*/
inline void query(Graph &G)
{
  int u = read_int();
  int v = read_int();

  G.reset_visited();
  putchar(G.find_path(u, v) + '0');
  putchar('\n');
}

int main()
{
  int n = 0, m = 0;
  scanf("%d %d\n", &n, &m);
  /*input the graph*/
  Graph G(n, m);
  for (int i = 0; i < m; i++)
  {
    add_edge(G);
  }

  /*output*/
  int q = 0, op = 0;
  scanf("%d\n", &q);
  for (int i = 0; i < q; i++)
  {
    op = read_int();
    if (op == 0)
    { // query the path
      query(G);
    }
    else if (op == 1)
    { // add new edge
      add_edge(G);
    }
  }

  return 0;
}
