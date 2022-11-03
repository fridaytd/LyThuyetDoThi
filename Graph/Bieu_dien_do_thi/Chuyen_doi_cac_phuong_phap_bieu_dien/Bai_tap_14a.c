#include <stdio.h>
#include <string.h>
#define MAX_Element 100
#define MAX_N 100

// Khai bao cau truc List
typedef struct
{
    int data[MAX_Element];
    int size;
} List;

void make_null(List *pL)
{
    pL->size = 0;
}

void push_back(List *pL, int x)
{
    pL->data[pL->size] = x;
    pL->size++;
}

int element_at(List *pL, int x)
{
    return pL->data[x - 1];
}

int count_list(List *pL)
{
    return pL->size;
}

// Khai bao cau truc Graph (danh sach dinh ke)
typedef struct
{
    // so dinh cua do thi
    int n;
    // Mang cac List luu danh sach cung
    List adj[MAX_N];
} Graph;

void init_graph(Graph *pG, int n)
{
    pG->n = n;
    int i;
    for (i = 1; i <= pG->n; i++)
        make_null(&pG->adj[i]);
}

void add_edge(Graph *pG, int u, int v)
{
    if (u == v)
    {
        push_back(&pG->adj[u], v);
    }
    else
    {
        push_back(&pG->adj[u], v);
        push_back(&pG->adj[v], u);
    }
}

void display_DSK(Graph *G)
{
    int i;
    for (i = 1; i <= G->n; i++)
    {
        int j;
        for (j = 1; j <= G->adj[i].size; j++)
            printf("%d ", element_at(&G->adj[i], j));
        printf("0\n");
    }
}

// Khai bao cau truc Graph ma tran ke
typedef struct
{
    int n, m;
    int A[MAX_N][MAX_N];
} Graph_MTK;

int main()
{
    Graph DSK;
    Graph_MTK MTK;
    int n;
    scanf("%d", &n);
    init_graph(&DSK, n);
    int i, j;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            scanf("%d", &MTK.A[i][j]);
    for (i = 1; i <= n; i++)
        for (j = i; j <= n; j++)
        {
            int k;
            for (k = 1; k <= MTK.A[i][j]; k++)
                add_edge(&DSK, i, j);
        }
    display_DSK(&DSK);
    return 0;
}
