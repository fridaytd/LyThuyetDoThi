#include <stdio.h>

#include "Graph_vo_huong.c"

int mark[MAX_N];

void DFS(Graph *G, int u)
{
    if (mark[u] != 0)
        return;
    mark[u] = 1;
    List L = neighbors(G, u);
    int i;
    for (i = 1; i <= L.size; i++)
        if (mark[element_at(&L, i)] == 0)
            DFS(G, element_at(&L, i));
}

int isConnected(Graph *G)
{
    int i;
    for (i = 1; i <= G->n; i++)
        mark[i] = 0;
    DFS(G, 1);
    for (i = 1; i <= G->n; i++)
        if (mark[i] == 0)
            return 0;
    return 1;
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
    if (isConnected(&G))
        printf("CONNECTED");
    else
        printf("DISCONNECTED");
}