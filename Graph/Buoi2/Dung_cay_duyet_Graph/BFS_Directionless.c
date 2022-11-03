#include <stdio.h>
#include "Graph_vo_huong.c"

#define MAX_Element 100

typedef struct
{
    int n, parent;
} ElementType;

typedef struct
{
    ElementType data[MAX_Element];
    int front, rear;
} Queue;

void make_null_queue(Queue *Q)
{
    Q->front = 0;
    Q->rear = -1;
}

int empty(Queue *Q)
{
    return Q->rear == -1;
}

void enqueue(Queue *Q, ElementType x)
{
    if ((Q->rear - Q->front + 1) % MAX_Element == 0 && !empty(Q))
        return;
    Q->rear = (Q->rear + 1) % MAX_Element;
    Q->data[Q->rear] = x;
}

ElementType front(Queue *Q)
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

int mark[MAX_N];
int parent[MAX_N];

void BFS(Graph *G, int u)
{
    Queue Q;
    make_null_queue(&Q);
    ElementType x;
    x.n = u;
    x.parent = 0;
    enqueue(&Q, x);
    while (!empty(&Q))
    {
        ElementType t = front(&Q);
        dequeue(&Q);
        if (mark[t.n] != 0)
            continue;
        mark[t.n] = 1;
        parent[t.n] = t.parent;
        List L = neighbors(G, t.n);
        int i;
        for (i = 1; i <= L.size; i++)
            if (mark[element_at(&L, i)] == 0)
            {
                ElementType t1;
                t1.n = element_at(&L, i);
                t1.parent = t.n;
                enqueue(&Q, t1);
            }
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
        mark[i] = 0;
    for (i = 1; i <= G.n; i++)
        if (mark[i] == 0)
            BFS(&G, i);
    for (i = 1; i <= G.n; i++)
        printf("%d %d\n", i, parent[i]);
    return 0;
}