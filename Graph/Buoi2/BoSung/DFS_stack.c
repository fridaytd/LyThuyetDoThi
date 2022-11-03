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
    int elements[MAX_Element];
    int top;
} Stack;

void make_null_stack(Stack *S)
{
    S->top = MAX_Element;
}

int empty_stack(Stack *S)
{
    return S->top == MAX_Element;
}

void push(Stack *S, int x)
{
    S->top--;
    S->elements[S->top] = x;
}

int top(Stack *S)
{
    return S->elements[S->top];
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

void DFS(Graph *G, int s)
{
    Stack S;
    make_null_stack(&S);
    push(&S, s);
    while (!empty_stack(&S))
    {
        int u = top(&S);
        pop(&S);
        parent[s] = 0;
        if (mark[u] != 0)
            continue;
        // printf("%d\n", u);
        mark[u] = 1;
        List L = neighbors(G, u);
        int i;
        for (i = 1; i <= L.size; i++)
        {
            int v = element_at(&L, i);
            if (mark[v] == 0)
            {
                push(&S, v);
                parent[v] = u;
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
            DFS(&G, i);
    for (i = 1; i <= G.n; i++)
        printf("%d %d\n", i, parent[i]);
    return 0;
}