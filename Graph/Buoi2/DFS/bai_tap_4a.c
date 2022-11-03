#include <stdio.h>
#include "Stack.c"
#include "Graph_vo_huong.c"

int mark[MAX_N];

void DFS(Graph *G, int x)
{
    Stack S;
    make_null_stack(&S);
    push(&S, x);
    while (!empty(&S))
    {
        int n = top(&S);
        pop(&S);
        if (mark[n] != 0)
            continue;
        printf("%d\n", n);
        mark[n] = 1;
        List L = neighbors(G, n);
        int i;
        for (i = 1; i <= L.size; i++)
            if (mark[element_at(&L, i)] == 0)
                push(&S, element_at(&L, i));
    }
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
            DFS(&G, i);
    return 0;
}