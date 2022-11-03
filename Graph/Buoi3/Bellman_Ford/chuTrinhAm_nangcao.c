#include <stdio.h>

#define MAX_Element 100
#define MAX_N 100

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

#define oo 99999999
int pi[MAX_N];
int p[MAX_N];

int uu;

int isChuTrinhAm(Graph *G, int s)
{
    int i;
    for (i = 1; i <= G->n; i++)
        pi[i] = oo;

    pi[s] = 0;
    p[s] = -1;
    int chutrinham = 0;
    int j;
    for (i = 1; i < G->n; i++)
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
    for (j = 0; j < G->m; j++)
    {
        int u = G->edges[j].u;
        int v = G->edges[j].v;
        int w = G->edges[j].w;
        if (pi[u] == oo)
            continue;
        if (pi[u] + w < pi[v])
        {
            uu = v;
            chutrinham = 1;
        }
    }
    return chutrinham;
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
    int s;
    scanf("%d", &s);
    if (isChuTrinhAm(&G, s))
    {
        int cur = uu;
        while (1)
        {
            printf("%d ", cur);
            cur = p[cur];
            if (cur == uu)
                break;
        }
    }
    else
    {
        printf("NO");
    }
    return 0;
}