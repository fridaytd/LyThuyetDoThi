#include <stdio.h>

#define MAX_Element 100
#define MAX_N 100
#define NO_EDGE -99

typedef struct
{
    int data[MAX_Element];
    int size;
} List;

void make_null_list(List *L)
{
    L->size = 0;
}

void push_back(List *L, int x)
{
    L->data[L->size] = x;
    L->size++;
}

int element_at(List *L, int i)
{
    return L->data[i - 1];
}

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
    for (i = 1; i <= G->n; i++)
        for (j = 1; j <= G->n; j++)
            G->A[i][j] = NO_EDGE;
}

void add_edge(Graph *G, int u, int v, int w)
{
    G->A[u][v] = w;
    G->m++;
}

int adjacent(Graph *G, int u, int v)
{
    return G->A[u][v] != NO_EDGE;
}

List neighbors(Graph *G, int u)
{
    List L;
    make_null_list(&L);
    int i;
    for (i = 1; i <= G->n; i++)
        if (adjacent(G, u, i))
            push_back(&L, i);
    return L;
}

#define oo 99999999

int pi[MAX_N][MAX_N];
int next[MAX_N][MAX_N];

void FloydWarshall(Graph *G)
{
    int u, v;
    for (u = 1; u <= G->n; u++)
        for (v = 1; v <= G->n; v++)
        {
            if (u == v)
            {
                pi[u][v] = 0;
                next[u][v] = -1;
            }
            else if (adjacent(G, u, v))
            {
                pi[u][v] = G->A[u][v];
                next[u][v] = v;
            }
            else
            {
                pi[u][v] = oo;
                // next[u][v] = -1;
            }
        }
    int k;
    for (k = 1; k <= G->n; k++)
    {
        for (u = 1; u <= G->n; u++)
            for (v = 1; v <= G->n; v++)
            {
                // if (pi[u][k] == oo)
                //     continue;
                // if (k == u || k == v || u == v)
                //     continue;
                if (pi[u][k] + pi[k][v] < pi[u][v])
                {
                    pi[u][v] = pi[u][k] + pi[k][v];
                    next[u][v] = next[u][k];
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
    int i;
    for (i = 1; i <= m; i++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add_edge(&G, u, v, w);
    }
    FloydWarshall(&G);
    int u, v;
    for (u = 1; u <= G.n; u++)
        for (v = 1; v <= G.n; v++)
        {
            if (pi[u][v] != oo)
                printf("%d -> %d: %d\n", u, v, pi[u][v]);
            else
                printf("%d -> %d: NO PATH\n", u, v);
        }
    return 0;
}