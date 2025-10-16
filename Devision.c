/*******************************************************************************************************************************************************************
*Title           : Division
*Description     : This function performs division of two given large numbers represented as doubly linked lists.
                   It implements the long division algorithm and stores the quotient in the resultant list.
*Prototype       : int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
*Input Parameters: head1 : Pointer to the first node of the dividend list.
                   tail1 : Pointer to the last node of the dividend list.
                   head2 : Pointer to the first node of the divisor list.
                   tail2 : Pointer to the last node of the divisor list.
                   headR : Pointer to the first node of the quotient list (result).
                   tailR : Pointer to the last node of the quotient list (result).
*Output          : Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/

#include "valid.h"   // your project’s header

int division(Dlist **head1, Dlist **tail1,
             Dlist **head2, Dlist **tail2,
             Dlist **headR, Dlist **tailR)
{
    // Division by zero check
    if ((*head2)->data == 0 && (*head2)->next == NULL)
    {
        printf("Error: Division by zero.\n");
        return FAILURE;
    }

    // If dividend < divisor, quotient = 0
    if (compare(*head1, *head2) < 0)
    {
        insert_at_last(headR, tailR, 0);
        return SUCCESS;
    }

    Dlist *dividend = *head1;
    Dlist *temp_h = NULL, *temp_t = NULL;   // Temporary portion of dividend
    Dlist *rem_h = NULL, *rem_t = NULL;     // Remainder after subtraction
    int count;

    // Long division loop
    while (dividend)
    {
        // Bring down next digit from dividend
        insert_at_last(&temp_h, &temp_t, dividend->data);
        dividend = dividend->next;

        // Remove leading zeros
        remove_leading_zeros(&temp_h);

        // If current portion smaller than divisor, quotient digit = 0
        if (compare(temp_h, *head2) < 0)
        {
            insert_at_last(headR, tailR, 0);
            continue;
        }

        // Find how many times divisor fits into temp_h
        count = 0;
        while (compare(temp_h, *head2) >= 0)
        {
            // Make a copy of divisor to avoid pointer corruption
            Dlist *div_copy_h = NULL, *div_copy_t = NULL;
            copy_list(*head2, &div_copy_h, &div_copy_t);

            // Subtract divisor from current part
            subtraction(&temp_h, &temp_t, &div_copy_h, &div_copy_t, &rem_h, &rem_t);

            // Clean up temporary lists
            deletelist(&temp_h, &temp_t);
            deletelist(&div_copy_h, &div_copy_t);

            // Update temp_h with remainder
            temp_h = rem_h;
            temp_t = rem_t;
            rem_h = rem_t = NULL;

            count++;
        }

        // Add quotient digit
        insert_at_last(headR, tailR, count);
    }

    // Remove leading zeros from final quotient
    remove_leading_zeros(headR);

    // Free remaining temp
    deletelist(&temp_h, &temp_t);

    return SUCCESS;
}
