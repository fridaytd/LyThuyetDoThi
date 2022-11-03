/*  Bai tap 12 _ 10b - DSDK: ham degree(), da do thi co huong co the co khuyen
 */

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
    push_back(&pG->adj[u], v);
}

int adjacent(Graph *pG, int u, int v)
{
    int i;
    for (i = 1; i <= pG->adj[u].size; i++)
        if (element_at(&pG->adj[u], i) == v)
            return 1;
    return 0;
}

int outdegree(Graph *pG, int u)
{
    return pG->adj[u].size;
}

int indegree(Graph *pG, int u)
{
    int i;
    int deg = 0;
    for (i = 1; i <= pG->n; i++)
    {
        int j;
        for (j = 1; j <= pG->adj[i].size; j++)
        {
            if (element_at(&pG->adj[i], j) == u)
                deg++;
        }
    }
    return deg;
}

int degree(Graph *pG, int u)
{
    return indegree(pG, u) + outdegree(pG, u);
}

void neighbors(Graph *pG, int u)
{
    int i;
    for (i = 1; i <= pG->adj[u].size; i++)
        printf("%d ", element_at(&pG->adj[u], i));
}

int main()
{
    Graph G;
    int n;
    printf("Nhap so dinh n = ");
    scanf("%d", &n);
    getchar();
    init_graph(&G, n);
    int i;
    for (i = 1; i <= G.n; i++)
    {
        printf("Adj[%d] = ", i);
        char s[20];
        fgets(s, 20, stdin);
        int j;
        for (j = 0; j < strlen(s); j++)
        {
            if (s[j] >= '0' && s[j] <= '9')
                add_edge(&G, i, (int)(s[j] - 48));
        }
    }
    printf("\n");
    for (i = 1; i <= G.n; i++)
    {
        printf("Adj[%d] = ", i);
        int j;
        for (j = 1; j <= G.adj[i].size; j++)
            printf("%d ", element_at(&G.adj[i], j));
        printf("\n");
    }
    printf("\n");
    for (i = 1; i <= G.n; i++)
    {
        printf("indeg(%d) = %d\n", i, indegree(&G, i));
    }
    printf("\n");
    for (i = 1; i <= G.n; i++)
    {
        printf("outdeg(%d) = %d\n", i, outdegree(&G, i));
    }
    printf("\n");
    for (i = 1; i <= G.n; i++)
    {
        printf("neighbors(%d) = ", i);
        neighbors(&G, i);
        printf("\n");
    }
    return 0;
}