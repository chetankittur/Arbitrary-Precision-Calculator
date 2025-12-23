/*Name: Chetan Kittur
  Date: 18/12/2025
  Project Title: Arbitrary Precision Calculator
  Description: The Arbitrary Precision Calculator (APC) is a command-line based application developed in the C programming 
               language to perform arithmetic operations on integers of unlimited size. Unlike conventional calculators that 
               are restricted by fixed-size data types, this project overcomes such limitations by representing numbers as doubly 
               linked lists, where each node stores a single digit. This design allows the calculator to efficiently handle very
                large positive and negative integers. The project supports core arithmetic operations such as addition, 
                subtraction, multiplication, and division, with complete sign management and correct handling of edge cases like
                zero and unequal operand lengths. Each operation is implemented using fundamental arithmetic principles,
                including carry propagation in addition, borrow handling in subtraction, partial product generation in
                multiplication, and repeated subtraction for division. The application accepts input through command-line
                arguments, ensuring flexibility and ease of use. This project highlights practical applications of data 
                structures, dynamic memory allocation, modular programming, and algorithmic problem-solving in C, making 
                it a robust and scalable solution for high-precision numerical computation.
 */
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
