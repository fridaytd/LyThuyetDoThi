#include "List.c"
#define MAX_N 100

typedef struct
{
    int A[MAX_N][MAX_N];
    int n, m;
} Graph;

void init_graph(Graph *G, int n)
{
    G->n = n;
    G->m = 0;
    int i, j;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            G->A[i][j] = 0;
}

void add_edge(Graph *G, int u, int v)
{
    G->A[u][v]++;
    G->A[v][u]++;
    G->m++;
}

int adjacent(Graph *G, int u, int v)
{
    return G->A[u][v] != 0;
}

List neighbors(Graph *G, int x)
{
    List L;
    make_null_list(&L);
    int i;
    for (i = 1; i <= G->n; i++)
        if (adjacent(G, x, i))
            push_back(&L, i);
    return L;
}
