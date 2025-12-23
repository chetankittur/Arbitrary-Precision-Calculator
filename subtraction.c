#include "apc.h"
#include<stdio.h>
#include<stdlib.h>

int subtraction(Dlist **head1, Dlist **tail1,
                Dlist **head2, Dlist **tail2,
                Dlist **headR, Dlist **tailR)
{
    // Compare magnitudes of list1 and list2
    int cmp = list_compare(*head1, *head2);

    // If both numbers are equal, result is 0
    if (cmp == 2)
    {
        insert_first(headR, tailR, 0);   // Insert 0 as result
        return SUCCESS; 
    }

    // Pointers to decide which list is bigger
    Dlist *list1_head, *list1_tail;
    Dlist *list2_head, *list2_tail;

    // If list1 > list2, subtract list2 from list1
    if (cmp == 0)
    {
        list1_head = *head1;   // Larger number head
        list1_tail = *tail1;   // Larger number tail

        list2_head = *head2;   // Smaller number head
        list2_tail = *tail2;   // Smaller number tail
    }
    else
    {
        // If list1 < list2, reverse subtraction
        // Sign handling is done in main / division
        list1_head = *head2;   // Larger number head
        list1_tail = *tail2;   // Larger number tail

        list2_head = *head1;   // Smaller number head
        list2_tail = *tail1;   // Smaller number tail
    }

    // Start subtraction from least significant digit
    Dlist *t1 = list1_tail;
    Dlist *t2 = list2_tail;

    int borrow = 0;   // Borrow flag
    int val;          // Store subtraction result digit

    // Initialize result list
    *headR = NULL;
    *tailR = NULL;

    // Traverse till all digits of larger number are processed
    while (t1)
    {
        int d1 = t1->data - borrow;     // Current digit of minuend
        int d2 = (t2 ? t2->data : 0);   // Current digit of subtrahend

        // If borrowing is required
        if (d1 < d2)
        {
            d1 += 10;      // Borrow from next higher digit
            borrow = 1;    // Set borrow
        }
        else
        {
            borrow = 0;    // No borrow needed
        }

        val = d1 - d2;     // Subtract digits

        // Insert result digit at beginning
        insert_first(headR, tailR, val);

        // Move to previous digit
        t1 = t1->prev;
        if (t2) 
            t2 = t2->prev;
    }

    // Remove leading zeros from result
    while ((*headR)->data == 0 && (*headR)->next != NULL)
    {
        Dlist *tmp = *headR;        // Node to be deleted
        *headR = (*headR)->next;    // Move head forward
        (*headR)->prev = NULL;      // Update previous pointer
        free(tmp);                  // Free removed node
    }

    
    return SUCCESS;   
}
