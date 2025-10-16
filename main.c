#include "valid.h"

int main(int argc, char *argv[])
{
    if (argc < 4) {
        errorprint();
        return 1;
    }

    char *sop1 = argv[1];
    char *sop2 = argv[3];
    char *sop  = argv[2];

    /* validate operands */
    if (isvalid(sop1) != SUCCESS) {
        errorprint();
        puts("Operand 1 is not a digit");
        return 1;
    }
    if (isvalid(sop2) != SUCCESS) {
        errorprint();
        puts("Operand 2 is not a digit");
        return 1;
    }

    /* Determine operator */
    char op = '\0';
    if (sop[0] != '\0') {
        op = sop[0];
        if (operator_check((char[]){op,'\0'}) != SUCCESS) {
            if (strchr(sop, '*') != NULL) op = '*';
        }
    }

    if (operator_check((char[]){op,'\0'}) != SUCCESS) {
        puts("Operators should be + - x X * /");
        return 1;
    }

    /* Build Dlist numbers (MSB at head) */
    Dlist *op1_head = NULL, *op1_tail = NULL;
    Dlist *op2_head = NULL, *op2_tail = NULL;
    Dlist *res_head = NULL, *res_tail = NULL;

    for (char *p = sop1; *p != '\0'; ++p)
        insert_at_last(&op1_head, &op1_tail, (*p - '0'));

    for (char *p = sop2; *p != '\0'; ++p)
        insert_at_last(&op2_head, &op2_tail, (*p - '0'));

    /* print input expression */
    printf("Expression: ");
    print_list(op1_head);
    printf(" %c ", op);
    print_list(op2_head);
    printf("\n");

    /* main operation switch */
    switch (op) {
        case '+':
            if (addition(&op1_head, &op1_tail, &op2_head, &op2_tail, &res_head, &res_tail) == SUCCESS) {
                printf("Result: ");
                print_list(res_head);
                printf("\n");
            } else {
                printf("Addition not possible\n");
            }
            break;

        case '-': {
            int cmp = compare(op1_head, op2_head);
            printf("Result: ");
            if (cmp == SMALLER) {
                if (subtraction(&op2_head, &op2_tail, &op1_head, &op1_tail, &res_head, &res_tail) == SUCCESS) {
                    printf("-");
                    print_list(res_head);
                    printf("\n");
                } else {
                    printf("Subtraction not possible\n");
                }
            } else {
                if (subtraction(&op1_head, &op1_tail, &op2_head, &op2_tail, &res_head, &res_tail) == SUCCESS) {
                    print_list(res_head);
                    printf("\n");
                } else {
                    printf("Subtraction not possible\n");
                }
            }
            break;
        }

        case 'x':
        case 'X':
        case '*':
            if (multiplication(&op1_head, &op1_tail, &op2_head, &op2_tail, &res_head, &res_tail) == SUCCESS) {
                printf("Result: ");
                print_list(res_head);
                printf("\n");
            } else {
                printf("Multiplication not possible\n");
            }
            break;

        case '/':
            if (division(&op1_head, &op1_tail, &op2_head, &op2_tail, &res_head, &res_tail) == SUCCESS) {
                printf("Quotient: ");
                print_list(res_head);
                printf("\n");
            } else {
                printf("Division failed\n");
            }
            break;

        default:
            printf("Invalid input. Try again\n");
            break;
    }

    /* cleanup all lists */
    deletelist(&op1_head, &op1_tail);
    deletelist(&op2_head, &op2_tail);
    deletelist(&res_head, &res_tail);

    return 0;
}
