#include <stdio.h>

#define MAX_Vertices 20
#define MAX_Length 20
#define MAX_elementStack 40
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

int mark[MAX_Vertices];
int parent[MAX_Vertices];

void DFS_Recusion(Graph *G, int u, int pr)
{
    if (mark[u] != 0)
        return;
    printf("Duyet: %d\n", u);
    mark[u] = 1;
    parent[u] = pr;
    List nei = neighbors(G, u);
    int v;
    int i;
    for (i = 1; i <= nei.size; i++)
    {
        v = element_at(&nei, i);
        // printf("%d\n", v);
        DFS_Recusion(G, v, u);
    }
}

int main()
{
    Graph G;
    freopen("dothi.txt", "r", stdin);
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
    for (i = 1; i <= n; i++)
    {
        parent[i] = -1;
        mark[i] = 0;
    }
    for (i = 1; i <= n; i++)
        if (mark[i] == 0)
            DFS_Recusion(&G, i, 0);
    for (i = 1; i <= n; i++)
        printf("parent of %d is %d\n", i, parent[i]);
    return 0;
}