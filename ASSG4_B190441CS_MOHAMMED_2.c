#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_ADJACENT 1000

struct Vertex
{
    int data;
    int set;
    struct Vertex *adj[MAX_ADJACENT];
    struct Vertex* parent; //For implementing disjoint set.
}typedef vertex;

struct Edge
{
    vertex *a;
    vertex *b;
    int weight;
}typedef edge;

vertex* createVertex(int data)
{
    vertex *v = (vertex *)malloc(sizeof(vertex));
    for(int i=0; i < MAX_ADJACENT; i++)
        v->adj[i]=NULL;
    v->data=data;
    v->set=data;
    v->parent=NULL;
    return v;
}

vertex* findSet(vertex *a)
{
    while(a->parent)
        a=a->parent;
    return a;
}

void setUnion(vertex *a, vertex *b)
{
    while(a->parent)
        a=a->parent;
    while(b->parent)
        b=b->parent;
    a->parent=b;
}

edge createEdge(vertex *a, vertex *b)
{
    edge t;
    t.a = a;
    t.b = b;
    t.weight=-1;
    return t;
}

void addToAdjacentList(vertex *v, vertex *adj)
{
    int i=0;
    while(v->adj[i])
        i++;
    v->adj[i]=adj;
}

void printAdjacentList(vertex *v)
{
    int i=0;
    while(v->adj[i])
        printf("%d ", v->adj[i++]->data);
    printf("\n");
}

int compare(const void *a, const void *b)
{
    return ((edge *)a)->weight > ((edge *)b)->weight;
}

int main()
{
    char c;
   scanf("%c", &c);
    int v, data;
   scanf("%d\n", &v); 
    
    vertex *verts[v];
    for(int i=0; i<v; i++)
        verts[i]=createVertex(i);
    
    char s[100];
    int index=0;
    int edgeCount=0;
    while(index!=v)
    {
        fgets(s, 100, stdin);
        s[strlen(s)-1]=' ';
        s[strlen(s)]='\0';
        int i=0;
        while(s[i])
        {
            data=0;
            while(s[i]!=' ')
                data=data*10+s[i++]-'0';
            if(data!=index) addToAdjacentList(verts[index], verts[data]);
            if(data>index) edgeCount++;
            i++;
        }
        index++;
    }

    edge edges[edgeCount];
    int e=0;
    for(int i=0; i<v; i++)
        for(int j=0; verts[i]->adj[j]; j++)
        {
            if(verts[i]->adj[j]->data > verts[i]->data)
            edges[e++] = createEdge(verts[i], verts[i]->adj[j]);
        }
    
    index=0, e=0;
    while(index!=v)
    {
        fgets(s, 100, stdin);
        s[strlen(s)-1]=' ';
        s[strlen(s)]='\0';
        int i=0;
        int numCount=0;
        while(s[i])
        {
            data=0;
            while(s[i]!=' ')
                data=data*10+s[i++]-'0';
            if(numCount!=0 && verts[index]->adj[numCount-1]->data > verts[index]->data) edges[e++].weight=data;
            i++;
            numCount++;
        }
        index++;
    }
    
    qsort(edges, edgeCount, sizeof(edge), compare);
  
 /*  for(int i=0; i<edgeCount; i++)
        printf("Edge: (%d %d), weight: %d\n", edges[i].a->data, edges[i].b->data, edges[i].weight);
    */

   int sum=0, count=0;;
   for(int i=0; i<edgeCount && count<=v-1; i++)
   {
       if(findSet(edges[i].a)!=findSet(edges[i].b))
       {
           sum+=edges[i].weight;
           setUnion(edges[i].a, edges[i].b);
           count++;
       }
   }
   printf("%d", sum);
}