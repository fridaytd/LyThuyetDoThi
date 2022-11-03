#include <stdio.h>

#define MAX_N 100
#define MAX_Element 100
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

void dequeue(Queue *Q)
{
    if (Q->front == Q->rear)
        make_null_queue(Q);
    else
        Q->front = (Q->front + 1) % MAX_Element;
}

int front(Queue *Q)
{
    return Q->data[Q->front];
}

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

int mark[MAX_N];
int parent[MAX_N];

void BFS(Graph *G, int u)
{
    Queue Q;
    make_null_queue(&Q);
    enqueue(&Q, u);
    parent[u] = -1;
    while (!empty_queue(&Q))
    {
        int t = front(&Q);
        dequeue(&Q);
        if (mark[t] != 0)
            continue;
        // printf("%d\n", t);
        mark[t] = 1;
        List L = neighbors(G, t);
        int i;
        for (i = 1; i <= L.size; i++)
        {
            int v = element_at(&L, i);
            if (mark[v] == 0)
            {
                enqueue(&Q, v);
                if (parent[v] == -1)
                    parent[v] = t;
            }
        }
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
    {
        mark[i] = 0;
        parent[i] = -1;
    }
    for (i = 1; i <= G.n; i++)
        if (mark[i] == 0)
            BFS(&G, i);
    for (i = 1; i <= G.n; i++)
        printf("%d %d\n", i, parent[i]);
    return 0;
}