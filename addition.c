/*******************************************************************************************************************************************************************
*Title			: Addition
*Description		: This function performs addition of two given large numbers and store the result in the resultant list.
*Prototype		: int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
*Input Parameters	: head1: Pointer to the first node of the first double linked list.
			: tail1: Pointer to the last node of the first double linked list.
			: head2: Pointer to the first node of the second double linked list.
			: tail2: Pointer to the last node of the second double linked list.
			: headR: Pointer to the first node of the resultant double linked list.
			: tailR: Pointer to the last node of the resultant double linked list.
*Output			: Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/
#include "valid.h"

int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    int carry = 0, data = 0;
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
        if(!new) 
        return FAILURE;

        new->next = NULL;
        new->prev = NULL;

        data = carry + op1 + op2;

        if(data >= 10)
        {
            carry = 1;
            new->data = data % 10;
        }
        else
        {
            carry = 0;
            new->data = data;
        }

        if(*tailR == NULL && *headR == NULL)
        {
            *tailR = new;
            *headR = new;
        }
        else
        {
            new->next = *headR;
            (*headR)->prev = new;
            *headR = new;
        }

        if(*tail1 != NULL)
            *tail1 = (*tail1)->prev;

        if(*tail2 != NULL)
            *tail2 = (*tail2)->prev;
    }

    if(carry)
    {
        Dlist *new = malloc(sizeof(Dlist));
        if(!new) 
        return FAILURE;
        new->next = *headR;
        new->prev = NULL;
        new->data = 1;

        if(*headR)
        {
            (*headR)->prev = new;
            *headR = new;
        }
        else
            *tailR = new;
    }

    return SUCCESS;
}
