#ifndef APC_H
#define APC_H

// Macro for success return value
#define SUCCESS 0

// Macro for failure return value
#define FAILURE -1

// Structure definition for doubly linked list node
typedef struct node
{
    struct node *prev;   // Pointer to previous node
    int data;            // Digit stored in the node
    struct node *next;   // Pointer to next node
} Dlist;

// -------- Function Prototypes --------

// Convert command-line operands into linked lists (digits only)
void digit_to_list(Dlist **head1, Dlist **tail1,
                   Dlist **head2, Dlist **tail2,
                   char *argv[]);

// Insert a node at the beginning of the linked list
int insert_first(Dlist **head, Dlist **tail, int data);

// Insert a node at the end of the linked list
int insert_last(Dlist **head, Dlist **tail, int data);

// Print the number stored in the linked list
void print_list(Dlist *head);

// Delete all nodes in a linked list
void delete_list(Dlist **head, Dlist **tail);

// Compare two linked lists 
int list_compare(Dlist *head1, Dlist *head2);

// Perform addition of two numbers using linked lists
int addition(Dlist **head1, Dlist **tail1,Dlist **head2, Dlist **tail2,Dlist **headR, Dlist **tailR);

// Perform subtraction of two numbers using linked lists
int subtraction(Dlist **head1, Dlist **tail1,Dlist **head2, Dlist **tail2,Dlist **headR, Dlist **tailR);

// Perform multiplication of two numbers using linked lists
int multiplication(Dlist **head1, Dlist **tail1,Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);

// Perform division of two numbers using linked lists
int division(Dlist **head1, Dlist **tail1,Dlist **head2, Dlist **tail2,Dlist **headR, Dlist **tailR);

#endif
