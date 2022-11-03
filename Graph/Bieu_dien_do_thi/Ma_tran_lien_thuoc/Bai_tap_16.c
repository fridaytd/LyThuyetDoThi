/*Bieu diễn ma trận đỉnh cung.
 */
#include <stdio.h>
#define MAX_M 100
#define MAX_N 100

// Dinh nghia cau truc Graph ma tran lien thuoc
typedef struct
{
    int n, m;
    int A[MAX_N][MAX_M];
} Graph;

void init_graph(Graph *pG, int n, int m)
{
    pG->n = n;
    pG->m = m;
    int i, j;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
            pG->A[i][j] = 0;
}

void add_edge(Graph *pG, int e, int u, int v)
{
    pG->A[u][e]++;
    pG->A[v][e]++;
}

int adjacent(Graph *pG, int u, int v)
{
    int i;
    for (i = 1; i <= pG->m; i++)
        if (pG->A[u][i] != 0 && pG->A[v][i] != 0)
            return 1;
    return 0;
}

int degree(Graph *pG, int u)
{
    int i;
    int deg = 0;
    for (i = 1; i <= pG->m; i++)
        deg += pG->A[u][i];
    return deg;
}

void neighbors(Graph *pG, int u)
{
    int i;
    for (i = 1; i <= pG->n; i++)
        if (adjacent(pG, u, i))
            printf("%d ", i);
}

int main()
{
    return 0;
}