// Recursive C program for level order traversal of Binary Tree
#include <stdio.h>
#include <stdlib.h>
 
/* A binary tree node has data, pointer to left child
   and a pointer to right child */
struct node
{
    int data;
    struct node* left, *right;
};

/* Helper function that allocates a new node with the
   given data and NULL left and right pointers. */
struct node* newNode(int data)
{
    struct node* node = (struct node*)
                        malloc(sizeof(struct node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
 
    return(node);
}

struct node* lca(struct node *root, int a1, int a2) {

    if(NULL == root) return NULL;

    if(root->data == a1 || root->data == a2)
        return root;

    struct node* left_lca = lca(root->left,a1,a2);
    struct node* right_lca = lca(root->right,a1,a2);

    if (left_lca && right_lca) return root;
    else if(left_lca) return left_lca;
    else return right_lca;
}
 
/* Driver program to test above functions*/
int main()
{
    struct node *root = newNode(1);
    root->left        = newNode(2);
    root->right       = newNode(3);
    root->left->left  = newNode(4);
    root->left->right = newNode(5);
    struct node *la = lca(root,3,5);
    printf("lca is %d\n\r",la->data);
    return 0;
}
