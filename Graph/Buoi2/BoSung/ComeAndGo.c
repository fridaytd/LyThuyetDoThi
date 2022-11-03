#include <stdio.h>

#define MAX_Element 100
#define MAX_N 100
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
    int top;
} Stack;

void make_null_stack(Stack *S)
{
    S->top = MAX_Element;
}

void push(Stack *S, int x)
{
    S->top--;
    S->data[S->top] = x;
}

int top(Stack *S)
{
    return S->data[S->top];
}

void pop(Stack *S)
{
    S->top++;
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

int min(int a, int b)
{
    return (a < b) ? a : b;
}

int num[MAX_N];
int min_num[MAX_N];
int on_stack[MAX_N];
int k;
Stack S;
int count = 0;

void SCC(Graph *G, int u)
{
    num[u] = k;
    min_num[u] = k;
    k++;
    on_stack[u] = 1;
    push(&S, u);
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
    if (min_num[u] == num[u])
    {
        count++;
        int t;
        do
        {
            t = top(&S);
            pop(&S);
            on_stack[t] = 0;
        } while (t != u);
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
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        if (w == 1)
            add_edge(&G, u, v);
        else
        {
            add_edge(&G, u, v);
            add_edge(&G, v, u);
        }
    }
    make_null_stack(&S);
    for (i = 1; i <= G.n; i++)
    {
        num[i] = -1;
        on_stack[i] = 0;
    }
    k = 1;
    for (i = 1; i <= G.n; i++)
        if (num[i] < 0)
            SCC(&G, i);
    // printf("%d", count);
    if (count == 1)
        printf("OKIE");
    else
        printf("NO");
    return 0;
}