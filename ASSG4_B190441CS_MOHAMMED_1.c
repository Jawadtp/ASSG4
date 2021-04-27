#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
}typedef node;

node* createNode(int x)
{
    node *t = (node *)malloc(sizeof(node));
    t->data=x;
    t->next=NULL;
    return t;
}

node* getAdjacencyList(int m[], int n, int x)
{
    node *head=createNode(x);
    node *t=head;
    for(int i=0; i<n; i++)
    {
        if(m[i]) 
        {
           t->next=createNode(i);
           t=t->next;
        }
    }
    return head;
}

void printList(node *t)
{
    while(t)
    {
        printf("%d ",t->data);
        t=t->next;
    }
    printf("\n");
}

int main()
{
    int n;
    scanf("%d", &n);
    int mat[n][n];

    int x;
    int i=0;
    while(i<n)
    {
        int j=0;
        while(j<n)
        {
            scanf("%d", &x);
            mat[i][j]=x;
            j++;
        }
        i++;
    }        

    node* adjList[n];
    for(i=0; i<n; i++)
        adjList[i]=getAdjacencyList(mat[i], n, i);

    for(i=0; i<n; i++)
        printList(adjList[i]);
    return 0;
}