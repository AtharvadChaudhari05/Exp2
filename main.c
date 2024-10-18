

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX 100
// Stack data structure for operators
typedef struct {
    int top;
    char items[MAX];
} Stack;
// Function prototypes
void initStack(Stack *s);
int isEmpty(Stack *s);
int isFull(Stack *s);
void push(Stack *s, char c);
char pop(Stack *s);
char peek(Stack *s);
int precedence(char op);
void infixToPostfix(char *infix, char *postfix);
// Initialize stack
void initStack(Stack *s) {
    s->top = -1;
}
// Check if stack is empty
int isEmpty(Stack *s) {
    return s->top == -1;
}
// Check if stack is full
int isFull(Stack *s) {
    return s->top == MAX - 1;
}
// Push character onto stack
void push(Stack *s, char c) {
    if (!isFull(s)) {
        s->items[++s->top] = c;
    } else {
        printf("Stack is full\n");
        exit(EXIT_FAILURE);
    }
}
// Pop character from stack
char pop(Stack *s) {
    if (!isEmpty(s)) {
        return s->items[s->top--];
    } else {
        printf("Stack is empty\n");
        exit(EXIT_FAILURE);
    }
}
// Peek at top of stack
char peek(Stack *s) {
    if (!isEmpty(s)) {
        return s->items[s->top];
    } else {
        printf("Stack is empty\n");
        exit(EXIT_FAILURE);
    }
}
// Determine precedence of operators
int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}
// Convert infix expression to postfix expression
void infixToPostfix(char *infix, char *postfix) {
    Stack s;
    initStack(&s);
    int i = 0, k = 0;
    char c;
    while ((c = infix[i++]) != '\0') {
        if (c == ' ') continue; // Ignore spaces
        if (isalnum(c)) {
            postfix[k++] = c; // Add operand to postfix expression
        } else if (c == '(') {
            push(&s, c); // Push '(' onto stack
        } else if (c == ')') {
            while (!isEmpty(&s) && peek(&s) != '(') {
                postfix[k++] = pop(&s); // Pop until '(' is found
            }
            pop(&s); // Discard '('
        } else {
            while (!isEmpty(&s) && precedence(c) <= precedence(peek(&s))) {
                postfix[k++] = pop(&s); // Pop operators with higher or equal precedence
            }
            push(&s, c); // Push current operator onto stack
        }
    }
    // Pop remaining operators in stack
    while (!isEmpty(&s)) {
        postfix[k++] = pop(&s);
    }
    postfix[k] = '\0'; // Null-terminate the postfix expression
}
int main() {
    char infix[MAX], postfix[MAX];
    printf("Enter infix expression: ");
    fgets(infix, MAX, stdin);
    // Remove trailing newline character from input
    size_t len = strlen(infix);
    if (len > 0 && infix[len - 1] == '\n') {
        infix[len - 1] = '\0';
    }
    infixToPostfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);
    return 0;
}





