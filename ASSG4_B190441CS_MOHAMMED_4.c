#include <stdio.h>
#include <stdlib.h>

#define MAX_ADJACENT 100

struct Node
{
    int data;
    int visited;
    struct Node *adj[MAX_ADJACENT];
    struct Node* next;
    
}typedef node;

struct Queue
{
    struct Node *head;
    struct Node* tail;
}typedef queue;


node* createNode(int data)
{
    node *t = (node *)malloc(sizeof(node));
    t->data=data;
    t->visited=0;
    t->next=NULL;
    for(int i=0; i<MAX_ADJACENT; i++)
        t->adj[i]=NULL;
    return t;    
}

void enqueue(queue *q, node *x)
{
    if(!q->head) 
    {
        q->head=x;
        q->tail=x;
        return;
    }
    q->tail->next=x;
    q->tail=x;
}

node* dequeue(queue *q)
{
    if(!q->head) return NULL;
    node *x = q->head;
    q->head=q->head->next;
    if(!q->head)
    {
        q->head=q->tail=NULL;
    }
    return x;
}

int isQueueEmpty(queue *q)
{
    return q->head?0:1;
}
void addEdge(node *a, node *adj)
{
    int i=0;
    while(a->adj[i])
        i++;

    a->adj[i]=adj;
}

void clearVisited(node *arr[], int n)
{
    for(int i=0; i<n; i++)
        arr[i]->visited=0;
}

void dfs(node *a)
{
   if(a->visited) return;
   a->visited=1;
   printf("%d ",a->data);
   for(int i=0; a->adj[i]; i++)
        dfs(a->adj[i]);
}

void bfs(node *a)
{
    if(!a) return;
    queue q;
    q.head=q.tail=NULL;
    enqueue(&q, a);
    while(!isQueueEmpty(&q))    
    {
        node *t = dequeue(&q);
        if(t->visited==0)
        {
            printf("%d ", t->data);
            t->visited=1;
            for(int i=0; t->adj[i]; i++)
                enqueue(&q, t->adj[i]);
        }        
    } 
}

int main()
{
    
    int v, e;
    scanf("%d %d", &v, &e);
    node *vert[v];
    for(int i=0; i<v; i++)
        vert[i]=createNode(i);
    int a, b, s;    
    while(e--)
    {
        scanf("%d %d", &a, &b);
        addEdge(vert[a], vert[b]);
    }
    scanf("%d", &s);
    bfs(vert[s]);
    printf("\n");
    clearVisited(vert, v);
    dfs(vert[s]);
    return 0;
}