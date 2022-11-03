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
    int data[MAX_Element];
    int front, rear;
} Queue;

void make_null_queue(Queue *Q)
{
    Q->front = 0;
    Q->rear = -1;
}

int empty_queue(Queue *Q)
{
    return Q->rear == -1;
}

void enqueue(Queue *Q, int x)
{
    Q->rear = (Q->rear + 1) % MAX_Element;
    Q->data[Q->rear] = x;
}

int front(Queue *Q)
{
    return Q->data[Q->front];
}

void dequeue(Queue *Q)
{
    if (Q->front == Q->rear)
        make_null_queue(Q);
    else
        Q->front = (Q->front + 1) % MAX_Element;
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
            deg++;
    return deg;
}

int mark[MAX_N];

void dfs(Graph *G, int u, List *L)
{
    mark[u] = 1;
    List nei = neighbors(G, u);
    int i;
    for (i = 1; i <= nei.size; i++)
    {
        int v = element_at(&nei, i);
        if (mark[v] == 0)
            dfs(G, v, L);
    }
    push_back(L, u);
}

List topo_sort(Graph *G)
{
    List L1;
    make_null_list(&L1);
    int i;
    for (i = 1; i <= G->n; i++)
        mark[i] = 0;
    for (i = 1; i <= G->n; i++)
        if (mark[i] == 0)
            dfs(G, i, &L1);
    List L2;
    for (i = L1.size; i >= 1; i--)
        push_back(&L2, element_at(&L1, i));
    return L2;
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
    List L = topo_sort(&G);
    for (i = 1; i <= L.size; i++)
        printf("%d ", element_at(&L, i));
    return 0;
}