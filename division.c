#include <stdio.h>
#include "apc.h"

int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2,Dlist **headR, Dlist **tailR)
{
    int count = 0;                     // Quotient counter
    Dlist *tempH = NULL, *tempT = NULL;

    // If dividend < divisor, result is 0
    if (list_compare(*head1, *head2) == 1)
    {
        insert_first(headR, tailR, 0);
        return SUCCESS;
    }

    // Repeated subtraction
    while (list_compare(*head1, *head2) != 1)
    {
        tempH = tempT = NULL;

        // temp = dividend - divisor
        subtraction(head1, tail1,
                    head2, tail2,
                    &tempH, &tempT);

        count++;                        // Increase quotient

        // Delete old dividend
        delete_list(head1, tail1);

        // Update dividend with result
        *head1 = tempH;
        *tail1 = tempT;
    }

    // Store quotient into result list
    if (count == 0)
    {
        insert_first(headR, tailR, 0);
    }
    else
    {
        while (count > 0)
        {
            insert_first(headR, tailR, count % 10);
            count /= 10;
        }
    }

    return SUCCESS;
}
