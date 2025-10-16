APC PROJECT – ARBITRARY PRECISION CALCULATOR

This project performs arithmetic operations on large numbers that cannot be handled by normal C data types.
Each digit of the number is stored in a doubly linked list, allowing the program to handle numbers of any length accurately.

Features:
- Supports Addition (+), Subtraction (-), Multiplication (* or x), and Division (/)
- Works with numbers larger than long long int
- Uses doubly linked lists for storing and processing digits
- Detects invalid input and division by zero
- Displays clean and simple results

Files Used:
main.c              – Handles user input, operation selection, and output
addition.c          – Implements large number addition
subtraction.c       – Handles subtraction with borrow logic
multiplication.c    – Performs long multiplication
division.c          – Implements long division algorithm
valid.c / valid.h   – Contains validation, helper functions, and list operations

Compilation:
gcc *.c -o apc

Execution:
./apc <operand1> <operator> <operand2>

Examples:
./apc 999999999999 + 1
Expression: 999999999999 + 1
Result: 1000000000000

./apc 125 / 5
Expression: 125 / 5
Quotient: 25

./apc 12345 - 6789
Expression: 12345 - 6789
Result: 5556

Notes:
- Supported operators: +  -  *  /  x  X
- Input format: <operand1> <operator> <operand2>
- Negative results are displayed with a minus sign (-)
- Division is only performed if divisor is non-zero
