#include <iostream>
#include <vector>
#include <tuple>

#define INF 268435455

int n, m; // n: number of vertices, m: number of edges

using namespace std;

typedef tuple<int, int, int> Edge;
typedef vector<Edge> Graph; // u, v, w
typedef vector<Edge> Tree;  // u, v, w


inline void getint(int & ret);
Tree Kruskal(Graph graph);

int main(){
    extern int n, m;
    int u, v, w; 
    getint(n); getint(m); // n: number of vertices, m: number of edges
    Graph graph; // adjacency matrix
    for (int i = 0; i < m; i++){
        getint(u); getint(v); getint(w);
        u--; v--; // use 0-based indexing
        graph.push_back(make_tuple(u, v, w)); // m edges
    }
    Tree mst = Kruskal(graph);
    int sum = 0;
    printf("\n");
    for (int i = 0; i < mst.size(); i++){
        printf("%d %d %d\n", get<0>(mst[i]) + 1, get<1>(mst[i]) + 1, get<2>(mst[i]));
        sum += get<2>(mst[i]);
    }
    printf("%d\n", sum);
}

void quicksort(vector<Edge> &edges, int left, int right){
    // sort the edges in non-decreasing order of their weights
    if (left >= right)
        return;
    int pivot = get<2>(edges[left]);
    int i = left, j = right;
    while (i <= j){
        while (get<2>(edges[i]) < pivot)
            i++;
        while (get<2>(edges[j]) > pivot)
            j--;
        if (i <= j){
            swap(edges[i], edges[j]);
            i++;
            j--;
        }
    }
    quicksort(edges, left, j);
    quicksort(edges, i, right);
}

int find(vector<int> parent, int u){
    if (parent[u] == u)
        return u;
    else
        return find(parent, parent[u]);
}

void Union(vector<int> &parent, int u, int v){
    int u_root = find(parent, u);
    int v_root = find(parent, v);
    parent[u_root] = v_root; // set u's parent to v's parent
}

Tree Kruskal(Graph graph){
    extern int n, m;
    Tree mst; // empty set
    vector<int> parent(n); // disjoint set
    for (int i = 0; i < n; i++)
        parent[i] = i;
    vector<Edge> edges = graph;
    quicksort(edges, 0, m-1);
    // check if correctly sorted
    printf("\n");
    for (int i = 0; i < edges.size(); i++)
        printf("%d %d %d\n", get<0>(edges[i]) + 1, get<1>(edges[i]) + 1, get<2>(edges[i]));
    printf("\n");
    for (int i = 0; i < edges.size(); i++){
        int u = get<0>(edges[i]), v = get<1>(edges[i]);
        if (find(parent, u) != find(parent, v)){
            printf("u: %d, v: %d\n", u+1, v+1);
            mst.push_back(edges[i]);
            Union(parent, u, v);
        }
    }
    return mst;
}

int Weight(Tree t){
    int sum = 0;
    for (int i = 0; i < t.size(); i++)
        sum += get<2>(t[i]);
    return sum;
}

inline void getint(int & ret){
    ret = 0;
    char c;
    while((c = getchar()) < '0' || c > '9');
    while(c >= '0' && c <= '9'){
        ret = ret * 10 + c - '0';
        c = getchar();
    }
}