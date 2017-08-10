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

struct node *findLCA(struct node* root, int n1, int n2)
{

    if (root == NULL) return NULL;

    if (root->data == n1 || root->data == n2)
        return root;

    struct node *left_lca  = findLCA(root->left, n1, n2);
    struct node *right_lca = findLCA(root->right, n1, n2);

    if (left_lca && right_lca)  return root;

    return (left_lca != NULL)? left_lca: right_lca;
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

int findDistance(struct node *root, int x)
{
    // Base case
    if (root == NULL)
        return -1;

    // Initialize distance
    int dist = -1;

    // Check if x is present at root or in left
    // subtree or right subtree.
    if ((root->data == x) ||
            (dist = findDistance(root->left,
                                 x)) >= 0 ||
            (dist =
             findDistance(root->right,
                 x)) >= 0)
        return dist + 1;

    return dist;
}


void distance(struct node *root,int key,int len, int *res) {

    if (root == NULL) return;
    if(root->data == key) {
        *res = len;
    }
    else {
        len++;
        distance(root->left,key,len,res);
        distance(root->right,key,len,res);
    }
}

int find_distance(struct node *root, int a1, int a2) {
    if(root == NULL) {
        return 0;
    }
    int d1,d2,d3;
    struct node *lc = lca(root,a1,a2);
    distance(root,a1,0,&d1);
    distance(root,a2,0,&d2);
    distance(root,lc->data,0,&d3);
    printf("%d %d %d\n\r",d1,d2,d3);
    int d4 = findDistance(root,a1);
    int d5 = findDistance(root,a2);
    int d6 = findDistance(root,lc->data);
    printf("%d %d %d\n\r",d4,d5,d6);
    return (d1 + d2)-2*d3;
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
    struct node *lb = findLCA(root,3,5);
    printf("lca is %d\n\r",lb->data);
    printf("distance is %d\n\r",find_distance(root,3,5));
    return 0;
}
