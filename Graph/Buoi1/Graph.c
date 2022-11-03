#include <stdio.h>

#define MAX_N 20

typedef struct
{
    int A[MAX_N][MAX_N];
    int n; // so dinh
    int m; // so cung
} Graph;

void init_graph(Graph *G, int n)
{
    int i, j;
    G->n = n;
    G->m = 0;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            G->A[i][j] = 0;
}

void add_edge(Graph *G, int x, int y)
{
    G->m++;
    if (x == y)
        G->A[x][y]++;
    else
    {
        G->A[x][y]++;
        G->A[y][x]++;
    }
}

int adjacent(Graph *G, int x, int y)
{
    return G->A[x][y] != 0;
}

int degree(Graph *G, int x)
{
    int deg = 0;
    int i;
    for (i = 1; i <= G->n; i++)
        deg += (i == x) ? 2 * G->A[i][x] : G->A[i][x];
    return deg;
}

int main()
{
    Graph G;
    int i, j;
    int n, m;
    freopen("dothi.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    init_graph(&G, n);
    int u, v;
    for (i = 1; i <= m; i++)
    {
        scanf("%d%d", &u, &v);
        add_edge(&G, u, v);
    }
    for (i = 1; i <= G.n; i++)
    {
        for (j = 1; j <= G.n; j++)
            printf("%d ", G.A[i][j]);
        printf("\n");
    }
    for (i = 1; i <= G.n; i++)
        printf("deg(%d) = %d\n", i, degree(&G, i));
    return 0;
}