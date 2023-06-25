#include <stdio.h>
#include <stdlib.h>

struct Node{
    struct Node* next;
    struct State* val;
};

// void printList(struct Node* current)
// {
//     while(current != NULL)
//     {
//         printf("%d -> ", current->val);
//         current = current->next;
//     }
//     printf("NULL\n");
// }

void push(struct Node** pp_head, struct State* v)
{
    struct Node* newNode  = (struct Node*)malloc(sizeof(struct Node)); //allocate space for the new node
    newNode->val = v; //set value
    if(*pp_head == NULL)  //if no head
        newNode->next = NULL; //newNode is head, set its next to null
    else
        newNode->next = *pp_head; //head exists, set new node's next to it
    
    *pp_head = newNode; //replace head with new node
}


struct State* pop(struct Node** pp_head){
    if(*pp_head == NULL)
    {
        printf("Stack Empty. Can't Pop.\n");
        return 0;
    }

    struct Node* p_popped = *pp_head;
    struct State* v = p_popped->val; //save val for return
    *pp_head = p_popped->next; //set head to one after
    free(p_popped);
    return v;
}

struct State* peek(struct Node* p_head){
    if(p_head == NULL)
    {
        printf("Stack Empty. Can't Peek.\n");
        return 0;
    }

    return p_head->val;
}