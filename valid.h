#ifndef VALID_H
#define VALID_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include<string.h>

/* Success / Failure codes */
#define SUCCESS 0
#define FAILURE 1

/* ---------------- Dlist node ---------------- */
typedef struct node
{
    struct node *prev;
    struct node *next;
    char data; /* store digit 0..9 as char for compatibility */
} Dlist;

/* Comparison return codes */
#define SMALLER  -1
#define EQUAL     0
#define GREATER   1

/* ---------------- Prototypes ---------------- */

/* Usage / errors */
void errorprint(void);

/* Validation helpers */
int is(char *op);            /* returns SUCCESS if non-empty digit-only string */
int isvalid(char *op);       /* allows leading + / - */

/* Operator check */
int operator_check(char argv[]);

/* List operations */
int insert_at_first(Dlist **head, Dlist **tail, int data);
int insert_at_last(Dlist **head, Dlist **tail, int data);
void deletelist(Dlist **head, Dlist **tail);
void copy_list(Dlist *src_head, Dlist **dest_head, Dlist **dest_tail);

/* Printing */
void print_list(Dlist *head);

/* Comparison / normalization */
int compare(Dlist *head1, Dlist *head2);
int remove_leading_zeros(Dlist **res_head);

/* Arithmetic prototypes (implemented elsewhere in your project) */
int addition(Dlist **head1, Dlist **tail1,
             Dlist **head2, Dlist **tail2,
             Dlist **headR, Dlist **tailR);

int subtraction(Dlist **head1, Dlist **tail1,
                Dlist **head2, Dlist **tail2,
                Dlist **res_head, Dlist **res_tail);

int multiplication(Dlist **head1, Dlist **tail1,
                   Dlist **head2, Dlist **tail2,
                   Dlist **headR, Dlist **tailR);

int division(Dlist **op1_head, Dlist **op1_tail,
             Dlist **op2_head, Dlist **op2_tail,
             Dlist **res_head, Dlist **res_tail);


#endif /* VALID_H */
