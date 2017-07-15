#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
    int data;
    struct Node *next;
};

/* Function to insert a node at the beginning */
void push(struct Node ** head_ref, int new_data)
{
    struct Node* new_node = 
        (struct Node*) malloc(sizeof(struct Node));
    new_node->data  = new_data;
    new_node->next = (*head_ref);
    (*head_ref)  = new_node;
}

/* Utility function to print a singly linked list */
void printList(struct Node *head)
{
    struct Node *temp = head;
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void reverseList (struct Node **head_ref) {
    struct Node *prev,*current,*next;
    prev = NULL;
    current = *head_ref;

    while (current) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head_ref = prev;
}

struct Node *mergeSorted(struct Node *a, struct Node *b) {
    struct Node *result;
    if(!a) return b;
    if(!b) return a;
    if(a->data < b->data) {
        result = a;
        result->next = mergeSorted(a->next,b);
    }
    else {
        result = b;
        result->next = mergeSorted(a,b->next);
    }
    return result;
}

void rotateList(struct Node **head_ref, int k) {
    if(NULL == head_ref) return;
    struct Node *tmp = *head_ref;
    struct Node *pt;
    int i = 1;
    for (i; i< k && tmp->next; ++i) {
        tmp = tmp->next;
    }
    if(tmp->next == NULL) return;
    pt = tmp;

    tmp = tmp->next;
    while (tmp->next ) tmp = tmp->next;

    tmp->next = *head_ref;

    *head_ref = pt->next;
    pt->next = NULL;
}

void printMiddle(struct Node **head_ref) {

    if (NULL == head_ref) return;
    struct Node *slow, *fast;
    slow = fast = *head_ref;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    printf("Middle %d\n\r",slow->data);
}

void swapNodes(struct Node **head_ref, int x, int y) {
    struct Node *currentX,*privX,*currentY,*privY;
    struct Node *x_node, *y_node;
    currentX = currentY = *head_ref;
    privX = privY = NULL;
    if(x == y)
        return;
    while(currentX && currentX->data != x){
        privX = currentX;
        currentX = currentX->next;
    }
    if(currentX == NULL)
        return;
    while(currentY && currentY->data != y) {
        privY = currentY;
        currentY = currentY->next;
    }
    if(currentY == NULL)
        return;
    
    if(privX) {
        privX->next = currentX->next;
    }
    if(privY) {
        privY->next = currentY->next;
    }
    if(privX==NULL) {
        privX = currentX->next;
        *head_ref = privX;
    }
    if(privY == NULL) {
        privY = currentY->next;
        *head_ref = privY;
    }
    currentX->next = NULL;
    currentY->next = NULL;

    if (privX && privX != *head_ref) {
        currentY->next = privX->next;
        privX->next = currentY;
    }
    if(privY && privY != *head_ref) {
        currentX->next = privY->next;
        privY->next = currentX;
    }
    if(privX == *head_ref) {
        currentY->next = privX;
        *head_ref = currentY;
    }
    else if(privY == *head_ref) {
        currentX->next = privY;
        *head_ref = currentX;
    }
}

int compareList(struct Node *a, struct Node *b) {
    if (a == NULL && b == NULL) return 1;
    if(a == NULL || b == NULL) return 0;
    if(a->data == b->data && compareList(a->next,b->next))
        return 1;
    else
        return 0;
}

void checkPalindrome(struct Node **head_ref) {
    struct Node *head = *head_ref;
    struct Node *middle,*slow_ptr, *fast_ptr, *priv_slow_ptr;
    slow_ptr = fast_ptr = *head_ref;
    middle = NULL;

    while (fast_ptr && fast_ptr->next) {
        priv_slow_ptr = slow_ptr;
        fast_ptr = fast_ptr->next->next;
        slow_ptr = slow_ptr->next;
    }

    if(fast_ptr != NULL) {
        middle = slow_ptr;
        slow_ptr = slow_ptr->next;
    }
    priv_slow_ptr->next = NULL;
    reverseList(&slow_ptr);

    int ret = compareList(head,slow_ptr);

    printf("Ret val %d\n\r",ret);
    reverseList(&slow_ptr);
    if(middle) {
        priv_slow_ptr->next = middle;
        middle->next = slow_ptr;
    }
    else {
        priv_slow_ptr->next = slow_ptr;
    }
    printList(head); 
}

void skipMdeleteN(struct Node  *head, int M, int N)
{
    struct Node *curr = head, *t;
    int count;

    while (curr)
    {
        for (count = 1; count<M && curr!= NULL; count++)
            curr = curr->next;


        if (curr == NULL)
            return;


        t = curr->next;
        for (count = 1; count<=N && t!= NULL; count++)
        {
            struct Node *temp = t;
            t = t->next;
            free(temp);
        }
        curr->next = t; // Link the previous list with remaining nodes


        curr = t;
    }
}

int main()
{
    struct Node *p = NULL, *q = NULL;
    push(&p, 3);
    push(&p, 2);
    push(&p, 1);
    push(&p, 2);
    push(&p, 3);
    printf("First Linked List:\n");
    printList(p);
    checkPalindrome(&p);

    push(&q, 8);
    push(&q, 7);
    push(&q, 6);
    push(&q, 5);
    push(&q, 4);
    printf("Second Linked List:\n");
    printList(q);
    struct Node *res = mergeSorted(p,q);
    printList(res);
    swapNodes(&res,1,7);
    printList(res);

    reverseList(&res);
    printList(res);

    rotateList(&res, 4);
    printList(res);
    printMiddle(&res);
    skipMdeleteN(res,2,2);
    printList(res);
}
