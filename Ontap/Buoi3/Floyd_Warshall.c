#include <stdio.h>

#define MAX_N 100
#define MAX_M 500
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
    G->m++;
}

#define oo 9999999

int pi[MAX_N][MAX_N];
int next[MAX_N][MAX_N];

void FloydWarshall(Graph *G)
{
    int i, j;
    for (i = 1; i <= G->n; i++)
        for (j = 1; j <= G->n; j++)
            if (G->A[i][j] != NO_EDGE)
            {
                pi[i][j] = G->A[i][j];
                next[i][j] = j;
            }
            else
            {
                pi[i][j] = oo;
                next[i][j] = -1;
            }
    for (i = 1; i <= G->n; i++)
        pi[i][i] = 0;
    int k;
    for (k = 1; k <= G->n; k++)
        for (i = 1; i <= G->n; i++)
            for (j = 1; j <= G->n; j++)
            {
                if (pi[i][k] == oo || pi[k][j] == oo)
                    continue;
                if (pi[i][k] + pi[k][j] < pi[i][j])
                {
                    pi[i][j] = pi[i][k] + pi[k][j];
                    next[i][j] = next[i][k];
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
    FloydWarshall(&G);
    int j;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            if (pi[i][j] != oo)
                printf("%d -> %d: %d\n", i, j, pi[i][j]);
            else
                printf("%d -> %d: oo\n", i, j);
    return 0;
}