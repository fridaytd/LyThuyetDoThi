#include <stdio.h>
#include "Queue.c"
#include "Graph_vo_huong.c"

int mark[MAX_N];

void BFS(Graph *G, int x)
{
    Queue Q;
    make_null_queue(&Q);
    enqueue(&Q, x);
    while (!empty(&Q))
    {
        int n = front(&Q);
        dequeue(&Q);
        if (mark[n] == 1)
            continue;
        printf("%d\n", n);
        mark[n] = 1;
        List L = neighbors(G, n);
        int i;
        for (i = 1; i <= L.size; i++)
            if (mark[element_at(&L, i)] == 0)
                enqueue(&Q, element_at(&L, i));
    }
}

int main()
{
    int i;
    Graph G;
    freopen("Graph.txt", "r", stdin);
    int n, m;
    scanf("%d%d", &n, &m);
    init_graph(&G, n);
    for (i = 1; i <= m; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(&G, u, v);
    }
    for (i = 1; i <= G.n; i++)
        mark[i] = 0;
    // int j;
    // for (i = 1; i <= G.n; i++)
    // {
    //     for (j = 1; j <= G.n; j++)
    //         printf("%d ", G.A[i][j]);
    //     printf("\n");
    // }
    for (i = 1; i <= n; i++)
        if (mark[i] == 0)
            BFS(&G, i);
    return 0;
}