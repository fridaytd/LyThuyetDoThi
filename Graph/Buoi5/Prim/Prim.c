#include <stdio.h>

#define MAX_N 100
#define MAX_Element 100
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
    G->A[v][u] = w;
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

int pi[MAX_N];
int p[MAX_N];
int mark[MAX_N];
#define oo 99999999

int prim(Graph *G, Graph *T, int s)
{
    init_graph(T, G->n);
    int i;
    for (i = 1; i <= G->n; i++)
    {
        mark[i] = 0;
        pi[i] = oo;
        p[i] = -1;
    }
    pi[s] = 0;
    int sum_w = 0;
    int it;
    for (it = 1; it <= G->n; it++)
    {
        int u, min_pi = oo;
        int j;
        for (j = 1; j <= G->n; j++)
            if (mark[j] == 0 && pi[j] < min_pi)
            {
                u = j;
                min_pi = pi[u];
            }
        mark[u] = 1;
        if (p[u] != -1)
        {
            int w = G->A[p[u]][u];
            add_edge(T, p[u], u, w);
            sum_w += w;
        }
        List L = neighbors(G, u);
        for (j = 1; j <= L.size; j++)
        {
            int v = element_at(&L, j);
            if (mark[v] == 0 && G->A[u][v] < pi[v])
            {
                pi[v] = G->A[u][v];
                p[v] = u;
            }
        }
    }

    // for (i = 1; i <= G->n; i++)
    // {
    //     if (p[i] != -1)
    //     {
    //         int w = G->A[p[i]][i];
    //         add_edge(T, p[i], i, w);
    //         sum_w += w;
    //     }
    // }

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
    printf("%d\n", prim(&G, &T, 1));
    int j;
    for (i = 1; i <= T.n; i++)
    {
        for (j = i + 1; j <= T.n; j++)
            if (T.A[i][j] != NO_EDGE)
                printf("%d %d %d\n", i, j, T.A[i][j]);
    }
    return 0;
}