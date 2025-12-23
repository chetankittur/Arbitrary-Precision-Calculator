#include "apc.h"
#include<stdio.h>
#include<stdlib.h>

int multiplication(Dlist **head1, Dlist **tail1,Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    // Pointer to traverse first number from least significant digit
    Dlist *t1 = *tail1;

    // Counter to track position for adding trailing zeros
    int count = 0;

    // Final result list (LISTR)
    Dlist *listRH = NULL, *listRT = NULL;

    // Loop through each digit of first number
    while (t1)
    {
        int carry = 0;     // Carry generated during multiplication
        int mul = 0;       // Store multiplication result

        // Partial result list for current digit (LISTR1)
        Dlist *listR1H = NULL, *listR1T = NULL;

        // Pointer to traverse second number from least significant digit
        Dlist *t2 = *tail2;

        // Multiply current digit of list1 with entire list2
        while (t2)
        {
            mul = t1->data * t2->data + carry; // Multiply digits and add carry
            carry = mul / 10;                  // Update carry
            mul = mul % 10;                    // Extract digit

            // Insert digit at beginning of partial result
            insert_first(&listR1H, &listR1T, mul);

            // Move to next digit of list2
            t2 = t2->prev;
        }

        // Insert remaining carry if any
        if (carry)
            insert_first(&listR1H, &listR1T, carry);

        // Append zeros based on current digit position
        for (int i = 0; i < count; i++)
            insert_last(&listR1H, &listR1T, 0);

        // Temporary list to store addition result (LISTR2)
        Dlist *listR2H = NULL, *listR2T = NULL;

        // Add current result with partial result
        addition(&listRH, &listRT,
                 &listR1H, &listR1T,
                 &listR2H, &listR2T);

        // Update final result list
        listRH = listR2H;
        listRT = listR2T;

        // Move to next digit of first number
        count++;
        t1 = t1->prev;
    }

    // Assign final multiplication result
    *headR = listRH;
    *tailR = listRT;

    // Remove leading zeros from result
    while (*headR && (*headR)->data == 0 && (*headR)->next)
    {
        Dlist *temp = *headR;        // Store node to be deleted
        *headR = (*headR)->next;     // Move head forward
        (*headR)->prev = NULL;       // Update previous pointer
        free(temp);                  // Free removed node
    }

    // Return success status
    return SUCCESS;
}
