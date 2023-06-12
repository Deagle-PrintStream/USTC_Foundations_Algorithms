#include <stdio.h>
#include <vector>
#include <algorithm>

#define INFTY (0x0fffffff)

struct Edge
{
  int from;
  int to;
  int weight;
  inline bool operator==(const Edge &other) { return this->from == other.from && this->to == other.to; }
};

bool smaller_weight(const Edge &a, const Edge &b) { return a.weight < b.weight; }

class Graph
{
private:
  /*amount of vertices*/
  const int n;
  /*amount of edges, flexible since later new edgs may be added*/
  const int m;
  /*vector for edges*/
  std::vector<Edge> edges;
  std::vector<Edge> tree;
  /*adjacent table of vertex*/
  std::vector<std::vector<int>> adj;
  /*used in DFS to mark if one vertex has been visited*/
  std::vector<bool> marked;
  std::vector<bool> visited;
  inline void DFS(int u, int v);

public:
  Graph(int n, int m);
  ~Graph();
  /*add a new edge between u and v*/
  inline void add_edge(int u, int v, int w);
  /*find the MST*/
  inline void Kruscal(int &mst_w, int &smst_w);

  /*reset visited[]*/
  bool DFS(int u);
};

Graph::Graph(int _n, int _m) : n(_n), m(_m)
{
  edges.clear();
  adj.resize(n + 1);
  tree.clear();
  marked.resize(n + 1, false);
  visited.resize(n + 1, false);
}

Graph::~Graph(void)
{
  edges.clear();
  adj.clear();
  marked.clear();
}

void Graph::add_edge(int u, int v, int w)
{
  edges.push_back({u, v, w});
}

void Graph::Kruscal(int &mst_w, int &smst_w)
{
  int MST_weight = 0;
  int edge_count = 0;
  std::sort(edges.begin(), edges.end(), smaller_weight);
  for (int i = 0; i < n; i++)
  {
    Edge e = edges[i];
    if (marked[e.from] == false || marked[e.to] == false)
    {
      marked[e.from] = marked[e.to] = true;
      MST_weight += e.weight;
      tree.push_back(e);
      adj[e.from].push_back(e.to);
      adj[e.to].push_back(e.from);
      edge_count++;
      if (edge_count >= n + 1)
      {
        break;
      }
    }
  }

  for (int idx = tree.size() - 1; idx >= 0; idx--)
  {
    Edge max_e = tree[idx];
    int u = max_e.from;
    int v = max_e.to;

    for (auto p = adj[u].begin(); p != adj[u].end(); p++)
    {
      if (*p == v)
      {
        adj[u].erase(p);
        break;
      }
    }
    for (auto p = adj[v].begin(); p != adj[v].end(); p++)
    {
      if (*p == v)
      {
        adj[v].erase(p);
        break;
      }
    }

    DFS(max_e.from);
    std::vector<int> bridge_w;
    for (int i = 0; i < edges.size(); i++)
    {
      if (marked[edges[i].from] != marked[edges[i].to])
      {
        bridge_w.push_back(edges[i].weight);
      }
    }
    if (bridge_w.size() > 1)
    {
      std::sort(bridge_w.begin(), bridge_w.end());
      int s_max_w = bridge_w[1];
      mst_w = MST_weight;
      smst_w = MST_weight - max_e.weight + s_max_w;
      return;
    }
    adj[u].push_back(v);
    adj[v].push_back(u);
    visited.resize(n + 1, false);
    marked.resize(n + 1, true);
  }
}

bool Graph::DFS(int u)
{
  marked[u] = false;
  visited[u] = true;

  bool flag = false;

  for (int i = 0; i < adj[u].size(); i++)
  {
    if (visited[adj[u][i]] == false)
    {
      flag = DFS(adj[u][i]);
    }
    if (flag == true)
      return true;
  }
  return flag;
}

inline int read_uint(void)
{
  int x = 0;
  char ch = getchar();
  while (ch == '\n' || ch == ' ')
    ch = getchar();
  while (ch >= '0' && ch <= '9')
    x = x * 10 + ch - '0', ch = getchar();
  return x;
}

int main()
{
  int n = 0, m = 0;
  scanf("%d %d\n", &n, &m);
  /*input the graph*/
  Graph G(n, m);
  int u = 0, v = 0, w = 0;
  for (int i = 0; i < m; i++)
  {
    u = read_uint();
    v = read_uint();
    w = read_uint();
    G.add_edge(u, v, w);
  }
  /*output*/
  int min_tree_w = 0, sub_min_tree_w = 0;
  G.Kruscal(min_tree_w, sub_min_tree_w);
  printf("%d\n%d\n", min_tree_w, sub_min_tree_w);

  return 0;
}
