#include <stdio.h>
#include <string.h>
// Dinh nghia hang MAX_N : so dinh toi da ma do thi co the chua
#define MAX_N 100
#define MAX_Element 100

// Dinh nghia cau truc Graph_MTK : ma tran dinh - dinh (ma tran ke)
typedef struct
{
    // n : so dinh, m : so cung
    int n, m;
    // mang A luu ma tran ke.
    int A[MAX_N][MAX_N];
} Graph_MTK;

void init_Graph_MTK(Graph_MTK *pG, int n)
{
    pG->n = n;
    pG->m = 0;
    int i, j;
    for (i = 1; i <= pG->n; i++)
        for (j = 1; j <= pG->n; j++)
            pG->A[i][j] = 0;
}

void add_edge_MTK(Graph_MTK *pG, int u, int v)
{
    if (u == v)
    {
        pG->A[u][v]++;
    }
    else
    {
        pG->A[u][v]++;
        pG->A[v][u]++;
    }
}

void display_MTK(Graph_MTK *G)
{
    int i, j;
    for (i = 1; i <= G->n; i++)
    {
        for (j = 1; j <= G->n; j++)
            printf("%d ", G->A[i][j]);
        printf("\n");
    }
}

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

// Khai bao cau truc Graph_DSK (danh sach dinh ke)
typedef struct
{
    // so dinh cua do thi
    int n;
    // Mang cac List luu danh sach cung
    List adj[MAX_N];
} Graph_DSK;

void init_Graph_DSK(Graph_DSK *pG, int n)
{
    pG->n = n;
    int i;
    for (i = 1; i <= pG->n; i++)
        make_null(&pG->adj[i]);
}

void add_edge_DSC(Graph_DSK *pG, int u, int v)
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

int main()
{
    Graph_DSK DSC;
    Graph_MTK MTK;
    int n;
    scanf("%d", &n);
    getchar();
    init_Graph_DSK(&DSC, n);
    init_Graph_MTK(&MTK, n);
    int i;
    for (i = 1; i <= DSC.n; i++)
    {
        printf("Adj[%d] = ", i);
        char s[20];
        fgets(s, 20, stdin);
        int j;
        for (j = 0; j < strlen(s); j++)
        {
            if (s[j] >= '1' && s[j] <= '9' && (int)(s[j] - 48) >= i)
                add_edge_DSC(&DSC, i, (int)(s[j] - 48));
        }
    }
    for (i = 1; i <= DSC.n; i++)
    {
        int j;
        for (j = 1; j <= DSC.adj[i].size; j++)
            if (element_at(&DSC.adj[i], j) >= i)
                add_edge_MTK(&MTK, i, element_at(&DSC.adj[i], j));
    }
    display_MTK(&MTK);
    return 0;
}