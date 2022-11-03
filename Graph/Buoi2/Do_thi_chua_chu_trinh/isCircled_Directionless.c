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
int has_circle = 0;
int parent[MAX_N];
int start = 1, end = 1;

void DFS(Graph *G, int u, int p)
{
    if (color[u] != 0)
        return;
    color[u] = 1;
    parent[u] = p;
    List L = neighbors(G, u);
    int i;
    for (i = 1; i <= L.size; i++)
    {
        int v = element_at(&L, i);
        if (v == p)
            continue;
        if (color[v] == 0)
            DFS(G, v, u);
        else if (color[v] == 1)
        {
            has_circle = 1;
            start = u;
            end = v;
        }
    }
    color[u] = 2;
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
    for (i = 1; i <= G.n; i++)
        if (color[i] == 0)
            DFS(&G, i, 0);
    if (has_circle)
    {
        List L;
        make_null_list(&L);
        push_back(&L, end);
        push_back(&L, start);
        do
        {
            start = parent[start];
            push_back(&L, start);
        } while (start != end);
        for (i = L.size; i >= 1; i--)
            printf("%d ", element_at(&L, i));
    }
    else
        printf("-1");
    return 0;
}