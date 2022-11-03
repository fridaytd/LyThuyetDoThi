#include <stdio.h>

#define MAX_Element 100

typedef struct
{
    int elements[MAX_Element];
    int top;
} Stack;

void make_null_stack(Stack *S)
{
    S->top = -1;
}

int empty(Stack *S)
{
    return S->top == -1;
}

int top(Stack *S)
{
    return S->elements[S->top];
}

void push(Stack *S, int x)
{
    S->top++;
    S->elements[S->top] = x;
}

void pop(Stack *S)
{
    S->top--;
}

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
    if (L->size == MAX_Element)
        return;
    L->data[L->size] = x;
    L->size++;
}

int element_at(List *L, int x)
{
    return L->data[x - 1];
}

#define MAX_N 100

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
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            G->A[i][j] = 0;
}

void add_edge(Graph *G, int u, int v)
{
    G->A[u][v]++;
    G->m++;
}

int adjacent(Graph *G, int u, int v)
{
    return G->A[u][v] != 0;
}

List neighbors(Graph *G, int x)
{
    List L;
    make_null_list(&L);
    int i;
    for (i = 1; i <= G->n; i++)
        if (adjacent(G, x, i))
            push_back(&L, i);
    return L;
}

int num[MAX_N];
int min_num[MAX_N];
int on_stack[MAX_N];
int k;
Stack S;
int count = 0;
int max = -1;

int min(int a, int b)
{
    return (a < b) ? a : b;
}

void SCC(Graph *G, int u)
{
    num[u] = k;
    min_num[u] = k;
    k++;
    push(&S, u);
    on_stack[u] = 1;
    List L = neighbors(G, u);
    int i;
    for (i = 1; i <= L.size; i++)
    {
        int v = element_at(&L, i);
        if (num[v] < 0)
        {
            SCC(G, v);
            min_num[u] = min(min_num[u], min_num[v]);
        }
        else if (on_stack[v])
            min_num[u] = min(min_num[u], num[v]);
    }
    if (num[u] == min_num[u])
    {
        // printf("\nTim duoc bo phan lien thong manh, %d la dinh khop\n", u);
        count++;
        int w;
        int dem = 0;
        do
        {
            w = top(&S);
            pop(&S);
            // printf("%d\n", w);
            on_stack[w] = 0;
        } while (w != u);
        if (dem > max)
            max = dem;
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
    make_null_stack(&S);
    k = 1;
    for (i = 1; i <= n; i++)
    {
        num[i] = -1;
        on_stack[i] = 0;
    }
    for (i = 1; i <= n; i++)
        if (num[i] < 0)
            SCC(&G, i);
    // for (i = 1; i <= n; i++)
    //     printf("%d %d\n", num[i], min_num[i]);
    // if (count == 1)
    //     printf("STRONG CONNECTED");
    // else
    //     printf("DISCONNECTED");
    printf("%d", count);
    return 0;
}