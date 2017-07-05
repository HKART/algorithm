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


int main()
{
    struct Node *p = NULL, *q = NULL;
    push(&p, 3);
    push(&p, 2);
    push(&p, 1);
    printf("First Linked List:\n");
    printList(p);

    push(&q, 8);
    push(&q, 7);
    push(&q, 6);
    push(&q, 5);
    push(&q, 4);
    printf("Second Linked List:\n");
    printList(q);
    struct Node *res = mergeSorted(p,q);
    printList(res);

    reverseList(&res);
    printList(res);

    rotateList(&res, 4);
    printList(res);
    printMiddle(&res);
}
