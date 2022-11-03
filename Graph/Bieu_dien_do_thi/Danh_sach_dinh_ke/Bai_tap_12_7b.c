/*  Bai tap 12 _ 7b - DSDK: ham innit_graph() & add_edge(), da do thi vo huong, co the co khuyen
 */

#include <stdio.h>
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
    Graph G;
    init_graph(&G, 5);
    add_edge(&G, 3, 4);
    add_edge(&G, 1, 3);
    add_edge(&G, 2, 2);
    int i;
    for (i = 1; i <= G.n; i++)
    {
        printf("Adj[%d] = ", i);
        int j;
        for (j = 1; j <= G.adj[i].size; j++)
            printf("%d ", element_at(&G.adj[i], j));
        printf("\n");
    }
    return 0;
}