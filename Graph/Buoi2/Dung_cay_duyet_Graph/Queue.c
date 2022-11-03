#define MAX_Element 100

typedef struct
{
    int data[MAX_Element];
    int front, rear;
} Queue;

void make_null_queue(Queue *Q)
{
    Q->front = 0;
    Q->rear = -1;
}

int empty(Queue *Q)
{
    return Q->rear == -1;
}

void enqueue(Queue *Q, int x)
{
    if ((Q->rear - Q->front + 1) % MAX_Element == 0 && !empty(Q))
        return;
    Q->rear = (Q->rear + 1) % MAX_Element;
    Q->data[Q->rear] = x;
}

int front(Queue *Q)
{
    return Q->data[Q->front];
}

void dequeue(Queue *Q)
{
    if (Q->front == Q->rear)
        make_null_queue(Q);
    else
        Q->front = (Q->front + 1) % MAX_Element;
}
