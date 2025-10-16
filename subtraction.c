/*******************************************************************************************************************************************************************
*Title			: Subtraction
*Description		: This function performs subtraction of two given large numbers and store the result in the resultant list.
*Prototype		: int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
*Input Parameters	: head1: Pointer to the first node of the first double linked list.
			: tail1: Pointer to the last node of the first double linked list.
			: head2: Pointer to the first node of the second double linked list.
			: tail2: Pointer to the last node of the second double linked list.
			: headR: Pointer to the first node of the resultant double linked list.
			: tailR: Pointer to the last node of the resultant double linked list.
*Output			: Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/

#include "valid.h"

int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **res_head, Dlist **res_tail)
{
    int borrow = 0, data = 0;
    int op1;
    int op2;

    while(*tail1 != NULL || *tail2 != NULL)
    {
        if(*tail1 == NULL)
            op1 = 0;
        else
            op1 = (*tail1)->data;

        if(*tail2 == NULL)
            op2 = 0;
        else
            op2 = (*tail2)->data;

        Dlist *new = malloc(sizeof(Dlist));
        if(!new) return FAILURE;

        new->next = NULL;
        new->prev = NULL;

        if(borrow)
            --op1;

        if(op1 < op2)
        {
            new->data = (10 + op1) - op2;
            borrow = 1;
        }
        else
        {
            new->data = op1 - op2;
            borrow = 0;
        }

        if(*res_head == NULL)
        {
            *res_head = new;
            *res_tail = new;
        }
        else
        {
            (*res_head)->prev = new;
            new->next = *res_head;
            *res_head = new;
        }

        if(*tail1 != NULL)
            *tail1 = (*tail1)->prev;

        if(*tail2 != NULL)
            *tail2 = (*tail2)->prev;
    }

    while (*res_head && (*res_head)->data == 0 && (*res_head)->next != NULL)
    {
        Dlist *temp = *res_head;
        if(!temp) return FAILURE;
        *res_head = (*res_head)->next;
        (*res_head)->prev = NULL;
        free(temp);
    }

    return SUCCESS;
}
