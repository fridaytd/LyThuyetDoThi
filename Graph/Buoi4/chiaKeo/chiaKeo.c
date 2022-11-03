#include <stdio.h>

#define MAX_Element 100
#define MAX_N 100
#define NO_EDGE 0;
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

int indegree(Graph *G, int u)
{
    int deg = 0;
    int i;
    for (i = 1; i <= G->n; i++)
        if (adjacent(G, i, u))
            deg += G->A[i][u];
    return deg;
}

int rank[MAX_N];
List L[MAX_N];

void ranking(Graph *G)
{
    int d[MAX_N];
    int i;
    int k = 1;
    make_null_list(&L[k]);
    for (i = 1; i <= G->n; i++)
    {
        d[i] = indegree(G, i);
        if (d[i] == 0)
            push_back(&L[k], i);
    }
    while (L[k].size > 0)
    {
        make_null_list(&L[k + 1]);
        for (i = 1; i <= L[k].size; i++)
        {
            int u = element_at(&L[k], i);
            rank[u] = k;
            List nei = neighbors(G, u);
            int j;
            for (j = 1; j <= nei.size; j++)
            {
                int v = element_at(&nei, j);
                d[v] -= G->A[u][v];
                if (d[v] == 0)
                    push_back(&L[k + 1], v);
            }
        }
        k++;
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
        add_edge(&G, v, u);
    }
    ranking(&G);
    int sum = 0;
    for (i = 1; i <= G.n; i++)
    {
        printf("%d\n", rank[i]);
        sum += rank[i];
    }
    printf("%d", sum);
    return 0;
}