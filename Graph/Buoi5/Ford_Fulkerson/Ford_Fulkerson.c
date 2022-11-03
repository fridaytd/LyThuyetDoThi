#include <stdio.h>

#define MAXN 100
#define NO_EDGE 0
#define oo 9999999

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

int empty_queue(Queue *Q)
{
    return Q->rear == -1;
}

int front(Queue *Q)
{
    return Q->elements[Q->front];
}

void enqueue(Queue *Q, int i)
{
    Q->rear++;
    Q->elements[Q->rear] = i;
}

void dequeue(Queue *Q)
{
    if (Q->front == Q->rear)
        make_null_queue(Q);
    else
        Q->front++;
}

typedef struct
{
    int n, m;
    int C[MAXN][MAXN];
    int F[MAXN][MAXN];
} Graph;

void init_graph(Graph *G, int n)
{
    G->n = n;
    G->m = 0;
    int i, j;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
        {
            G->C[i][j] = 0;
            G->F[i][j] = 0;
        }
}

void add_edge(Graph *G, int u, int v, int w)
{
    G->C[u][v] = w;
    G->m++;
}

void init_flow(Graph *G)
{
    int i, j;
    for (i = 1; i <= G->n; i++)
        for (j = 1; j <= G->n; j++)
            G->F[i][j] = 0;
}

int min(int a, int b)
{
    return (a < b) ? a : b;
}

typedef struct
{
    int dir;
    int p;
    int sigma;
} Label;

Label labels[MAXN];

int FordFulkerson(Graph *G, int s, int t)
{
    init_flow(G);
    int max_flow = 0;

    Queue Q;

    do
    {
        int i;
        for (i = 1; i <= G->n; i++)
            labels[i].dir = 0;
        labels[s].dir = +1;
        labels[s].p = s;
        labels[s].sigma = oo;
        make_null_queue(&Q);
        enqueue(&Q, s);
        int found = 0;
        while (!empty_queue(&Q))
        {
            int u = front(&Q);
            dequeue(&Q);
            int v;
            for (v = 1; v <= G->n; v++)
                if (G->C[u][v] != NO_EDGE && labels[v].dir == 0 && G->F[u][v] < G->C[u][v])
                {
                    enqueue(&Q, v);
                    labels[v].dir = +1;
                    labels[v].p = u;
                    labels[v].sigma = min(labels[u].sigma, G->C[u][v] - G->F[u][v]);
                }
            for (v = 1; v <= G->n; v++)
                if (G->C[v][u] != NO_EDGE && labels[v].dir == 0 && G->F[v][u] > 0)
                {
                    enqueue(&Q, v);
                    labels[v].dir = -1;
                    labels[v].p = u;
                    labels[v].sigma = min(labels[u].sigma, G->F[v][u]);
                }
            if (labels[t].dir != 0)
            {
                found = 1;
                break;
            }
        }
        if (found == 1)
        {
            int sigma = labels[t].sigma;
            int u = t;
            while (u != s)
            {
                int p = labels[u].p;
                if (labels[u].dir > 0)
                    G->F[p][u] += sigma;
                else if (labels[u].dir < 0)
                    G->F[u][p] -= sigma;
                u = p;
            }
            max_flow += sigma;
        }
        else
            break;
    } while (1);
    return max_flow;
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

    int max_flow = FordFulkerson(&G, 1, n);
    printf("Max flow: %d\n", max_flow);
    printf("S:");
    for (i = 1; i <= G.n; i++)
        if (labels[i].dir != 0)
            printf(" %d", i);
    printf("\nT:");
    for (i = 1; i <= G.n; i++)
        if (labels[i].dir == 0)
            printf(" %d", i);
    return 0;
}