#include<stdio.h>
#include "apc.h"

int addition(Dlist **head1, Dlist **tail1,Dlist **head2, Dlist **tail2,Dlist **headR, Dlist **tailR)
{
    // Pointers to traverse list1 and list2 from the last node
    Dlist *temp1 = *tail1;
    Dlist *temp2 = *tail2;

    int data;        
    int carry = 0;     // Variable to store carry during addition

    // Loop until both lists are completely traversed
    while (temp1 || temp2)     
    {
        // Case 1: Both lists have digits
        if (temp1 && temp2)
        {
            data = temp1->data + temp2->data + carry;
        }
        // Case 2: Only list1 has digits
        else if (temp1 && temp2 == NULL)
        {
            data = temp1->data + carry;
        }
        // Case 3: Only list2 has digits
        else if (temp2 && temp1 == NULL)
        {
            data = temp2->data + carry;
        }

        // Check if carry is generated
        if (data > 9)
        {
            carry = data / 10;     // Update carry
            data = data % 10;      // Extract last digit
        }
        else
        {
            carry = 0;             // No carry
        }

        // Insert the result digit at the beginning of result list
        insert_first(headR, tailR, data);

        // Move pointer of list1 to previous node
        if (temp1)
            temp1 = temp1->prev;

        // Move pointer of list2 to previous node
        if (temp2)
            temp2 = temp2->prev;
    }

    // If carry remains after final addition
    if (carry)
        insert_first(headR, tailR, carry);
    return SUCCESS;
}
