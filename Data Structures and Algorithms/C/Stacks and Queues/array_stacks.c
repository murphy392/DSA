#include <stdio.h>
#include <stdlib.h>

/**
    LIFO methodology
    Stacks are dynamic and size and can grow and shrink dynamically

    When not to use: 
        Uses extra memory: each element must contain the address to the next elelment 
        Readability: The code might be hard to read and write
*/

typedef struct {
    int *stack;
    int top;
    int capacity;
} Stack;

Stack* createStack(int capacity) {
    Stack *newStack = (Stack*)malloc(sizeof(Stack));
    newStack->stack = (int*)malloc(capacity * sizeof(int));
    newStack->top = -1;
    newStack->capacity = capacity;
    return newStack;
}

void push(Stack *s, int element){
    if (s->top == s->capacity -1 ) {
        printf("Stack is full\n");
        return;
    }
    s->stack[++s->top] = element;
}

int pop(Stack *s) {
    if (s->top == -1){
        printf("Stack is empty\n");
        return -1;
    }
    return s->stack[s->top--];
}

int peek(Stack *s){
    if (s->top == -1){
        printf("Stack is empty\n");
        return -1;
    }
    return s->stack[s->top];
}

int isEmpty(Stack *s){
    return s->top == -1;
}

int size(Stack *s) {
    return s->top + 1;
}

void printStack(Stack *s){
    printf("Stack: ");
    for (int i = 0; i <= s->top; ++i){
        printf("%c ", s->stack[i]);
    }
    printf("\n");
}

int main(void){
    Stack *myStack = createStack(100);

    push(myStack, 'A');
    push(myStack, 'B');
    push(myStack, 'C');

    // Print initial stack
    printStack(myStack);

    printf("Pop: %c\n", pop(myStack));
    printf("Peek: %c\n", peek(myStack));
    printf("isEmpty: %d\n", isEmpty(myStack)); // 0 = false, 1 = true
    printf("Size: %d\n", size(myStack));

    return 0;
}