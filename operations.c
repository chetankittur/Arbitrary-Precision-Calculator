#include <stdio.h>
#include <stdlib.h>
#include "apc.h"

// Insert a node at the end of the doubly linked list
int insert_last(Dlist **head, Dlist **tail, int data)
{
    // Allocate memory for new node
    Dlist *new = malloc(sizeof(Dlist));

    // Check for memory allocation failure
    if (new == NULL)
        return FAILURE;

    // Initialize new node data and pointers
    new->data = data;
    new->next = NULL;
    new->prev = NULL;

    // If list is empty
    if (*head == NULL && *tail == NULL)
    {
        *head = new;   // Set head to new node
        *tail = new;   // Set tail to new node
        return SUCCESS;
    }
    else
    {
        // Link new node at the end
        new->prev = *tail;
        (*tail)->next = new;
        *tail = new;   // Update tail
        return SUCCESS;
    }
}

// Insert a node at the beginning of the doubly linked list
int insert_first(Dlist **head, Dlist **tail, int data)
{
    // Allocate memory for new node
    Dlist *new = malloc(sizeof(Dlist));

    // Initialize new node data and pointers
    new->data = data;
    new->prev = NULL;
    new->next = NULL;

    // If list is empty
    if (*head == NULL && *tail == NULL)
    {
        *head = new;   // Set head to new node
        *tail = new;   // Set tail to new node
        return SUCCESS;
    }
    else
    {
        // Link new node at the beginning
        new->next = *head;
        (*head)->prev = new;
        *head = new;   // Update head
        return SUCCESS;
    }
}

// Print all digits stored in the linked list
void print_list(Dlist *head)
{
    // Traverse list from head to tail
    while (head)
    {
        printf("%d", head->data);  // Print digit
        head = head->next;         // Move to next node
    }
    printf("\n");                  // Print newline after number
}

// Convert command-line arguments into digit linked lists
void digit_to_list(Dlist **head1, Dlist **tail1,
                   Dlist **head2, Dlist **tail2,
                   char *argv[])
{
    // Get operand strings from argv
    char *num1 = argv[1];
    char *num2 = argv[3];

    // Skip sign character if present
    if (*num1 == '+' || *num1 == '-') 
    num1++;
    if (*num2 == '+' || *num2 == '-')
     num2++;

    // Insert digits of first number into list1
    for (int i = 0; num1[i] != '\0'; i++)
        insert_last(head1, tail1, num1[i] - '0');

    // Insert digits of second number into list2
    for (int i = 0; num2[i] != '\0'; i++)
        insert_last(head2, tail2, num2[i] - '0');
}

// Delete all nodes in a linked list
void delete_list(Dlist **head, Dlist **tail)
{
    Dlist *temp;

    // Traverse and free each node
    while (*head)
    {
        temp = *head;              // Store current node
        *head = (*head)->next;     // Move head forward
        free(temp);                // Free node
    }

    *tail = NULL;                  // Reset tail
}

// Compare two linked lists representing numbers
int list_compare(Dlist *head1, Dlist *head2)
{
    int list1_count = 0, list2_count = 0;
    Dlist *t1 = head1;
    Dlist *t2 = head2;

    // Count digits in list1
    while (t1)
    {
        list1_count++;
        t1 = t1->next;
    }

    // Count digits in list2
    while (t2)
    {
        list2_count++;
        t2 = t2->next;
    }

    // Step 1: Compare number of digits
    if (list1_count > list2_count)
        return 0;   // list1 > list2
    else if (list1_count < list2_count)
        return 1;   // list2 > list1

    // Step 2: Same length, compare digit by digit
    t1 = head1;
    t2 = head2;

    while (t1 && t2)
    {
        if (t1->data > t2->data)
            return 0;   // list1 > list2
        else if (t1->data < t2->data)
            return 1;   // list2 > list1

        t1 = t1->next;
        t2 = t2->next;
    }

    // Step 3: All digits are equal
    return 2;   // list1 == list2
}
