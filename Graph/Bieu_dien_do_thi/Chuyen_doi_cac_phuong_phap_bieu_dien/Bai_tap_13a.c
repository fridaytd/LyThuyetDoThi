/*Nhap ma tran ke => Danh sach cung (Vo huong)
 */
#include <stdio.h>
#define MAX_M 100
#define MAX_N 100
// Khai bao cau truc Edge
typedef struct
{
    int u, v;
} Edge;

// Khai bao cau truc Graph DSC
typedef struct
{
    int n, m;
    Edge edges[MAX_M];
} Graph_DSC;

void init_graph_DSC(Graph_DSC *pG, int n)
{
    pG->m = 0;
    pG->n = n;
}

void add_edge(Graph_DSC *pG, int u, int v)
{
    pG->edges[pG->m].u = u;
    pG->edges[pG->m].v = v;
    pG->m++;
}

void display_DSC(Graph_DSC *pG)
{
    int i;
    for (i = 0; i < pG->m; i++)
        printf("%d %d\n", pG->edges[i].u, pG->edges[i].v);
}

// Khai bao cau truc Graph ma tran ke
typedef struct
{
    int n, m;
    int A[MAX_N][MAX_N];
} Graph_MTK;

int main()
{
    Graph_DSC DSC;
    Graph_MTK MTK;
    int n;
    scanf("%d", &n);
    init_graph_DSC(&DSC, n);
    int i, j;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            scanf("%d", &MTK.A[i][j]);
    for (i = 1; i <= n; i++)
        for (j = i; j <= n; j++)
        {
            int k;
            for (k = 1; k <= MTK.A[i][j]; k++)
                add_edge(&DSC, i, j);
        }
    display_DSC(&DSC);
    return 0;
}