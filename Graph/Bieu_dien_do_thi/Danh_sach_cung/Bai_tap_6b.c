/* Bai tap 6b - DSC: Liet ke dinh ke cua do thi co huong
    Bieu dien do thi va in bac cac dinh ra man hinh.
*/

#include <stdio.h>

// Dinh nghia hang MAX_M : so luong cung toi da ma do thi co the chua
#define MAX_M 100

// Dinh nghia cau truc Edge : dinh nghia cau truc cung
typedef struct
{
    int u, v;
} Edge;

// Dinh nghia cau truc Graph : luu tru mot do thi
typedef struct
{
    // n : so dinh, m : so cung;
    int n, m;
    // mang edges luu tru cung cua do thi
    Edge edges[MAX_M];
} Graph;

void init_graph(Graph *pG, int n)
{
    pG->n = n;
    pG->m = 0;
}

void add_edge(Graph *pG, int u, int v)
{
    if (u < 1 || u > pG->n || v < 1 || v > pG->n)
        return;
    pG->edges[pG->m].u = u;
    pG->edges[pG->m].v = v;
    pG->m++;
}

int adjacent(Graph *pG, int u, int v)
{
    int i;
    for (i = 0; i < pG->m; i++)
        if ((pG->edges[i].u == u && pG->edges[i].v == v))
            return 1;
    return 0;
}

int degree(Graph *pG, int u)
{
    int i, deg = 0;
    for (i = 0; i < pG->m; i++)
    {
        if (pG->edges[i].u == u)
            deg++;
        if (pG->edges[i].v == u)
            deg++;
    }
    return deg;
}

void neighbors(Graph *pG, int u)
{
    int e;
    for (e = 1; e <= pG->n; e++)
        if (adjacent(pG, u, e))
            printf("%d ", e);
    printf("\n");
}

int main()
{
    Graph G;
    int n, m;
    freopen("dothi.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    init_graph(&G, n);
    int i, u, v;
    for (i = 1; i <= m; i++)
    {
        scanf("%d%d", &u, &v);
        add_edge(&G, u, v);
    }
    for (u = 1; u <= G.n; u++)
    {
        printf("neighbors(%d) = ", u);
        neighbors(&G, u);
    }
    return 0;
}