/* Bai tap 8c - MTK : ham add_edge(), ĐA ĐỒ THỊ VÔ HƯỚNG.
 */
#include <stdio.h>

// Dinh nghia hang MAX_N : so dinh toi da ma do thi co the chua
#define MAX_N 100

// Dinh nghia cau truc Graph : ma tran dinh - dinh (ma tran ke)
typedef struct
{
    // n : so dinh, m : so cung
    int n, m;
    // mang A luu ma tran ke.
    int A[MAX_N][MAX_N];
} Graph;

void init_graph(Graph *pG, int n)
{
    pG->n = n;
    pG->m = 0;
    int i, j;
    for (i = 1; i <= pG->n; i++)
        for (j = 1; j <= pG->n; j++)
            pG->A[i][j] = 0;
}

void add_edge(Graph *pG, int u, int v)
{
    pG->A[u][v]++;
    pG->A[v][u]++;
}

int main()
{
    Graph G;
    int i, j, n, m, u, v;
    scanf("%d%d", &n, &m);
    init_graph(&G, n);
    for (i = 1; i <= m; i++)
    {
        scanf("%d%d", &u, &v);
        add_edge(&G, u, v);
    }
    for (i = 1; i <= G.n; i++)
    {
        for (j = 1; j <= G.n; j++)
            printf("%d ", G.A[i][j]);
        printf("\n");
    }
    return 0;
}