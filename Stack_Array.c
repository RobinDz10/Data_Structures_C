#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

#define MAX_SIZE 100
#define ERR INT_MIN

typedef struct StackList{
    int arr[MAX_SIZE];
    int top;
} Stack;

Stack* init(){
    Stack* st = (Stack*)malloc(sizeof(Stack));
    if(!st){
        printf("Insufficient memory.\n");
        return NULL;
    }
    memset(st->arr, ERR, sizeof(st->arr));
    st->top = -1;
    return st;
}

bool isEmpty(Stack* st){
    return -1 == st->top;
}

bool isFull(Stack* st){
    return MAX_SIZE - 1 == st->top;
}

void push(Stack* st, int value){
    if(isFull(st)){
        printf("The stack is full.\n");
        return;
    }
    st->arr[++st->top] = value;
    return;
}

int peek(Stack* st){
    if(isEmpty(st)){
        printf("The stack is empty.\n");
        return ERR;
    }
    return st->arr[st->top];
}

int pop(Stack* st){
    if(isEmpty(st)){
        printf("The stack is empty.\n");
        return ERR;
    }
    return st->arr[st->top--];
}

void printStack(Stack* st){
    if(isEmpty(st)){
        printf("The stack is empty.\n");
        return;
    }
    for(int i = st->top; i >= 0; --i){
        printf("%d ", st->arr[i]);
    }
    printf("\n");
    return;
}

void deleteStack(Stack* st){
    free(st);
    st = NULL;
    return;
}

int stackSize(Stack* st){
    return st->top + 1;
}

void test(){
    Stack* st = init();
    push(st, 1);
    push(st, 2);
    printf("%d\n", stackSize(st));
    push(st, 3);
    push(st, 4);
    push(st, 5);
    printf("%d\n", stackSize(st));
    printStack(st);
    pop(st);
    printf("%d\n", stackSize(st));
    printStack(st);
    printf("%d\n", peek(st));
    printf("%d\n", stackSize(st));
    pop(st);
    pop(st);
    pop(st);
    printf("%d\n", stackSize(st));
    printStack(st);
    printf("%d\n", pop(st));
    pop(st);
    pop(st);
    printf("%d\n", stackSize(st));
}

int main(){
    test();
    return 0;
}
