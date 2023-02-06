#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_SIZE 100
#define ERR INT_MIN

typedef struct QueueNode{
    int data;
    struct QueueNode* next;
} QNode;

typedef struct{
    int size;
    QNode* front;
    QNode* rear;
} Q;

Q* init(){
    Q* q = (Q*)malloc(sizeof(Q));
    if(!q){
        printf("Insufficient memory to initialize a queue.\n");
        return NULL;
    }
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
    return q;
}

bool isFull(Q* q){
    return MAX_SIZE == q->size;
}

bool isEmpty(Q* q){
    return 0 == q->size;
}

void push(Q* q, int val){
    if(!q){
        printf("The queue has not been initialized.\n");
        return;
    }
    if(isFull(q)){
        printf("The queue is full.\n");
        return;
    }
    QNode* node = (QNode*)malloc(sizeof(QNode));
    if(!node){
        printf("Insufficient memory to initialize a new queue node.\n");
        return;
    }
    node->data = val;
    node->next = NULL;
    if(NULL == q->front){
        q->front = node;
    }
    if(NULL == q->rear){
        q->rear = node;
    }
    else{
        q->rear->next = node;
        q->rear = node;
    }
    q->size++;
    return;
}

int peek(Q* q){
    if(!q){
        printf("The queue has not been initialized.\n");
        return ERR;
    }
    if(isEmpty(q)){
        printf("The queue is empty.\n");
        return ERR;
    }
    return q->front->data;
}

int pop(Q* q){
    if(!q){
        printf("The queue has not been initialized.\n");
        return ERR;
    }
    if(isEmpty(q)){
        printf("The queue is empty.\n");
        return ERR;
    }
    QNode* temp = q->front;
    int val = temp->data;
    if(q->front == q->rear){
        q->front = NULL;
        q->rear = NULL;
    }
    else{
        q->front = temp->next;
    }
    q->size--;
    free(temp);
    temp = NULL;
    return val;
}

void destroyQueue(Q* q){
    if(!q){
        printf("The queue has not been initialized.\n");
        return;
    }
    QNode* temp = NULL;
    while(q->front){
        temp = q->front;
        q->front = q->front->next;
        free(temp);
        temp = NULL;
    }
    return;
}

void printQueue(Q* q){
    if(!q){
        printf("The queue has not been initialized.\n");
        return;
    }
    if(isEmpty(q)){
        printf("The queue is empty.\n");
        return;
    }
    QNode* temp = q->front;
    while(temp){
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
    return;
}

void test(){
    Q* q = init();
    push(q, 1);
    push(q, 2);
    push(q, 3);
    push(q, 4);
    push(q, 5);
    printQueue(q);
    printf("%d\n", pop(q));
    printf("%d\n", pop(q));
    printQueue(q);
    printf("%d\n", pop(q));
    printf("%d\n", pop(q));
    printQueue(q);
    printf("%d\n", pop(q));
    printQueue(q);
    pop(q);
    pop(q);
    destroyQueue(q);
}

int main(){
    test();
    return 0;
}
