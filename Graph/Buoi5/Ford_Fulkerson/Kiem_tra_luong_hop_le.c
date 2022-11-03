#include <stdio.h>

#define MAXN 100
#define NO_EDGE 0

typedef struct
{
    int n, m;
    int C[MAXN][MAXN];
    int F[MAXN][MAXN];
} Graph;

void init_graph(Graph *G, int n)
{
    G->n = n;
    G->m = 0;
    int i, j;
    for (i = 1; i <= G->n; i++)
        for (j = 1; j <= G->n; j++)
            G->C[i][j] = NO_EDGE;
}

void add_edge(Graph *G, int u, int v, int w)
{
    G->C[u][v] = w;
    G->m++;
}

void sum_in_out(Graph *G, int s, int *in, int *out)
{
    *in = 0;
    *out = 0;
    int i;
    for (i = 1; i <= G->n; i++)
    {
        if (G->C[s][i] != NO_EDGE)
            (*out) += G->F[s][i];
        if (G->C[i][s] != NO_EDGE)
            (*in) += G->F[i][s];
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
        int u, v, c, f;
        scanf("%d%d%d%d", &u, &v, &c, &f);
        add_edge(&G, u, v, c);
        G.F[u][v] = f;
    }
    int hople = 1;
    int in[MAXN];
    int out[MAXN];
    for (i = 1; i <= G.n; i++)
    {
        sum_in_out(&G, i, &in[i], &out[i]);
        if (in[i] != out[i] && i != 1 && i != n)
        {
            hople = 0;
            break;
        }
        int j;
        for (j = 1; j <= G.n; j++)
            if (G.C[i][j] != NO_EDGE)
                if (G.F[i][j] < 0 || G.F[i][j] > G.C[i][j])
                {
                    hople = 0;
                    break;
                }
    }
    if (out[1] != in[n])
        hople = 0;
    printf("%s", (hople == 0) ? "NO" : "YES");
    return 0;
}