#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 10000

struct Node{
    int data;
    int rank;
    struct Node *parent;
}typedef node;

int *count;

node* makeSet(int data)
{
    node *t = (node *)malloc(sizeof(node));
    t->parent=t;
    t->data=data;
    t->rank=0;
    return t;
}

node* findSet(node *a, int type) //No path compression.
{
    count[type]++;
    if(a!=a->parent) return findSet(a->parent, type);
    return a;
}

node *findSetP(node *a, int type) //With path compression
{
    count[type]++;
    if(a!=a->parent) 
        a->parent = findSetP(a->parent, type);
    return a->parent;
}

int link(node *a, node *b, int type)
{
    if(b->rank > a->rank)
    {
        a->parent = b;
        if(type == 1 || type == 3) b->rank = (1 + a->rank > b->rank)?1+a->rank:b->rank;
        return b->data;
    }
    else b->parent = a;
    if(type == 1 || type == 3) a->rank = (1 + b->rank > a->rank)?1+b->rank:a->rank;
    return a->data;
}

void setUnion(node **elements[], int x, int y)
{
    if(!elements[0][x] || !elements[0][y])
    {
        printf("-1 -1 -1 -1\n");
        return;
    }
    printf("%d ", link(findSet(elements[0][x], 0), findSet(elements[0][y], 0), 0)); //No heuristic
    printf("%d ", link(findSet(elements[1][x], 1), findSet(elements[1][y], 1), 1)); //Rank
    printf("%d ", link(findSetP(elements[2][x], 2), findSetP(elements[2][y], 2), 2)); //Path compression
    printf("%d\n", link(findSetP(elements[3][x], 3), findSetP(elements[3][y], 3), 3)); //Everything
}

int main()
{
    count = (int *)malloc(4*sizeof(int));
    for(int i=0; i<4; i++)
        count[i]=0;

    node **elements[4];
    for(int i=0; i<4; i++)
        elements[i] = (node**)malloc(MAX_NODES * sizeof(node*));
    
    int flag = 1, x, y;
    char c;

    while(flag)
    {
        scanf("%c", &c);
        switch(c)
        {
            case 'm':
            {
                scanf("%d", &x);
                if(elements[0][x]) printf("-1\n");
                else
                {
                    printf("%d\n",x);
                    for(int i=0; i<4; i++)
                        elements[i][x]=makeSet(x);
                }
                break;
            }
            case 'f':
            {
                scanf("%d", &x);
                if(!elements[0][x]) printf("-1 -1 -1 -1\n");
                else
                    printf("%d %d %d %d\n", findSet(elements[0][x], 0)->data, findSet(elements[1][x], 1)->data, findSetP(elements[2][x], 2)->data, findSetP(elements[3][x], 3)->data);                               
                break;
            }
            case 'u':
            {
                scanf("%d %d", &x, &y);
                setUnion(elements, x, y);
                break;
            }
            case 's':
            {
                printf("%d %d %d %d\n", count[0], count[1], count[2], count[3]);
                flag=0;
                break;
            }
        }
    }
}





