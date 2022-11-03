#include <stdio.h>

#define MAXN 500
#define NO_EDGE -1

typedef struct
{
    int n, m;
    int A[MAXN][MAXN];
} Graph;

void init_graph(Graph *G, int n)
{
    G->n = n;
    G->m = 0;
    int i, j;
    for (i = 1; i <= G->n; i++)
        for (j = 1; j <= G->n; j++)
            G->A[i][j] = NO_EDGE;
}

void add_edge(Graph *G, int u, int v, int w)
{
    G->A[u][v] = w;
    G->A[v][u] = w;
    G->m++;
}

int p[MAXN];
int pi[MAXN];
int mark[MAXN];

#define oo 9999999

int Prim(Graph *G, Graph *T, int s)
{
    int u;
    for (u = 1; u <= G->n; u++)
    {
        p[u] = -1;
        mark[u] = 0;
        pi[u] = oo;
    }

    pi[s] = 0;
    int it;
    for (it = 1; it < G->n; it++)
    {
        int u, j, min_pi = oo;
        for (j = 1; j <= G->n; j++)
            if (mark[j] == 0 && pi[j] < min_pi)
            {
                u = j;
                min_pi = pi[j];
            }

        mark[u] = 1;

        int v;
        for (v = 1; v <= G->n; v++)
            if (mark[v] == 0 && G->A[u][v] != NO_EDGE && G->A[u][v] < pi[v])
            {
                pi[v] = G->A[u][v];
                p[v] = u;
            }
    }
    int sum_w = 0;
    init_graph(T, G->n);
    for (u = 1; u <= G->n; u++)
        if (p[u] != -1)
        {
            add_edge(T, p[u], u, G->A[p[u]][u]);
            sum_w += G->A[p[u]][u];
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
    int sum_w = Prim(&G, &T, 1);
    printf("%d\n", sum_w);
    int j;
    for (i = 1; i <= T.n; i++)
        for (j = i; j <= T.n; j++)
            if (T.A[i][j] != NO_EDGE)
                printf("%d %d %d \n", i, j, T.A[i][j]);
    return 0;
}