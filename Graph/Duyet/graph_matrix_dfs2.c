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

void makeNull_List(List *L) // Khoi tao List rong
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

// Khai bao cau truc Stack
typedef struct Stack
{
    int data[MAX_elementStack];
    int index;
} Stack;

void makeNull_Stack(Stack *S) // Khoi tao empty Stack
{
    S->index = MAX_elementStack;
}

void push_Stack(Stack *S, int x) // Them x vao stack
{
    if (S->index == 0)
        return;
    S->index--;
    S->data[S->index] = x;
}

int top_Stack(Stack *S) // Tra ve phan tu tai dinh Stacl
{
    return S->data[S->index];
}

void pop_Stack(Stack *S) // Lay phan tu o dinh ra khoi Stack
{
    S->index++;
}

int empty_Stack(Stack *S) // Kiem tra xem co phai ngan xep rong
{
    return S->index == MAX_elementStack;
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
    makeNull_List(&L);
    int i;
    for (i = 1; i <= G->n; i++)
    {
        if (G->A[i][x] != 0)
            push_back(&L, i);
    }
    return L;
}

List depth_first_search(Graph *G, int x, int parent[]) // Duyet Graph bat dau tai dinh x
{
    int i;
    int mark[MAX_Vertices];
    for (i = 1; i <= G->n; i++) // Khoi tao mang danh dau dinh chua duoc duyet
    {
        mark[i] = 0;
    }
    List L; // Khoi tao List luu thu tu duyet
    makeNull_List(&L);
    Stack S;
    makeNull_Stack(&S);
    push_Stack(&S, x);
    parent[x] = 0;
    while (!empty_Stack(&S))
    {
        int u = top_Stack(&S);
        pop_Stack(&S);
        if (mark[u] != 0)
            continue;
        push_back(&L, u);
        mark[u] = 1;
        List ner = neighbors(G, u);
        for (i = 1; i <= ner.size; i++)
            if (mark[element_at(&ner, i)] == 0)
            {
                push_Stack(&S, element_at(&ner, i));
                parent[element_at(&ner, i)] = u;
            }
    }
    return L;
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
    int parent[MAX_Vertices];
    int mark[MAX_Vertices];
    for (i = 1; i <= G.n; i++) // Khoi tao mang danh dau dinh chua duoc duyet
    {
        mark[i] = 0;
        parent[i] = -1;
    }
    List order;
    makeNull_List(&order);
    for (i = 1; i <= G.n; i++)
    {
        if (mark[i] != 0)
            continue;
        int j;
        List L = depth_first_search(&G, i, parent);
        for (j = 1; j <= L.size; j++)
        {
            push_back(&order, element_at(&L, j));
            mark[element_at(&L, j)] = 1;
        }
    }
    for (i = 1; i <= order.size; i++)
        printf("Duyet : %d\n", element_at(&order, i));
    for (i = 1; i <= n; i++)
        printf("parent of %d is %d\n", i, parent[i]);
    return 0;
}