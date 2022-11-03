#include <stdio.h>

#define MAX_Element 100
#define MAX_N 100
#define NO_EDGE 0
#define oo 99999999

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

List parent(Graph *G, int u)
{
    List L;
    make_null_list(&L);
    int i;
    for (i = 1; i <= G->n; i++)
        if (adjacent(G, i, u))
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

int outdegree(Graph *G, int u)
{
    int deg = 0;
    int i;
    for (i = 1; i <= G->n; i++)
        if (adjacent(G, u, i))
            deg++;
    return deg;
}

List topo_sort(Graph *G)
{
    int d[MAX_N];
    int i;
    for (i = 1; i <= G->n; i++)
        d[i] = indegree(G, i);
    List L;
    make_null_list(&L);
    Queue Q;
    make_null_queue(&Q);
    for (i = 1; i <= G->n; i++)
        if (d[i] == 0)
            enqueue(&Q, i);
    while (!empty_queue(&Q))
    {
        int u = front(&Q);
        dequeue(&Q);
        push_back(&L, u);
        List nei = neighbors(G, u);
        int j;
        for (j = 1; j <= nei.size; j++)
        {
            int v = element_at(&nei, j);
            d[v]--;
            if (d[v] == 0)
                enqueue(&Q, v);
        }
    }
    return L;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int min(int a, int b)
{
    return a < b ? a : b;
}

int main()
{
    Graph G;
    int d[MAX_N];
    int n;
    scanf("%d", &n);
    init_graph(&G, n + 2);
    int i;
    for (i = 1; i <= n; i++)
        scanf("%d", &d[i]);
    int m;
    scanf("%d", &m);
    for (i = 1; i <= m; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(&G, u, v);
    }
    int alpha = n + 1;
    d[alpha] = 0;
    int beta = n + 2;
    for (i = 1; i <= n; i++)
    {
        if (indegree(&G, i) == 0)
            add_edge(&G, alpha, i);
        if (outdegree(&G, i) == 0)
            add_edge(&G, i, beta);
    }
    int t[MAX_N];
    List topo = topo_sort(&G);
    for (i = 2; i <= topo.size; i++)
    {
        int u = element_at(&topo, i);
        t[u] = -oo;
        List p = parent(&G, u);
        int j;
        for (j = 1; j <= p.size; j++)
        {
            int v = element_at(&p, j);
            t[u] = max(t[u], t[v] + d[v]);
        }
    }
    printf("%d", t[beta]);
}