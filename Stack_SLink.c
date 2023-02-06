#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_SIZE 100
#define ERR INT_MIN

typedef struct StackNode{
    int data;
    struct StackNode* prev;
} SNode;

typedef struct{
    SNode* top;
    int size;
} Stack;

Stack* init(){
    Stack* st = (Stack*)malloc(sizeof(Stack));
    if(!st){
        printf("Insufficient memory.\n");
        return NULL;
    }
    st->top = NULL;
    st->size = 0;
}

bool isEmpty(Stack* st){
    return 0 == st->size;
}

bool isFull(Stack* st){
    return MAX_SIZE == st->size;
}

void push(Stack* st, int val){
    if(isFull(st)){
        printf("Stack is full.\n");
        return;
    }
    SNode* node = (SNode*)malloc(sizeof(SNode));
    if(!node){
        printf("Insufficient memory.\n");
        return;
    }
    node->data = val;
    node->prev = NULL;
    if(NULL == st->top){
        st->top = node;
    }
    else{
        node->prev = st->top;
        st->top = node;
    }
    st->size++;
    return;
}

int peek(Stack* st){
    if(isEmpty(st)){
        printf("Stack is empty.\n");
        return ERR;
    }
    return st->top->data;
}

int pop(Stack* st){
    if(isEmpty(st)){
        printf("Stack is empty.\n");
        return ERR;
    }
    SNode* temp = st->top;
    int res = temp->data;
    if(temp->prev)
        st->top = temp->prev;
    else
        st->top = NULL;
    st->size--;
    free(temp);
    temp = NULL;
    return res;
}

void printStack(Stack* st){
    if(isEmpty(st)){
        printf("Stack is empty.\n");
        return;
    }
    SNode* temp = st->top;
    while(temp){
        printf("%d ", temp->data);
        temp = temp->prev;
    }
    printf("\n");
    return;
}

void deleteStack(Stack* st){
    SNode* temp = NULL;
    while(st->top){
        temp = st->top;
        st->top = st->top->prev;
        free(temp);
        temp = NULL;
    }
    return;
}

void test(){
    Stack* st = init();
    push(st, 1);
    push(st, 2);
    printf("%d\n", st->size);
    push(st, 3);
    push(st, 4);
    push(st, 5);
    printf("%d\n", st->size);
    printStack(st);
    pop(st);
    printf("%d\n", st->size);
    printStack(st);
    printf("%d\n", peek(st));
    printf("%d\n", st->size);
    pop(st);
    pop(st);
    pop(st);
    printf("%d\n", st->size);
    printStack(st);
    printf("%d\n", pop(st));
    pop(st);
    pop(st);
    printf("%d\n", st->size);
}

int main(){
    test();
    return 0;
}
