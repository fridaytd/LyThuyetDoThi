/* Bai tap 3c - DSC: ham add_edge() nang cao
    them cung vao do thi co kiem tra dieu kien cua u, v.
    pG la don do thi vo huong, neu cung (u, v) hoac cung (v, u) da co trong pG->edges roi thi khong lam gi ca
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
        if ((pG->edges[i].u == u && pG->edges[i].v == v) || (pG->edges[i].u == v && pG->edges[i].v == u))
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

int main()
{
    Graph G;
    init_graph(&G, 4);
    add_edge(&G, 1, 2);
    add_edge(&G, 3, 4);
    add_edge(&G, 5, 1);
    add_edge(&G, 1, 7);
    add_edge(&G, 3, 4);
    add_edge(&G, 3, 4);
    add_edge(&G, 3, 4);
    add_edge(&G, 4, 3);
    printf("n = %d, m = %d\n", G.n, G.m);
    int e;
    for (e = 0; e < G.m; e++)
        printf("%d %d\n", G.edges[e].u, G.edges[e].v);
    return 0;
}