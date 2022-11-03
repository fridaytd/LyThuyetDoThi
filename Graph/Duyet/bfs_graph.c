#include <stdio.h>

#define MAX_Vertices 20
#define MAX_Length 20
#define MAX_elementStack 40
#define MAX_elememtQueue 40
// Khai bao cau truc List
typedef struct List
{
    int data[MAX_Length];
    int size;
} List;

void make_null(List *L) // Khoi tao List rong
{
    L->size = 0;
}

void push_back(List *L, int x) // insert x vao cuoi List
{
    L->data[L->size] = x;
    L->size++;
}

int element_at(List *L, int x) // Tra ve gia tri co tai chi so x
{
    return L->data[x - 1];
}

// Khai bao cau truc Queue
typedef struct Queue
{
    int data[MAX_elememtQueue];
    int front, rear;
} Queue;

void makeNull_Queue(Queue *Q)
{
    Q->front = 0;
    Q->rear = -1;
}

int empty_Queue(Queue *Q)
{
    return Q->rear == -1;
}

void push_Queue(Queue *Q, int x)
{
    Q->rear = (Q->rear + 1) % MAX_elememtQueue;
    Q->data[Q->rear] = x;
}

void pop_Queue(Queue *Q)
{
    if (Q->front == Q->rear)
        makeNull_Queue(Q);
    else
        Q->front = (Q->front + 1) % MAX_elememtQueue;
}

int top_Queue(Queue *Q)
{
    return Q->data[Q->front];
}

// Khai bao cau truc Graph
typedef struct Graph
{
    int A[MAX_Vertices][MAX_Vertices];
    int n;
} Graph;

void init_graph(Graph *G, int n) // Khoi tao Graph voi n dinh
{
    G->n = n;
    int i, j;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            G->A[i][j] = 0;
}

void add_edge(Graph *G, int x, int y) // Them cung e = (x, y)
{
    G->A[x][y] = 1;
    G->A[y][x] = 1;
}

int degree(Graph *G, int x) // tinh bac cua dinh x
{
    int i, deg = 0;
    for (i = 1; i <= G->n; i++)
        deg += (G->A[i][x] != 0) ? 1 : 0;
    return deg;
}

int adjacent(Graph *G, int x, int y) // Kiem tra xem dinh x va dinh y co ke nhau khong
{
    return G->A[x][y] != 0;
}

void remove_edge(Graph *G, int x, int y) // Xoa cung e = (x, y) ra khoi do thi
{
    G->A[x][y] = 0;
    G->A[y][x] = 0;
}

List neighbors(Graph *G, int x) // Tra ve danh sach cac dinh ke cua x
{
    List L;
    make_null(&L);
    int i;
    for (i = 1; i <= G->n; i++)
    {
        if (G->A[i][x] != 0)
            push_back(&L, i);
    }
    return L;
}

List broad_first_search(Graph *G, int x, int parent[])
{
    List dfs_L;
    make_null(&dfs_L);
    Queue Q;
    makeNull_Queue(&Q);
    int mark[MAX_Vertices];
    int i;
    for (i = 1; i <= G->n; i++)
        mark[i] = 0;
    push_Queue(&Q, x);
    parent[x] = 0;
    while (!empty_Queue(&Q))
    {
        int u = top_Queue(&Q);
        pop_Queue(&Q);
        if (mark[u] != 0)
            continue;
        push_back(&dfs_L, u);
        mark[u] = 1;
        List L = neighbors(G, u);
        for (i = 1; i <= L.size; i++)
        {
            int v = element_at(&L, i);
            if (mark[v] == 0)
                push_Queue(&Q, v);
            if (parent[v] == -1)
                parent[v] = u;
        }
    }
    return dfs_L;
}

int main()
{
    freopen("dothi.txt", "r", stdin);
    Graph G;
    int n, m;
    scanf("%d%d", &n, &m);
    init_graph(&G, n);
    int u, v;
    int i;
    for (i = 1; i <= m; i++)
    {
        scanf("%d%d", &u, &v);
        add_edge(&G, u, v);
    }
    int mark[MAX_Vertices];
    int parent[MAX_Vertices];
    for (i = 1; i <= G.n; i++)
    {
        mark[i] = 0;
        parent[i] = -1;
    }
    for (i = 1; i <= G.n; i++)
    {
        if (mark[i] == 0)
        {
            List L = broad_first_search(&G, i, parent);
            int j;
            for (j = 1; j <= L.size; j++)
            {
                printf("Duyet : %d\n", element_at(&L, j));
                mark[element_at(&L, j)] = 1;
            }
        }
    }
    for (i = 1; i <= G.n; i++)
        printf("parent of %d is %d\n", i, parent[i]);
    return 0;
}
