#include <stdio.h>
#include <stdlib.h>

struct node{
long int key;
struct node *left,*right,*p;
};

typedef struct node *node;

struct TREE{
node root;};
typedef struct TREE *TREE;

node CREATENODE(long int x)
{
    node temp=(node)malloc(sizeof(struct node));
    temp->left=temp->right=temp->p=NULL;
    temp->key=x;
    return temp;
}
node SEARCH(node root, long int key)
{
    if (root == NULL || root->key == key)
       return root;

    if (root->key < key)
       return SEARCH(root->right, key);

    return SEARCH(root->left, key);
}

node treemin(node z)
{
    node y=z;
    while(y&&y->left!=NULL)
        y=y->left;
    return y;
}

node treemax(node z)
{
    node y=z;
    while(y&&y->right!=NULL)
        y=y->right;
    return y;
}

node SUCCESSOR(node x)
{
    node y;
    if(x->right!=NULL)
        return treemin(x->right);
    y=x->p;
    while(y!=NULL&&x==y->right)
    {
        x=y;
        y=y->p;
    }
    return y;
}

node PREDECESSOR(node x)
{
    node y;
    if(x->left!=NULL)
        return treemax(x->left);
    y=x->p;
    while(y!=NULL&&x==y->left)
    {
        x=y;
        y=y->p;
    }
    return y;
}


void TRANSPLANT(struct TREE T,node u,node v)
{
    if(u->p==NULL)
        T.root=v;
    else if(u==u->p->left)
        u->p->left=v;
    else
        u->p->right=v;
    if(v!=NULL)
        v->p=u->p;

}

void INSERT(struct TREE T, node z)
{
    node y,x;
    y=NULL;
    x=T.root;
    while(x!=NULL)
    {
        y=x;
        if(z->key<x->key)
            x=x->left;
        else
            x=x->right;
    }
    z->p=y;
    if(y==NULL)
        T.root=z;
    else if(z->key<y->key)
        y->left=z;
    else
        y->right=z;
}

void DELETE(struct TREE T,node z)
{
    node y;
    if(z->left==NULL)
        TRANSPLANT(T,z,z->right);
    else if(z->right==NULL)
        TRANSPLANT(T,z,z->left);
    else
    {
        y=treemin(z->right);
        if(y->p!=z)
        {
            TRANSPLANT(T,y,y->right);
            y->right=z->right;
            y->right->p=y;
        }
        TRANSPLANT(T,z,y);
        y->left=z->left;
        y->left->p=y;
    }
    free(z);
}

void INORDER(node x)
{
    if(x!=NULL)
    {
        INORDER(x->left);
        printf("%ld",x->key);
        INORDER(x->right);
    }
}
void PREORDER(node x)
{
 if(x!=NULL)
 {
  printf("%ld",x->key);
  PREORDER(x->left);
  PREORDER(x->right);
 }
}
void POSTORDER(node x)
{
 if(x!=NULL)
 {
  POSTORDER(x->left);
  POSTORDER(x->right);
  printf("%ld",x->key);
 }
}


void main()
{
    char opt;
    long int k;
    TREE T;
    T->root=NULL;
    node temp,y;
    while(1){
        scanf("%c",&opt);
        switch(opt)
        {
        case 'a':
            scanf("%ld",&k);
            temp=CREATENODE(k);
            INSERT(T,temp);
            break;
        case 'd':
            scanf("%ld",&k);
            temp=SEARCH(T.root,k);
            printf("\n");
            if(temp!=NULL){
            printf("%ld",temp->key);
            DELETE(T,temp);
            }
            else
                printf("-1");
            printf("\n");
            break;
        case 's':
            scanf("%ld",&k);
            temp=SEARCH(T.root,k);
            printf("\n");
            if(temp!=NULL)
            printf("1");
            else
                printf("-1");
            printf("\n");
            break;
        case 'c':
            scanf("%ld",&k);
            temp=SEARCH(T.root,k);
            printf("\n");
            if(temp!=NULL)
            {
            y=SUCCESSOR(temp);
            printf("%ld",y->key);
            }
            else
                printf("-1");
            printf("\n");
            break;
        case 'r':
            scanf("%ld",&k);
            temp=SEARCH(T.root,k);
            printf("\n");
            if(y!=NULL){
            y=PREDECESSOR(temp);
            printf("%ld",y->key);}
            else
                printf("-1");
            printf("\n");
            break;
        case 'i':
            printf("\n");
            INORDER(T.root);
            printf("\n");
            break;
        case 'p':
            printf("\n");
            PREORDER(T.root);
            printf("\n");
            break;
        case 't':
            printf("\n");
            POSTORDER(T.root);
            printf("\n");
            break;
        case 'e':
            exit(0);
            break;
        }
    }
}
