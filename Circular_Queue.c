#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_SIZE 5
#define ERR INT_MIN

typedef struct{
    int arr[MAX_SIZE];
    int front;
    int rear;
} CQ;

CQ* init(){
    CQ* q = (CQ*)malloc(sizeof(CQ));
    if(!q){
        printf("Insufficient memory to initialize the circular queue.\n");
        return NULL;
    }
    q->front = 0;
    q->rear = 0;
    return q;
}

CQ* destroy(CQ* q){
    if(!q){
        printf("The circular queue has not been initialized.\n");
        return NULL;
    }
    free(q);
    return NULL;
}

void push(CQ* q, int val){
    if(!q){
        printf("The circular queue has not been initialized.\n");
        return;
    }
    if((q->rear + 1) % (MAX_SIZE) == q->front){
        printf("The circular queue is full.\n");
        return;
    }
    q->arr[q->rear] = val;
    q->rear = (q->rear + 1) % MAX_SIZE;
    return;
}

int pop(CQ* q){
    if(!q){
        printf("The circular queue has not been initialized.\n");
        return ERR;
    }
    if(q->rear == q->front){
        printf("The circular queue is empty.\n");
        return ERR;
    }
    int val = q->arr[q->front];
    q->front = (q->front + 1) % MAX_SIZE;
    return val; 
}

void printQ(CQ* q){
    if(!q){
        printf("The circular queue has not been initialized.\n");
        return;
    }
    int i = q->front;
    while(i != q->rear){
        printf("%d ", q->arr[i]);
        i = (i + 1) % MAX_SIZE;
    }
    printf("\n");
    return;
}

void test(){
    CQ* q = init();
    push(q, 1);
    printQ(q);
    push(q, 2);
    printQ(q);
    push(q, 3);
    printQ(q);
    push(q, 4);
    printQ(q);
    push(q, 5);
    printQ(q);
    pop(q);
    push(q, 6);
    printQ(q);
    push(q, 7);
    printQ(q);
    return;
}

int main(){
    test();
    return 0;
}
