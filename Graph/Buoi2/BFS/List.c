#define MAX_Element 100

typedef struct
{
    int data[MAX_Element];
    int size;
} List;

void make_null_list(List *L)
{
    L->size = 0;
}

void push_back(List *L, int x)
{
    if (L->size == MAX_Element)
        return;
    L->data[L->size] = x;
    L->size++;
}

int element_at(List *L, int x)
{
    return L->data[x - 1];
}