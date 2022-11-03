#include <stdio.h>

#define MAX_N 100
#define NO_EDGE -99
typedef struct
{
    int n, m;
    int A[MAX_N][MAX_N];
} Graph;

void init_graph(Graph *G, int n)
{
    G->n = n;
    G->m = 0;
    int i, j;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            G->A[i][j] = NO_EDGE;
}

void add_edge(Graph *G, int u, int v, int w)
{
    G->A[u][v] = w;
    G->A[v][u] = w;
    G->m++;
}

#define oo 9999999

int pi[MAX_N];
int p[MAX_N];
int mark[MAX_N];

void MooreDijkstra(Graph *G, int s)
{
    int i;
    for (i = 1; i <= G->n; i++)
    {
        mark[i] = 0;
        p[i] = -1;
        pi[i] = oo;
    }

    pi[s] = 0;

    int it;
    for (it = 1; it < G->n; it++)
    {
        int j, u, min_pi = oo;
        for (j = 1; j <= G->n; j++)
            if (mark[j] == 0 && pi[j] < min_pi)
            {
                u = j;
                min_pi = pi[j];
            }
        mark[u] = 1;
        int v;
        for (v = 1; v <= G->n; v++)
            if (G->A[u][v] != NO_EDGE && mark[v] == 0)
                if (pi[u] + G->A[u][v] < pi[v])
                {
                    pi[v] = pi[u] + G->A[u][v];
                    p[v] = u;
                }
    }
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
    MooreDijkstra(&G, 1);
    printf("%d", (pi[n] == oo) ? -1 : pi[n]);
    return 0;
}