#include <stdio.h>

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
    if (L->size == MAX_Element)
        return;
    L->data[L->size] = x;
    L->size++;
}

int element_at(List *L, int x)
{
    return L->data[x - 1];
}

#define MAX_N 100

typedef struct
{
    int A[MAX_N][MAX_N];
    int n, m;
} Graph;

void init_graph(Graph *G, int n)
{
    G->n = n;
    G->m = 0;
    int i, j;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            G->A[i][j] = 0;
}

void add_edge(Graph *G, int u, int v)
{
    G->A[u][v]++;
    G->A[v][u]++;
    G->m++;
}

int adjacent(Graph *G, int u, int v)
{
    return G->A[u][v] != 0;
}

List neighbors(Graph *G, int x)
{
    List L;
    make_null_list(&L);
    int i;
    for (i = 1; i <= G->n; i++)
        if (adjacent(G, x, i))
            push_back(&L, i);
    return L;
}

int color[MAX_N];
int PhanDoi = 1;

void colorize(Graph *G, int u, int c)
{
    color[u] = c;
    List L = neighbors(G, u);
    int i;
    for (i = 1; i <= L.size; i++)
    {
        int v = element_at(&L, i);
        if (color[v] == 0)
            colorize(G, v, 3 - c);
        else if (color[v] == color[u])
            PhanDoi = 0;
    }
}

int main()
{
    Graph G;
    freopen("Graph.txt", "r", stdin);
    int n, m;
    scanf("%d%d", &n, &m);
    init_graph(&G, n);
    int i;
    for (i = 1; i <= m; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(&G, u, v);
    }
    for (i = 1; i <= G.n; i++)
        color[i] = 0;
    // for (i = 1; i <= G.n; i++)
    //     if (color[i] == 0)
    colorize(&G, 1, 1);
    if (PhanDoi)
    {
        for (i = 1; i <= G.n; i++)
            if (color[i] == 1)
                printf("%d ", i);
        printf("\n");
        for (i = 1; i <= G.n; i++)
            if (color[i] == 2)
                printf("%d ", i);
    }
    else
        printf("IMPOSSIBLE");
    return 0;
}