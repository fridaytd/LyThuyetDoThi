#include <stdio.h>

#define MAXN 500
#define NO_EDGE 0
#define oo 9999999

typedef struct
{
    int data[MAXN];
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
    int elements[MAXN];
    int front, rear;
} Queue;

void make_null_queue(Queue *Q)
{
    Q->front = 0;
    Q->rear = -1;
}

void enqueue(Queue *Q, int x)
{
    Q->rear++;
    Q->elements[Q->rear] = x;
}

void dequeue(Queue *Q)
{
    if (Q->front == Q->rear)
        make_null_queue(Q);
    else
        Q->front++;
}

int empty_queue(Queue *Q)
{
    return Q->rear == -1;
}

int front(Queue *Q)
{
    return Q->elements[Q->front];
}

typedef struct
{
    int A[MAXN][MAXN];
    int n, m;
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

List topo_sort(Graph *G)
{
    List L;
    make_null_list(&L);
    int d[MAXN];
    int i, j;
    for (i = 1; i <= G->n; i++)
    {
        d[i] = 0;
        for (j = 1; j <= G->n; j++)
            if (G->A[j][i] != NO_EDGE)
                d[i]++;
    }
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
        int v;
        for (v = 1; v <= G->n; v++)
            if (G->A[u][v] != NO_EDGE)
            {
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
    return (a < b) ? a : b;
}

int main()
{
    Graph G;
    int n;
    scanf("%d", &n);
    init_graph(&G, n + 2);
    int alpha = n + 1, beta = n + 2;
    int d[MAXN];
    d[alpha] = 0;
    int u;
    for (u = 1; u <= n; u++)
    {
        scanf("%d", &d[u]);
        while (1)
        {
            int v;
            scanf("%d", &v);
            if (v == 0)
                break;
            add_edge(&G, v, u);
        }
    }
    int deg_neg[MAXN];

    for (u = 1; u <= n; u++)
    {
        deg_neg[u] = 0;
        int v;
        for (v = 1; v <= n; v++)
            if (G.A[v][u] != NO_EDGE)
                deg_neg[u]++;
        if (deg_neg[u] == 0)
            add_edge(&G, alpha, u);
    }
    int deg_pos[MAXN];
    for (u = 1; u <= n; u++)
    {
        deg_pos[u] = 0;
        int v;
        for (v = 1; v <= n; v++)
            if (G.A[u][v] != NO_EDGE)
                deg_pos[u]++;
        if (deg_pos[u] == 0)
            add_edge(&G, u, beta);
    }

    int i;
    List L = topo_sort(&G);

    // for (i = 1; i <= L.size; i++)
    //     printf("%d ", element_at(&L, i));

    int t[MAXN], T[MAXN];
    t[alpha] = 0;
    for (i = 2; i <= L.size; i++)
    {
        int u = element_at(&L, i);
        t[u] = -oo;
        int v;
        for (v = 1; v <= G.n; v++)
            if (G.A[v][u] != NO_EDGE)
                t[u] = max(t[u], t[v] + d[v]);
    }
    T[beta] = t[beta];
    for (i = L.size - 1; i >= 1; i--)
    {
        int u = element_at(&L, i);
        T[u] = oo;
        int v;
        for (v = 1; v <= G.n; v++)
            if (G.A[u][v] != NO_EDGE)
                T[u] = min(T[u], T[v] - d[u]);
    }
    printf("%d\n", T[beta]);
    for (u = 1; u <= n + 2; u++)
        printf("%d-%d\n", t[u], T[u]);
    return 0;
}