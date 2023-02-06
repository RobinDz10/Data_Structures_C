#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_SIZE 10
#define ERR INT_MIN

typedef struct DequeNode{
    int data;
    struct DequeNode* prev;
    struct DequeNode* next;
} DQNode;

typedef struct{
    int size;
    DQNode* front;
    DQNode* rear;
} DQ;

DQ* init(){
    DQ* dq = (DQ*)malloc(sizeof(DQ));
    if(!dq){
        printf("Insufficient memory to initialize a deque.\n");
        return NULL;
    }
    dq->size = 0;
    dq->front = NULL;
    dq->rear = NULL;
    return dq;
}

bool isFull(DQ* dq){
    if(!dq){
        printf("The deque has not been initialized.\n");
        return NULL;
    }
    return MAX_SIZE == dq->size;
}

bool isEmpty(DQ* dq){
    if(!dq){
        printf("The deque has not been initialized.\n");
        return NULL;
    }
    return 0 == dq->size;
}

void push_front(DQ* dq, int val){
    if(!dq){
        printf("The deque has not been initialized.\n");
        return;
    }
    if(isFull(dq)){
        printf("The deque is full.\n");
        return;
    }
    DQNode* node = (DQNode*)malloc(sizeof(DQNode));
    if(!node){
        printf("Insufficient memory to initialize a new deque node.\n");
        return;
    }
    node->data = val;
    node->next = NULL;
    node->prev = NULL;
    if(NULL == dq->front)
        dq->front = node;
    else{
        dq->front->prev = node;
        node->next = dq->front;
        dq->front = node;
    }
    if(NULL == dq->rear)
        dq->rear = node;
    dq->size++;
    return;
}

void push_back(DQ* dq, int val){
    if(!dq){
        printf("The deque has not been initialized.\n");
        return;
    }
    if(isFull(dq)){
        printf("The deque is full.\n");
        return;
    }
    DQNode* node = (DQNode*)malloc(sizeof(DQNode));
    if(!node){
        printf("Insufficient memory to initialize a new deque node.\n");
        return;
    }
    node->data = val;
    node->next = NULL;
    node->prev = NULL;
    if(NULL == dq->front)
        dq->front = node;
    if(NULL == dq->rear)
        dq->rear = node;
    else{
        dq->rear->next = node;
        node->prev = dq->rear;
        dq->rear = node;
    }
    dq->size++;
    return;
}

int peek_front(DQ* dq){
    if(!dq){
        printf("The deque has not been initialized.\n");
        return ERR;
    }
    if(isEmpty(dq)){
        printf("The deque is empty.\n");
        return ERR;
    }
    return dq->front->data;
}

int peek_rear(DQ* dq){
    if(!dq){
        printf("The deque has not been initialized.\n");
        return ERR;
    }
    if(isEmpty(dq)){
        printf("The deque is empty.\n");
        return ERR;
    }
    return dq->rear->data;
}

int pop_front(DQ* dq){
    if(!dq){
        printf("The deque has not been initialized.\n");
        return ERR;
    }
    if(isEmpty(dq)){
        printf("The deque is empty.\n");
        return ERR;
    }
    DQNode* temp = dq->front;
    int val = temp->data;
    if(NULL == dq->front->next){
        dq->front = NULL;
        dq->rear = NULL;
    }
    else{
        DQNode* tempNext = temp->next;
        dq->front = temp->next;
        dq->front->prev = NULL;
    }
    free(temp);
    temp = NULL;
    dq->size--;
    return val;
}

int pop_back(DQ* dq){
    if(!dq){
        printf("The deque has not been initialized.\n");
        return ERR;
    }
    if(isEmpty(dq)){
        printf("The deque is empty.\n");
        return ERR;
    }
    DQNode* temp = dq->rear;
    int val = temp->data;
    if(NULL == dq->rear->prev){
        dq->front = NULL;
        dq->rear = NULL;
    }
    else{
        DQNode* tempPrev = temp->prev;
        dq->rear = tempPrev;
        dq->rear->next = NULL;
    }
    free(temp);
    temp = NULL;
    dq->size--;
    return val;
}

void printDequeFromFront(DQ* dq){
    if(!dq){
        printf("The deque has not been initialized.\n");
        return;
    }
    if(isEmpty(dq)){
        printf("The deque is empty.\n");
        return;
    }
    DQNode* temp = dq->front;
    while(temp){
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void printDequeFromRear(DQ* dq){
    if(!dq){
        printf("The deque has not been initialized.\n");
        return;
    }
    if(isEmpty(dq)){
        printf("The deque is empty.\n");
        return;
    }
    DQNode* temp = dq->rear;
    while(temp){
        printf("%d ", temp->data);
        temp = temp->prev;
    }
    printf("\n");
}

void destroyDeque(DQ* dq){
    if(!dq){
        printf("The deque has not been initialized.\n");
        return;
    }
    DQNode* temp = NULL;
    while(dq->front){
        temp = dq->front;
        dq->front = dq->front->next;
        free(temp);
        temp = NULL;
    }
    return;
}

void test(){
    DQ* dq = init();
    push_front(dq, 1);
    push_front(dq, 2);
    push_front(dq, 3);
    push_front(dq, 4);
    push_front(dq, 5);
    push_front(dq, 6);
    printDequeFromFront(dq);
    push_back(dq, -1);
    push_back(dq, -2);
    push_back(dq, -3);
    push_back(dq, -4);
    push_back(dq, -5);
    printDequeFromFront(dq);
    pop_front(dq);
    pop_front(dq);
    printDequeFromFront(dq);
    printDequeFromRear(dq);
    pop_front(dq);
    pop_front(dq);
    pop_front(dq);
    pop_front(dq);
    printDequeFromFront(dq);
    pop_back(dq);
    pop_back(dq);
    printDequeFromFront(dq);
    pop_back(dq);
    pop_back(dq);
    printDequeFromFront(dq);
}

int main(){
    test();
    return 0;
}
