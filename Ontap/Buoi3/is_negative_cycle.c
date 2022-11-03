#include <stdio.h>

#define MAX_N 100
#define MAX_M 100

typedef struct
{
    int u, v;
    int w;
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

void add_edge(Graph *G, int u, int v, int w)
{
    int m = G->m;
    G->edges[m].u = u;
    G->edges[m].v = v;
    G->edges[m].w = w;
    G->m++;
}

#define oo 9999999

int p[MAX_N];
int pi[MAX_N];

void BellmanFord(Graph *G, int s)
{
    int i, j;
    for (i = 0; i < G->m; i++)
        for (j = i + 1; j < G->m; j++)
            if (G->edges[i].w > G->edges[j].w)
            {
                Edge temp = G->edges[i];
                G->edges[i] = G->edges[j];
                G->edges[j] = temp;
            }
    for (i = 1; i <= G->n; i++)
    {
        pi[i] = oo;
        p[i] = -1;
    }
    for (i = 1; i < G->n; i++)
    {
        for (j = 0; j < G->m; j++)
        {
            int u = G->edges[j].u;
            int v = G->edges[j].v;
            int w = G->edges[j].w;
            if (pi[u] == oo)
                continue;
            if (pi[u] + w < pi[v])
            {
                pi[v] = pi[u] + w;
                p[v] = u;
            }
        }
    }
}

int has_negative_cycle(Graph *G)
{
    BellmanFord(G, 1);
    int j;
    for (j = 0; j < G->m; j++)
    {
        int u = G->edges[j].u;
        int v = G->edges[j].v;
        int w = G->edges[j].w;
        if (pi[u] + w < pi[v])
            return 1;
    }
    return 0;
}

int main()
{
    Graph G;
    int n, m;
    scanf("%d%d", &n, &m);
    init_graph(&G, n);
    int i;
    for (i = 1; i <= m; i++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add_edge(&G, u, v, w);
    }
    if (has_negative_cycle(&G))
        printf("negative cycle");
    else
        printf("ok");
    return 0;
}