/* Bai tap 4b - DSC: ham adjacent(), co huong
    kiem tra dinh u co ke voi dinh v hong?
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

int EdgeInGraph(Graph *pG, int u, int v)
{
    int i;
    for (i = 0; i < pG->m; i++)
        if ((pG->edges[i].u == u && pG->edges[i].v == v))
            return 1;
    return 0;
}

void add_edge(Graph *pG, int u, int v)
{
    if (u < 1 || u > pG->n || v < 1 || v > pG->n)
        return;
    if (EdgeInGraph(pG, u, v))
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

int main()
{
    Graph G;
    init_graph(&G, 4);
    add_edge(&G, 1, 2);
    add_edge(&G, 3, 4);
    add_edge(&G, 5, 1);
    add_edge(&G, 1, 7);
    add_edge(&G, 3, 4);
    add_edge(&G, 4, 3);
    add_edge(&G, 1, 3);
    printf("n = %d, m = %d\n", G.n, G.m);
    int e;
    for (e = 0; e < G.m; e++)
        printf("%d %d\n", G.edges[e].u, G.edges[e].v);
    if (adjacent(&G, 3, 1))
        printf("YES\n");
    else
        printf("NO\n");
    if (adjacent(&G, 4, 1))
        printf("YES\n");
    else
        printf("NO\n");
    if (adjacent(&G, 1, 2))
        printf("YES\n");
    else
        printf("NO\n");
    return 0;
}