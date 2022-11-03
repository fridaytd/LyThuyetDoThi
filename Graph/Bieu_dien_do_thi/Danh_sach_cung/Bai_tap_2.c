/* Bai tap 2 - DSC: ham add_edge() co ban
    them cung vao do thi.
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
    printf("n = %d, m = %d\n", G.n, G.m);
    int e;
    for (e = 0; e < G.m; e++)
        printf("%d %d\n", G.edges[e].u, G.edges[e].v);
    return 0;
}