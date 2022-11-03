#include <stdio.h>

#include "Graph_vo_huong.c"

int mark[MAX_N];

void DFS_Re(Graph *G, int n)
{
    if (mark[n] != 0)
        return;
    printf("%d\n", n);
    mark[n] = 1;
    List L = neighbors(G, n);
    int i;
    for (i = 1; i <= L.size; i++)
        if (mark[element_at(&L, i)] == 0)
            DFS_Re(G, element_at(&L, i));
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
            DFS_Re(&G, i);
    return 0;
}