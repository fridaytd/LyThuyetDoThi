#include <stdio.h>

#define MAX_M 100

typedef struct
{
    int u, v;
} Edge;

typedef struct
{
    int n, m;
    Edge edges[MAX_M];
} Graph;

void init_graph(Graph *G, int n)
{
    G->n = n;
    G->m = 0;
}

void add_edge(Graph *G, int u, int v)
{
    G->edges[G->m].u = u;
    G->edges[G->m].v = v;
    G->m++;
}

int degree(Graph *G, int x)
{
    int i;
    int deg = 0;
    for (i = 0; i < G->m; i++)
    {
        if (G->edges[i].u == x)
            deg++;
        if (G->edges[i].v == x)
            deg++;
    }
    return deg;
}

int adjacent(Graph *G, int u, int v)
{
    int i;
    for (i = 0; i < G->m; i++)
    {
        if ((G->edges[i].u == u && G->edges[i].v == v))
            return 1;
    }
    return 0;
}

void neighbors(Graph *G, int x)
{
    int i;
    for (i = 1; i <= G->n; i++)
        if (adjacent(G, x, i))
            printf("%d ", i);
}

int main()
{
    Graph G;
    int n, m;
    scanf("%d%d", &n, &m);
    init_graph(&G, n);
    int i;
    for (i = 0; i < m; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(&G, u, v);
    }
    for (i = 1; i <= n; i++)
    {
        printf("neighbours(%d) = ", i);
        neighbors(&G, i);
        printf("\n");
    }
    return 0;
}