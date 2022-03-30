#include<stdio.h>
#include<stdlib.h>

struct node{
int key;
struct node *left;
struct node *right;
int height;
};

typedef struct node *node;

struct TREE{
node root;};

int max (int a, int b)
{
    return a>b?a:b;
}

int height(node x)
{
    if(x==NULL)
        return 0;
    return 1+max(height(x->left),height(x->right));
}

node CREATENODE(int k)
{
    node temp=(node)malloc(sizeof(struct node));
    temp->key=k;
    temp->right=NULL;
    temp->left=NULL;
    temp->height=0;
    return temp;
}

node rightrotate(node p)
{
    node x=p->left;
    node t=x->right;

    p->left=t;
    x->right=p;
    x->height=height(x);
    p->height=height(p);

    return x;
}

node leftrotate(node p)
{
    node x=p->right;
    node t=x->left;

    p->right=t;
    x->left=p;

    x->height=height(x);
    p->height=height(p);

    return x;
}

node rightleft(node x)
{
    x->right=rightrotate(x->right);
    return leftrotate(x);
}

node leftright(node x)
{
    x->left=leftrotate(x->left);
    return rightrotate(x);
}

int getbalance(node x)
{
    if(x==NULL)
        return 0;
    return height(x->left)-height(x->right);
}

node insert(node root,int k)
{
    if(root==NULL)
        return CREATENODE(k);

    if(k<root->key)
        return insert(root->left,k);
    else if(k>root->key)
        return insert(root->right,k);
    else
        return root;

    root->height=height(root);

    int b=getbalance(root);

    if(b>1)
    {
        if(k<root->left->key)
            return rightrotate(root);
        else
            return leftright(root);
    }
    if(b<-1)
    {
        if(k>root->right->key)
            return leftrotate(root);
        else
            return rightleft(root);
    }
    return root;
}

node treemin(node x)
{
    node temp=x;
    while(temp->left!=NULL)
        temp=temp->left;
    return temp;
}
struct Node* insert(struct Node* node, int key)
{
    /* 1.  Perform the normal BST insertion */
    if (node == NULL)
        return(newNode(key));

    if (key < node->key)
        node->left  = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;


    node->height = height(node);


    int balance = getBalance(node);



    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }


    return node;
}
struct Node* deleteNode(struct Node* root, int key)
{

    if (root == NULL)
        return root;

    if ( key < root->key )
        root->left = deleteNode(root->left, key);

    else if( key > root->key )
        root->right = deleteNode(root->right, key);

    else
    {
        // node with only one child or no child
        if( (root->left == NULL) || (root->right == NULL) )
        {
            struct Node *temp = root->left ? root->left :
                                             root->right;

            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // One child case
             *root = *temp; // Copy the contents of
                            // the non-empty child
            free(temp);
        }
        else
        {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            struct Node* temp = treemin(root->right);


            root->key = temp->key;


            root->right = deleteNode(root->right, temp->key);
        }
    }

    // If the tree had only one node then return
    if (root == NULL)
      return root;


    root->height = 1 + max(height(root->left),
                           height(root->right));


    int balance = getBalance(root);


    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}
