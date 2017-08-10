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
 
/* Function protoypes */
void printGivenLevel(struct node* root, int level);
int height(struct node* node);
struct node* newNode(int data);
 
/* Function to print level order traversal a tree*/
void printLevelOrder(struct node* root)
{
    int h = height(root);
    int i;
    for (i=1; i<=h; i++)
        printGivenLevel(root, i);
}
 
/* Print nodes at a given level */
void printGivenLevel(struct node* root, int level)
{
    if (root == NULL)
        return;
    if (level == 1)
        printf("%d ", root->data);
    else if (level > 1)
    {
        printGivenLevel(root->left, level-1);
        printGivenLevel(root->right, level-1);
    }
}
int areIdentical(struct node *t, struct node *s) {
    if(t == NULL && s == NULL) 
        return 1;
    if(t == NULL || s == NULL)
        return 0;
    if(t->data == s->data && areIdentical(t->left,s->left)&& areIdentical(t->right,s->right))
        return 1;
    return 0;
}

int isSubtree(struct node *t ,struct node *s) {
    if(s == NULL) return 1;
    if(t == NULL) return 0;
    if(areIdentical(t,s)) return 1;
    return (isSubtree(t->left,s)||isSubtree(t->right,s));
}
int count_leaf(struct node *root) {
    static int count = 0;
    if (root == NULL) return 0;
    if(root->left == NULL && root->right == NULL) count++;
    count_leaf(root->left);
    count_leaf(root->right);
    return count;
}
#if 0
void inorder_without_rec(struct node *root) {
    struct node *current = root;
    int done = 0;
    while (!done) {
        if(current != NULL) {
            /* push current to stack */
            current = current->left;
        }
        else {
            {/*stack is not empty*/
                /* pop from the stack */
                printf ("%d\n\r",current->data);
                current = current->right;
            }
            /* else */
            {
                done = 1;
            }
        }
    }
}
struct node *buildTree (char in[], char pre[], int start, int end) {
    if(start > end) return NULL;
    static int idx = 0;
    struct node *tnode = newNode(pre[idx++]);
    if(start == end) return tnode;
    int inidx = search (in,start,end,tnode->data);
    tnode->left = buildTree(in,pre,start,inidx-1);
    tnode->right = buildTree(in,pre,inidx+1,end);
    return tnode;
}
#endif

/* Compute the "height" of a tree -- the number of
    nodes along the longest path from the root node
    down to the farthest leaf node.*/
int height(struct node* node)
{
    if (node==NULL)
        return 0;
    else
    {
        /* compute the height of each subtree */
        int lheight = height(node->left);
        int rheight = height(node->right);
 
        /* use the larger one */
        if (lheight > rheight)
            return(lheight+1);
        else return(rheight+1);
    }
}

int size_tree(struct node* node) {
    if(node == NULL)return 0;
    int lsize = size_tree(node->left);
    int rsize = size_tree(node->right);
    return lsize+1+rsize;
}

void root_to_leaf(struct node *node,int path[],int len) {
    if(node == NULL)return;
    path[len++] = node->data;
    if(node->left == NULL && node->right == NULL) {
        int i = 0;
        for (;i<len;++i) {
            printf("%d ",path[i]);
        }
        printf("\n\r");
    }
    else {
        root_to_leaf(node->left,path,len);
        root_to_leaf(node->right,path,len);
    }
}

void print_ancestor(struct node *node, int key, int path[],int len) {
    if(node == NULL) return;
    path[len++] = node->data;
    if(node->data == key) {
        int i = 0;
        for (;i<len;++i) {
            printf("%d ",path[i]);
        }
    }
    else {
        print_ancestor(node->left,key,path,len);
        print_ancestor(node->right,key,path,len);
    }
}

struct node *findLCA(struct node *root,int n1,int n2) {
    if (root == NULL) return NULL;
    if(root->data == n1 || root->data == n2) return root;

    struct node *llca = findLCA(root->left,n1,n2);
    struct node *rlca = findLCA(root->right,n1,n2);
    if(llca && rlca) return root;
    if(llca == NULL) return rlca;
    else return llca;
}

 
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
 
/* Driver program to test above functions*/
int main()
{
    struct node *root = newNode(1);
    root->left        = newNode(2);
    root->right       = newNode(3);
    root->left->left  = newNode(4);
    root->left->right = newNode(5);
 
    printf("Level Order traversal of binary tree is \n");
    printLevelOrder(root);

    printf("Size %d\n\r",size_tree(root));
    int path[50];
    int len = 0;
    root_to_leaf(root,path,len);
    print_ancestor(root,5,path,len); 
    struct node *res = findLCA(root,4,5);
    printf("lca %d\n\r",res->data);
    int count  = count_leaf(root);
    printf("count is %d\n\r",count);
    return 0;
}
