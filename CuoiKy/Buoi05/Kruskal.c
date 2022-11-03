#include <stdio.h>

#define MAXN 500
#define MAXM 500

typedef struct
{
    int u, v;
    int w;
} Edge;

typedef struct
{
    int n, m;
    Edge edges[MAXM];
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

int parent[MAXN];

int find_root(int u)
{
    while (u != parent[u])
        u = parent[u];
    return u;
}

int Kruskal(Graph *G, Graph *T)
{
    init_graph(T, G->n);
    int u;
    int sum_w = 0;
    for (u = 1; u <= G->n; u++)
        parent[u] = u;
    int j, i;
    for (i = 0; i < G->m; i++)
        for (j = i + 1; j < G->m; j++)
            if (G->edges[i].w > G->edges[j].w)
            {
                Edge temp = G->edges[i];
                G->edges[i] = G->edges[j];
                G->edges[j] = temp;
            }
    for (i = 0; i < G->m; i++)
    {
        int u = G->edges[i].u;
        int v = G->edges[i].v;
        int w = G->edges[i].w;
        int root_u = find_root(u);
        int root_v = find_root(v);
        if (root_u != root_v)
        {
            add_edge(T, u, v, w);
            parent[root_v] = root_u;
            sum_w += w;
        }
    }
    return sum_w;
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
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add_edge(&G, u, v, w);
    }
    Graph T;
    int sum_w = Kruskal(&G, &T);
    printf("%d\n", sum_w);
    for (i = 0; i < T.m; i++)
    {
        if (T.edges[i].u > T.edges[i].v)
            printf("%d %d %d\n", T.edges[i].v, T.edges[i].u, T.edges[i].w);
        else
            printf("%d %d %d\n", T.edges[i].u, T.edges[i].v, T.edges[i].w);
    }
    return 0;
}