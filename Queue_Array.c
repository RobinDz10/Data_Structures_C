#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_SIZE 100
#define ERR INT_MIN

typedef struct Queue{
    int data[MAX_SIZE];
    int rear;
} Q;

Q* init(){
    Q* q = (Q*)malloc(sizeof(Q));
    if(!q){
        printf("Insufficient memory.\n");
        return NULL;
    }
    q->rear = -1;
    return q;
}

bool isFull(Q* q){
    return MAX_SIZE - 1 == q->rear;
}

bool isEmpty(Q* q){
    return -1 == q->rear;
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
    if(isEmpty(q)){
        q->rear = 0;
        q->data[q->rear] = val;
    }
    else
        q->data[++q->rear] = val;
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
    return q->data[0];
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
    int val = q->data[0];
    if(q->rear >= 1){
        for(int i = 1; i <= q->rear; ++i){
            int temp = q->data[i];
            q->data[i] = q->data[i - 1];
            q->data[i - 1] = temp;
        }
    }
    q->rear--;
    return val;
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
    for(int i = 0; i <= q->rear; i++){
        printf("%d ", q->data[i]);
    }
    printf("\n");
    return;
}

void deleteQueue(Q* q){
    if(!q){
        printf("The queue has not been initialized.\n");
        return;
    }
    free(q);
    q = NULL;
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
    pop(q);
    printQueue(q);
    pop(q);
    printQueue(q);
    pop(q);
    printQueue(q);
    pop(q);
    printQueue(q);
    pop(q);
    printQueue(q);
    peek(q);
}

int main(){
    test();
    return 0;
}
