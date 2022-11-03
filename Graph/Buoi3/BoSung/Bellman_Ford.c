#include <stdio.h>

#define MAX_N 100
#define MAX_Element 100
#define NO_EDGE -1

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

int p[MAX_N];
int pi[MAX_N];
int mark[MAX_N];

void Bellman_Ford(Graph *G, int s)
{
    int i;
    for (i = 1; i <= G->n; i++)
    {
        pi[i] = oo;
        p[i] = -1;
        mark[i] = 0;
    }
    pi[s] = 0;
    p[s] = -1;
    int it;
    for (it = 1; it < G->n; it++)
    {
        int j, min_pi = oo;
        int u;
        for (j = 1; j <= G->n; j++)
            if (mark[j] == 0 && pi[j] < min_pi)
            {
                min_pi = pi[j];
                u = j;
            }
        mark[u] = 1;
        List L = neighbors(G, u);
        for (j = 1; j <= L.size; j++)
        {
            int v = element_at(&L, j);
            if (mark[v] == 0 && pi[u] + G->A[u][v] < pi[v])
            {
                pi[v] = pi[u] + G->A[u][v];
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
    int i;
    for (i = 1; i <= m; i++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add_edge(&G, u, v, w);
    }
    Bellman_Ford(&G, 1);
    for (i = 1; i <= G.n; i++)
        printf("pi[%d] = %d, p[%d] = %d\n", i, pi[i], i, p[i]);
    return 0;
}