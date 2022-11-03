#include <stdio.h>
#include "Graph_vo_huong.c"

int parent[MAX_N];
int mark[MAX_N];

void DFS(Graph *G, int u, int p)
{
    if (mark[u] != 0)
        return;
    mark[u] = 1;
    parent[u] = p;
    List L = neighbors(G, u);
    int i;
    for (i = 1; i <= L.size; i++)
        if (mark[element_at(&L, i)] == 0)
            DFS(G, element_at(&L, i), u);
}

int main()
{
    Graph G;
    freopen("Graph.txt", "r", stdin);
    int n, m;
    scanf("%d%d", &n, &m);
    init_graph(&G, n);
    int i;
    for (i = 1; i <= m; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(&G, u, v);
    }
    for (i = 1; i <= G.n; i++)
        mark[i] = 0;
    for (i = 1; i <= G.n; i++)
        if (mark[i] == 0)
            DFS(&G, i, 0);
    for (i = 1; i <= G.n; i++)
        printf("%d %d\n", i, parent[i]);
}