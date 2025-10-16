#include "valid.h"

void errorprint(void)
{
    puts("Argument should be : ");
    puts("./apc.exc <operand 1> <operator> <operand 2>");
}

int is(char *op)
{
    if (op == NULL) 
    return FAILURE;
    
    if (*op == '\0') 
    return FAILURE;

    while (*op != '\0')
    {
        if (!isdigit((unsigned char)*op))
            return FAILURE;
        op++;
    }
    return SUCCESS;
}

/* isvalid: allow optional leading '+' or '-' then digits */
int isvalid(char *op)
{
    if (op == NULL) 
    return FAILURE;

    if (*op == '+' || *op == '-')
        op++;

    if (*op == '\0') /* string was only sign */
        return FAILURE;

    while (*op != '\0')
    {
        if (!isdigit((unsigned char)*op))
            return FAILURE;
        op++;
    }
    return SUCCESS;
}

/* Check operator: accepted single-character operators: + - x X * / */
int operator_check(char argv[])
{
    if (argv == NULL) 
    return FAILURE;

    if (argv[0] == '\0') 
    return FAILURE;

    /* require single-character string */
    if (argv[1] != '\0') 
    return FAILURE;

    if (argv[0] == '+' || argv[0] == '-' || argv[0] == 'x' ||
        argv[0] == 'X' || argv[0] == '*' || argv[0] == '/')
        return SUCCESS;

    return FAILURE;
}

/* Delete all nodes in the list and reset head & tail pointers */
void deletelist(Dlist **head, Dlist **tail)
{
    if (head == NULL || tail == NULL)
        return;

    if (*head == NULL)
    {
        *tail = NULL;
        return;
    }

    Dlist *temp = *head;
    while (temp)
    {
        Dlist *next = temp->next;
        free(temp);
        temp = next;
    }

    *head = NULL;
    *tail = NULL;
}

/* Copy src list into dest (append using insert_at_last) */
void copy_list(Dlist *src_head, Dlist **dest_head, Dlist **dest_tail)
{
    Dlist *temp = src_head;
    while (temp)
    {
        insert_at_last(dest_head, dest_tail, temp->data);
        temp = temp->next;
    }
}

/* Insert a node at the tail of the doubly-linked list */
int insert_at_last(Dlist **head, Dlist **tail, int data)
{
    if (head == NULL || tail == NULL)
        return FAILURE;

    Dlist *new = malloc(sizeof *new);
    if (!new) 
    return FAILURE;

    new->data = (char)data;
    new->prev = NULL;
    new->next = NULL;

    if (*head == NULL && *tail == NULL)
    {
        *head = new;
        *tail = new;
    }
    else
    {
        (*tail)->next = new;
        new->prev = *tail;
        *tail = new;
    }

    return SUCCESS;
}

/* Insert a node at the head of the doubly-linked list */
int insert_at_first(Dlist **head, Dlist **tail, int data)
{
    if (head == NULL || tail == NULL)
        return FAILURE;

    Dlist *new = malloc(sizeof *new);
    if (!new) 
    return FAILURE;

    new->data = (char)data;
    new->prev = NULL;
    new->next = NULL;

    if (*head == NULL)
    {
        *head = new;
        *tail = new;
    }
    else
    {
        (*head)->prev = new;
        new->next = *head;
        *head = new;
    }

    return SUCCESS;
}

/* Print number as a continuous digit sequence (no arrows). Prints INFO when empty. */
void print_list(Dlist *head)
{
    if (head == NULL)
    {
        printf("INFO : List is empty\n");
        return;
    }

    while (head)
    {
        printf("%d", head->data);
        head = head->next;
    }
}

/* Compare two Dlist numbers (MSB at head). Return SMALLER/EQUAL/GREATER.
   This implementation compares lengths first then digits. */
int compare(Dlist *head1, Dlist *head2)
{
    /* handle NULL pointers as zero-length */
    if (head1 == NULL && head2 == NULL) 
    return EQUAL;

    if (head1 == NULL) {
        Dlist *t = head2;
        while (t) 
        { 
            if (t->data != 0) 
            return SMALLER; t = t->next; 
        }
        return EQUAL;
    }
    if (head2 == NULL) {
        Dlist *t = head1;
        while (t) 
        { 
            if (t->data != 0) 
            return GREATER; t = t->next; 
        }
        return EQUAL;
    }

    /* compute lengths */
    int len1 = 0, len2 = 0;
    Dlist *t1 = head1, *t2 = head2;
    while (t1) 
    { 
        len1++; t1 = t1->next;
    }
    while (t2) 
    {
         len2++; t2 = t2->next;
    }

    if (len1 > len2) 
    return GREATER;
    if (len1 < len2) 
    return SMALLER;

    /* same lengths: compare digit by digit */
    while (head1 && head2)
    {
        if (head1->data > head2->data) 
        return GREATER;
        if (head1->data < head2->data) 
        return SMALLER;
        head1 = head1->next;
        head2 = head2->next;
    }
    return EQUAL;
}

/* Remove leading zeros but keep one zero node if the number is zero.
   Returns SUCCESS (always) or FAILURE for invalid args. */
int remove_leading_zeros(Dlist **res_head)
{
    if (res_head == NULL) 
        return FAILURE;

    while (*res_head && (*res_head)->data == 0 && (*res_head)->next != NULL)
    {
        Dlist *temp = *res_head;
        *res_head = (*res_head)->next;
        (*res_head)->prev = NULL;
        free(temp);
    }
    return SUCCESS;
}