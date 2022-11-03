#include <stdio.h>
#include <math.h>

#define MAX_N 100

typedef struct
{
    int u, v;
    int w;
} Edge;

typedef struct
{
    int n, m;
    Edge edges[MAX_N];
} Graph;

void init_graph(Graph *G, int n)
{
    G->n = n;
    G->m = 0;
}

void add_edge(Graph *G, int u, int v, int w)
{
    G->edges[G->m].u = u;
    G->edges[G->m].v = v;
    G->edges[G->m].w = w;
    G->m++;
}

int adjacent(Graph *G, int u, int v)
{
    int i;
    for (i = 0; i < G->m; i++)
        if (G->edges[i].u == u && G->edges[i].v == v)
            return 1;
    return 0;
}

int pi[MAX_N];
int p[MAX_N];

#define oo 999999

void BellmanFord(Graph *G, int s)
{
    int i;
    for (i = 1; i <= G->n; i++)
        pi[i] = oo;
    pi[s] = 0;
    p[s] = -1;
    for (i = 1; i < G->n; i++)
    {
        int j;
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

int main()
{
    Graph G;
    int n, m;
    scanf("%d%d", &n, &m);
    init_graph(&G, n);
    int b[MAX_N];
    int i;
    for (i = 1; i <= n; i++)
        scanf("%d", &b[i]);
    for (i = 1; i <= m; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        int w = pow(v - u, 3);
        add_edge(&G, u, v, w);
    }
    int s, t;
    scanf("%d%d", &s, &t);
    BellmanFord(&G, s);
    if (pi[t] != oo)
        printf("%d", pi[t]);
    else
        printf("?");
    return 0;
}