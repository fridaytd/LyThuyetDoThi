/* Bai tap 11b - MTK : hàm neighbors(): liet ke tat ca ca dinh ke cua ĐỒ THỊ CÓ HƯỚNG (CÓ THỂ CÓ KHUYÊN).
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
}

int adjacent(Graph *pG, int u, int v)
{
    return pG->A[u][v] != 0;
}

int degree(Graph *pG, int u)
{
    int deg = 0;
    int i;
    for (i = 1; i <= pG->n; i++)
    {
        deg += pG->A[u][i];
        deg += pG->A[i][u];
    }
    return deg;
}

void neighbors(Graph *pG, int u)
{
    int i;
    for (i = 1; i <= pG->n; i++)
        if (adjacent(pG, u, i))
            printf("%d ", i);
    printf("\n");
}

int main()
{
    Graph G;
    int i, n, m, u, v;
    scanf("%d%d", &n, &m);
    init_graph(&G, n);
    for (i = 1; i <= m; i++)
    {
        scanf("%d%d", &u, &v);
        add_edge(&G, u, v);
    }
    for (i = 1; i <= G.n; i++)
    {
        printf("neighbours(%d) = ", i);
        neighbors(&G, i);
    }
    return 0;
}