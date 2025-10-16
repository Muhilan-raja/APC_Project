/*******************************************************************************************************************************************************************
*Title			: Multiplication
*Description		: This function performs multiplication of two given large numbers and store the result in the resultant list.
*Prototype		: int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
*Input Parameters	: head1: Pointer to the first node of the first double linked list.
			: tail1: Pointer to the last node of the first double linked list.
			: head2: Pointer to the first node of the second double linked list.
			: tail2: Pointer to the last node of the second double linked list.
			: headR: Pointer to the first node of the resultant double linked list.
			: tailR: Pointer to the last node of the resultant double linked list.
*Output			: Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/

#include "valid.h"

/* return 1 if list is NULL or all zeros */
static int list_is_zero(Dlist *head)
{
    if (head == NULL) return 1;
    for (Dlist *p = head; p != NULL; p = p->next) {
        if (p->data != 0) return 0;
    }
    return 1;
}

/* clear headR/tailR and set to single zero node */
static int make_zero_result(Dlist **headR, Dlist **tailR)
{
    if (headR == NULL || tailR == NULL) return FAILURE;
    deletelist(headR, tailR);
    if (insert_at_first(headR, tailR, 0) != SUCCESS) return FAILURE;
    return SUCCESS;
}

/* Multiplication routine */
int multiplication(Dlist **head1, Dlist **tail1,
                   Dlist **head2, Dlist **tail2,
                   Dlist **headR, Dlist **tailR)
{
    if (!head1 || !tail1 || !head2 || !tail2 || !headR || !tailR)
        return FAILURE;

    /* inputs must be non-empty lists */
    if (*head1 == NULL || *head2 == NULL)
        return FAILURE;

    /* if either operand is zero -> product zero */
    if (list_is_zero(*head1) || list_is_zero(*head2))
        return make_zero_result(headR, tailR);

    Dlist *acc_head = NULL, *acc_tail = NULL; /* accumulated sum of partials */
    Dlist *part_head = NULL, *part_tail = NULL; /* current partial product */
    Dlist *sum_head = NULL, *sum_tail = NULL; /* temporary sum */

    /* traverse multiplier from LSB (tail) to MSB (head) */
    Dlist *mult = *tail2;
    int shift = 0; /* number of zeros to append to current partial (10^shift) */

    while (mult != NULL) {
        /* clear any existing partial */
        deletelist(&part_head, &part_tail);

        int carry = 0;
        Dlist *mcand = *tail1; /* multiplicand traverse from LSB */

        while (mcand != NULL) {
            int a = (int)mcand->data;
            int b = (int)mult->data;
            int prod = a * b + carry;
            carry = prod / 10;
            int digit = prod % 10;

            /* build partial by inserting at first so list becomes MSB->LSB */
            if (insert_at_first(&part_head, &part_tail, digit) != SUCCESS) {
                deletelist(&part_head, &part_tail);
                deletelist(&acc_head, &acc_tail);
                return FAILURE;
            }

            mcand = mcand->prev;
        }

        if (carry) {
            if (insert_at_first(&part_head, &part_tail, carry) != SUCCESS) {
                deletelist(&part_head, &part_tail);
                deletelist(&acc_head, &acc_tail);
                return FAILURE;
            }
        }

        /* append 'shift' zeros at tail (multiply by 10^shift) */
        for (int i = 0; i < shift; ++i) {
            if (insert_at_last(&part_head, &part_tail, 0) != SUCCESS) {
                deletelist(&part_head, &part_tail);
                deletelist(&acc_head, &acc_tail);
                return FAILURE;
            }
        }

        /* if accumulator empty, move partial into accumulator */
        if (acc_head == NULL) {
            acc_head = part_head;
            acc_tail = part_tail;
            part_head = part_tail = NULL; /* ownership moved */
        } else {
            /* sum = acc + part -> sum_head */
            deletelist(&sum_head, &sum_tail); /* ensure clean */
            if (addition(&acc_head, &acc_tail, &part_head, &part_tail, &sum_head, &sum_tail) != SUCCESS) {
                deletelist(&part_head, &part_tail);
                deletelist(&acc_head, &acc_tail);
                deletelist(&sum_head, &sum_tail);
                return FAILURE;
            }

            /* free old acc and part (defensive) and adopt sum as new acc */
            deletelist(&acc_head, &acc_tail);
            deletelist(&part_head, &part_tail);

            acc_head = sum_head;
            acc_tail = sum_tail;
            sum_head = sum_tail = NULL;
        }

        shift++;
        mult = mult->prev;
    }

    /* final product in acc_head/acc_tail */
    *headR = acc_head;
    *tailR = acc_tail;

    /* cleanup temporaries (should be empty) */
    deletelist(&part_head, &part_tail);
    deletelist(&sum_head, &sum_tail);

    return SUCCESS;
}
