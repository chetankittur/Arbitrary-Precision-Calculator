
#include <stdio.h>
#include "apc.h"
int main(int argc, char *argv[])
{
    // Check for correct number of command line arguments
    if (argc != 4)
    {
        printf("Invalid Input\n");
        return 0;
    }

    // Declare doubly linked list pointers for operands and result
    Dlist *head1 = NULL, *tail1 = NULL;
    Dlist *head2 = NULL, *tail2 = NULL;
    Dlist *headR = NULL, *tailR = NULL;

    // Read operator from command line argument
    char op = argv[2][0];

    // Determine sign of first operand
    int sign1 = (argv[1][0] == '-') ? -1 : 1;

    // Determine sign of second operand
    int sign2 = (argv[3][0] == '-') ? -1 : 1;

    // Convert input numbers (without sign) into linked lists
    digit_to_list(&head1, &tail1, &head2, &tail2, argv);

    switch (op)
    {
        // ---------------- ADDITION ----------------
        case '+':
            // If both numbers have same sign
            if (sign1 == sign2)
            {
                // Perform addition
                addition(&head1, &tail1, &head2, &tail2, &headR, &tailR);

                // Print negative sign if both were negative
                if (sign1 == -1)
                    printf("-");
            }
            else
            {
                // Compare magnitudes of numbers
                int cmp = list_compare(head1, head2);

                // |num1| > |num2|
                if (cmp == 0)
                {
                    // Perform num1 - num2
                    subtraction(&head1, &tail1, &head2, &tail2, &headR, &tailR);

                    // Result sign follows num1
                    if (sign1 == -1)
                        printf("-");
                }
                else
                {
                    // Perform num2 - num1
                    subtraction(&head2, &tail2, &head1, &tail1, &headR, &tailR);

                    // Result sign follows num2
                    if (sign2 == -1)
                        printf("-");
                }
            }
            break;

        // ---------------- SUBTRACTION ----------------
        case '-':
            // If signs are different
            if (sign1 != sign2)
            {
                // Perform addition
                addition(&head1, &tail1, &head2, &tail2, &headR, &tailR);

                // Result sign follows first number
                if (sign1 == -1)
                    printf("-");
            }
            else
            {
                // Compare magnitudes of numbers
                int cmp = list_compare(head1, head2);

                // |num1| > |num2|
                if (cmp == 0)
                {
                    // Perform num1 - num2
                    subtraction(&head1, &tail1, &head2, &tail2, &headR, &tailR);

                    // Result sign follows first number
                    if (sign1 == -1)
                        printf("-");
                }
                else
                {
                    // Perform num2 - num1
                    subtraction(&head2, &tail2, &head1, &tail1, &headR, &tailR);

                    // Result becomes negative
                    if (sign1 == 1)
                        printf("-");
                }
            }
            break;

        // ---------------- MULTIPLICATION ----------------
        case 'x':
            // Perform multiplication
            multiplication(&head1, &tail1, &head2, &tail2, &headR, &tailR);

            // Print negative sign if result sign is negative and result is not zero
            if (sign1 * sign2 == -1 && !(headR->data == 0 && headR->next == NULL))
                printf("-");
            break;

        // ---------------- DIVISION ----------------
        case '/':
            // Perform division
            division(&head1, &tail1, &head2, &tail2, &headR, &tailR);

            // Print negative sign if result sign is negative and result is not zero
            if (sign1 * sign2 == -1 && !(headR->data == 0 && headR->next == NULL))
                printf("-");
            break;

        // Invalid operator case
        default:
            printf("Invalid Input\n");
            return 0;
    }
    // Print the final result stored in linked list
    print_list(headR);

    return 0;
}
