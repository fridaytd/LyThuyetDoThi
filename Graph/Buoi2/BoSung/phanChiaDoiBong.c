#include <stdio.h>

#define MAX_Element 100
#define MAX_N 100
#define NO_EDGE 0

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

void add_edge(Graph *G, int u, int v)
{
    G->A[u][v]++;
    G->A[v][u]++;
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

int color[MAX_N];
int conflict = 0;

void colorize(Graph *G, int u, int co)
{
    if (color[u] != 0)
        return;
    color[u] = co;
    List L = neighbors(G, u);
    int i;
    for (i = 1; i <= L.size; i++)
    {
        int v = element_at(&L, i);
        if (color[v] == co)
            conflict = 1;
        else if (color[v] == 0)
            colorize(G, v, 3 - co);
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
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(&G, u, v);
    }
    for (i = 1; i <= G.n; i++)
        color[i] = 0;
    for (i = 1; i <= G.n; i++)
        if (color[i] == 0)
            colorize(&G, i, 1);
    if (conflict)
        printf("IMPOSSIBLE");
    else
    {
        for (i = 1; i <= G.n; i++)
            if (color[i] == 1)
                printf("%d ", i);
        printf("\n");
        for (i = 1; i <= G.n; i++)
            if (color[i] == 2)
                printf("%d ", i);
    }
    return 0;
}