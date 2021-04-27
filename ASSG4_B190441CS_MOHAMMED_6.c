#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    int mark;
    int degree;
    struct Node *parent;
    struct Node* left;
    struct Node* right;
    struct Node* child;
}typedef node;

node* createNode(int data)
{
    node *t = (node *)malloc(sizeof(node));
    t->data=data;
    t->mark=0;
    t->degree=0;
    t->left=t->right=t->child=t->parent=NULL;
    return t;
}

node* insertIntoFHeap(node *H, node *x)
{
    if(!H)
    {
        H=x;
        H->right=H;
        H->left=H;
        return H;
    }

    x->right=H;
    x->left=H->left;
    H->left->right=x;
    H->left=x;
    if(x->data < H->data) H=x;
    return H;
}

node* binomialLink(node *a, node *b)
{
    if(a->data > b->data) return binomialLink(b,a);
    node* start = a->child;
    node* end = a->child? a->child->left:NULL;
    a->child=b;
    a->right=a;
    a->left=a;
    b->parent=a;
    b->right= start?start:b;
    b->left=end?end:b;
    if(start) start->left=b;
    if(end) end->right=b;
    a->degree=a->degree+1;
    a->child= b->data < b->right->data? b:b->right;
    return a;
}

node* Consolidate(node *H)
{
    if(!H) return NULL;
    node* arr[10];
    for(int i=0; i<10; i++)
        arr[i]=NULL;
    node *t=H;
    int nodeCount=0;
    do
    {
        nodeCount++;
        t=t->right;
    } while (t!=H);
    
    t=H;
    while(nodeCount--)
    {
        int d= t->degree;
        int check=0;
        while(arr[d])
        {
            
            node *temp = arr[d];
           
            temp->left->right=temp->right;
            temp->right->left=temp->left;
            node *tl = t->left;
            node *tr = t->right;
            if(tl == t && tr ==t) check=1;
            node *linked = binomialLink(t, temp);
            if(check) return linked;
            tl->right = linked;
            linked->left=tl;
            tr->left=linked;
            linked->right=tr;
            t=linked;
            arr[d]=NULL;
            d= t->degree;
            
        }
        arr[d]=t;
        t=t->right;
    }
    node *x=t;
    H=t;
    do
    {
        if(x->data < H->data) H=x;
        x=x->right;
    } while (x!=t);
    return H;
}

node* extractMin(node *H)
{
    if(!H) return NULL;
    if(H==H->right) return Consolidate(H->child);
    node *x = H->child;
    node *H1= H->right;
    if(x)
    {
        node *t = x;
        do
        {
            t->parent=NULL;
            t=t->right;
        } while (t!=x);
        
        H->left->right=x;
        node *prev= x->left;
        x->left=H->left;
        prev->right=H->right;
        H->right->left=prev;
        
    }
    else
    {
        H->left->right=H->right;
        H->right->left=H->left;
    }
    return Consolidate(H1); 

}

void FInsert(node **H, node *x)
{
    *H = insertIntoFHeap(*H, x);
}

void FExtractMin(node **H)
{
    *H = extractMin(*H);
}



void searchUtil(node *H, int key, node **result)
{
    if(*result || !H) return;
    
    node *t = H;
    do
    {
        if(t->data == key)
        {
            *result = t;
            return;
        }   
        searchUtil(t->child, key, result);
        t=t->right;
    } while (t!=H);
    
}

node* search(node *H, int key)
{
    node *result=NULL;
    searchUtil(H, key, &result);
    return result;
}

void cut(node *H, node *t)
{
    t->parent->degree=t->parent->degree-1;
    if(t==t->parent->child)
    {
        if(t->right!=t) t->parent->child=t->right;
        else t->parent->child=NULL;
    }
    t->parent=NULL;
    t->left->right=t->right;
    t->right->left=t->left;
    t->mark=0;
    t->right=H;
    t->left=H->left;
    H->left->right=t;
    H->left=t;

}

void cascadingCut(node *H, node *t)
{
    if(!t->parent) return;
    if(t->parent->mark==0)
    {
        t->parent->mark=1;
    }
    else
    {
        cut(H, t);
        cascadingCut(H, t->parent);
    }
}   

node* decreaseKey(node *H, int x, int k)
{

    if(!H) return H;
    node* t = search(H, x);
    if(!t) return H;

    t->data=k;

    if(t->parent && t->data < t->parent->data)
    {
        node *temp = t->parent;
       cut(H, t); 
        cascadingCut(H, temp); 
    }
    if(t->data < H->data) H=t;
    return H;
}


void FDecreaseKey(node **H, int x, int k)
{
    *H = decreaseKey(*H, x, k);
}


void FDelete(node **H, int x)
{
    *H=decreaseKey(*H, x, 99999);
    *H=extractMin(*H);
}

void printTree(node *H)
{
    if(!H) return;
    node *t=H;
    do
    {
        printf("%d ", t->data);
        t=t->right;
    } while (t!=H);

    t=H;
    do
    {
        printTree(t->child);
        t=t->right;
    } while (t!=H);
        
}

void levelPrint(node *H)
{
    if(!H) return;
    node *t = H;
    do
    {
        printf("%d ", t->data);
        printTree(t->child);
        t=t->right;
    } while (t!=H);
    
}

int count=10;

void printHeap(node *H)
{
    if(!H) return;
    
    node *t=H;
    do
    {
        count--;
        printf("%d ", t->data);
        printHeap(t->child);
        t=t->right;
    } while (t!=H);
        
}
void printList(node *H)
{
    if(!H) return;
    node *x=H;
    do
    {
        printf("%d ", x->data);
        x=x->right;
    } while (x!=H);
    
}
int main()
{
    node *H=NULL;
    char c;
    int x,y, flag=1;
    while(flag)
    {
        scanf("%c",&c);
        switch(c)
        {
            case 'i':
            {
                scanf("%d", &x);
                FInsert(&H, createNode(x));
                break;
            }
            case 'm':
            {
                printf("%d\n", H->data);
                break;
            }
            case 'x':
            {
                x=H->data;
                printf("%d\n", x);
                FExtractMin(&H);
                break;
            }
            case 'r':
            {
                scanf("%d %d", &x, &y);
                if(y>x) 
                {
                    printf("-1\n");
                    break;
                }
                FDecreaseKey(&H, x, y);
                printf("%d\n", y);
                break;
            }
            case 'd':
            {
                scanf("%d", &x);
                FDelete(&H, x);
                printf("%d\n", x);
                break;
            }
            case 'p':
            {
               
              // levelPrint(H);
                printList(H);
                printf("\n");
                break;
            }
            case 'e':
            {
                flag=0;
                break;
            }
        }
    }
    return 0;
}