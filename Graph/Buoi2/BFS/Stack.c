#define MAX_Element 100

typedef struct
{
    int elements[MAX_Element];
    int top;
} Stack;

void make_null_stack(Stack *S)
{
    S->top = -1;
}

int empty(Stack *S)
{
    return S->top == -1;
}

int top(Stack *S)
{
    return S->elements[S->top];
}

void push(Stack *S, int x)
{
    S->top++;
    S->elements[S->top] = x;
}

void pop(Stack *S)
{
    S->top--;
}