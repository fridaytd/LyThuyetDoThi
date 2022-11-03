#include <stdio.h>

#define MAX_N 100
#define MAX_Element 100

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
        if ((G->edges[i].u == u && G->edges[i].v == v) || (G->edges[i].u == v && G->edges[i].v == u))
            return 1;
    return 0;
}

List neighbors(Graph *G, int u)
{
    int i;
    List L;
    make_null_list(&L);
    for (i = 1; i <= G->n; i++)
        if (adjacent(G, u, i))
            push_back(&L, i);
    return L;
}

int parent[MAX_N];

int findRoot(int u)
{
    while (parent[u] != u)
        u = parent[u];
    return u;
}

int kruskal(Graph *G, Graph *T)
{
    // Xep thu tu cac cung
    int i, j;
    for (i = 0; i < G->m; i++)
        for (j = i + 1; j < G->m; j++)
            if (G->edges[i].w > G->edges[j].w)
            {
                Edge temp = G->edges[i];
                G->edges[i] = G->edges[j];
                G->edges[j] = temp;
            }
    // Khoi tao
    init_graph(T, G->n);
    for (i = 1; i < G->n; i++)
        parent[i] = i;
    int sum_w = 0;

    //

    for (i = 0; i < G->m; i++)
    {
        int u = G->edges[i].u;
        int v = G->edges[i].v;
        int w = G->edges[i].w;
        int root_u = findRoot(u);
        int root_v = findRoot(v);
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
    for (i = 1; i <= m; i++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add_edge(&G, u, v, w);
    }
    Graph T;
    printf("%d\n", kruskal(&G, &T));
    int j;
    for (i = 0; i < T.m; i++)
    {
        if (T.edges[i].u > T.edges[i].v)
        {
            int temp = T.edges[i].u;
            T.edges[i].u = T.edges[i].v;
            T.edges[i].v = temp;
        }
        for (j = i + 1; j < T.m; j++)
            if (T.edges[i].w > T.edges[j].w)
            {
                Edge temp = T.edges[i];
                T.edges[i] = T.edges[j];
                T.edges[j] = temp;
            }
    }
    for (i = 0; i < T.m; i++)
        printf("%d %d %d\n", T.edges[i].u, T.edges[i].v, T.edges[i].w);
    return 0;
}