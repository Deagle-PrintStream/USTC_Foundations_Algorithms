#include <stdio.h>  //for fast int read and write
#include <iostream> //for namespace std

/*maximum amount of vertex*/
#define N (600)
/*maximum amount of edgs*/
#define M (42000)
/*mark of infinity*/
#define INFTY (0x0FFFFFFF)

int graph[N][N]; // weight of edges
int dist[N][N];  // min distance of vertex pairs

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

/*init the matrix with all INFTY*/
inline void init_graph(int G[][N], const int n)
{
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      G[i][j] = INFTY;
    }
  }
}

/*@brief get the minimum distance of all pairs of vertex*/
inline void FloydWarshall(int graph[][N], const int n)
{
  for (int i = 0; i < n; ++i)
  {
    for (int j = 0; j < n; ++j)
    {
      dist[i][j] = graph[i][j];
    }
  }
  for (int k = 0; k < n; ++k)
  {
    for (int i = 0; i < n; ++i)
    {
      for (int j = 0; j < n; ++j)
      {
        if (dist[i][k] == INFTY || dist[k][j] == INFTY)
          continue;
        if (dist[i][j] > dist[i][k] + dist[k][j])
          dist[i][j] = dist[i][k] + dist[k][j];
      }
    }
  }
}

/* @brief check if graph has a loop with a sum of negative weigh
  @note exit(0) instantly if negative loop exists.
*/
inline void check_neg_cycle(int G[][N], const int n)
{
  static const char msg[] = "negative-weight cycle";
  int start = 0, end = 1;
  if (n <= 1)
    return;
  for (int k = 0; k < n; ++k)
  {

    if (dist[start][k] == INFTY || dist[k][end] == INFTY)
      continue;
    if (dist[start][end] > dist[start][k] + dist[k][end])
    {
      printf(msg);
      std::exit(0);
    }
  }
}

int main()
{
  /*real size of vertex*/
  int n = 0;
  /*real size of edges*/
  int m = 0;
  scanf("%d %d\n", &n, &m);
  init_graph(graph, n);

  /*input the graph*/
  int u = 0, v = 0, w = 0;
  for (int i = 0; i < m; i++)
  {
    u = read_int() - 1; /*count from 0*/
    v = read_int() - 1;
    w = read_int();
    graph[u][v] = w;
  }

  /*get min distance for each pair of node*/
  FloydWarshall(graph, n);
  /*check the graph for negative loop*/
  check_neg_cycle(graph, n);
  /*output*/
  int q = 0;
  scanf("%d\n", &q);
  for (int i = 0; i < q; i++)
  {
    u = read_int() - 1;
    v = read_int() - 1;
    write_int(dist[u][v]);
    putchar('\n');
  }
  return 0;
}
