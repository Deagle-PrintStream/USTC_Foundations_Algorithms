#include <stdio.h> //for fast int read and write
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

/*maximum amount of vertex*/
#define N (600)
/*maximum amount of edgs*/
#define M (42000)
/*mark of infinity*/
#define INFTY (0x0FFFFFFF)

struct Edge
{
  int from;
  int to;
  int weight;
};

/*all weight info*/
vector<Edge> edges;
/*all adjucent vertex for each vertex*/
vector<vector<Edge>> adj;
/*min distance array for temp usage*/
vector<int> dist;

inline const int read_int(void)
{
  int x = 0;
  int f = 1;
  char ch = getchar();
  while (ch == '\n' || ch == ' ')
    ch = getchar();
  if (ch == '-')
  {
    f = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9')
    x = x * 10 + ch - '0', ch = getchar();
  return x * f;
}

void write_int(int x)
{
  if (x < 0)
  {
    putchar('-');
    x = -x;
  }
  if (x > 9)
    write_int(x / 10);
  putchar(x % 10 + '0');
}

/*@brief Bellman-Ford sub process, slacken all edges for n times
@param n amount of vertex
@param s randomly picked vertex to start
@note exit(0) instantly if a negative-weighted loop exists*/
inline void BellmanFord(vector<Edge> &edges, int n, int s)
{
  dist.resize(n + 1, INFTY);
  dist[s] = 0;

  for (int i = 1; i <= n; ++i)
  {
    for (auto e : edges)
    {
      if (dist[e.from] < INFTY && dist[e.to] > dist[e.from] + e.weight)
      {
        dist[e.to] = dist[e.from] + e.weight;
      }
    }
  }

  // check negative weighted loop
  for (auto e : edges)
  {
    if (dist[e.from] < INFTY && dist[e.to] > dist[e.from] + e.weight)
    {
      static const char msg[] = "negative-weight cycle";
      printf(msg);
      exit(0);
    }
  }
}

/*@brief Dijkstra sub process, find min distance to all vertex from a start vertex
@param n amount of vertex
@param s vertex to start with
*/
vector<int> Dijkstra(int n, int s)
{
  node<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
  vector<int> dist(n + 1, INFTY);
  vector<bool> vis(n + 1, false);

  dist[s] = 0;
  pq.push({0, s});
  while (!pq.empty())
  {
    auto node = pq.top();
    pq.pop();
    int u = node.second;
    if (vis[u])
      continue;
    vis[u] = true;
    for (auto e : adj[u])
    {
      int v = e.to, w = e.weight;
      if (dist[u] < INFTY && dist[v] > dist[u] + w)
      {
        dist[v] = dist[u] + w;
        pq.push({dist[v], v});
      }
    }
  }
  return dist;
}

int main()
{
  /*real size of vertex*/
  int n = 0;
  /*real size of edges*/
  int m = 0;
  scanf("%d %d\n", &n, &m);

  /*input the graph*/
  int u = 0, v = 0, w = 0;
  for (int i = 0; i < m; i++)
  {
    u = read_int(); /*count from 1*/
    v = read_int();
    w = read_int();
    edges.push_back({u, v, w});
  }

  /*construct a new graph with a new virtual vertex s, set weight between s and all other vertex with 0 */
  int s = 0;
  vector<Edge> edges_new = edges;
  for (int v = 1; v <= n; ++v)
  {
    edges_new.push_back({s, v, 0});
  }
  /*whereby Bellman Ford Alg, we get the min distance from s to all other vertex*/
  BellmanFord(edges_new, n, s);

  /*alter weight with new form: w'(u,v) = w(u,v) + h(u) - h(v)*/
  for (auto &e : edges_new)
  {
    e.weight = e.weight + dist[e.from] - dist[e.to];
  }

  /*construct the adjucent table for new graph, which is needed in Dijkstra Alg*/
  adj.resize(n + 1);
  for (auto const e : edges_new)
  {
    adj[e.from].push_back(e);
  }

  /*execute Dijkstra Alg upon all vertexes as source and store the distance value in dist_all*/
  vector<vector<int>> dist_all(n + 1, vector<int>(n + 1, INFTY));
  for (int i = 1; i <= n; ++i)
  {
    auto d = Dijkstra(n, i);
    for (int j = 1; j <= n; ++j)
    {
      if (d[j] == INFTY)
        continue;
      dist_all[i][j] = d[j] + dist[j] - dist[i];
    }
  }
  /*output*/
  int q = 0;
  scanf("%d\n", &q);
  for (int i = 0; i < q; i++)
  {
    u = read_int();
    v = read_int();
    write_int(dist_all[u][v]);
    putchar('\n');
  }
  return 0;
}
