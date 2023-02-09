#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_SIZE 100
#define ERR INT_MIN

typedef struct HeapNode{
    int arr[MAX_SIZE];
    int size;
} Heap;

Heap* init_heap(){
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    if(!heap){
        printf("Insufficient memory to initialize a heap.\n");
        return NULL;
    }
    heap->size = 0;
    return heap;
}

Heap* destroy_heap(Heap* heap){
    if(!heap){
        printf("The heap has not been initialized.\n");
        return NULL;
    }
    free(heap);
    return NULL;
}

bool isEmpty(Heap* heap){
    if(!heap){
        printf("The heap has not been initialized.\n");
        return true;
    }
    return 0 == heap->size;
}

bool isFull(Heap* heap){
    if(!heap){
        printf("The heap has not been initialized.\n");
        return false;
    }
    return MAX_SIZE == heap->size;
}

void printHeap(Heap* heap){
    if(!heap){
        printf("The heap has not been initialized.\n");
        return;
    }
    if(isEmpty(heap)){
        printf("The heap is empty.\n");
        return;
    }
    for(int i = 0; i < heap->size; i++){
        printf("%d ", heap->arr[i]);
    }
    printf("\n");
    return;
}

void adjustHeap(Heap* heap, int index){
    while(true){
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        if(left >= heap->size)
            return;
        int min = left;
        if(right < heap->size && (heap->arr[right] < heap->arr[left]))
            min = right;
        if(heap->arr[index] <= heap->arr[min])
            return;
        int temp = heap->arr[index];
        heap->arr[index] = heap->arr[min];
        heap->arr[min] = temp;
        index = min;
    }
}

void insert(Heap* heap, int val){
    if(!heap){
        printf("The heap has not been initialized.\n");
        return;
    }
    if(isFull(heap)){
        printf("The heap is full.\n");
        return;
    }
    heap->arr[heap->size++] = val;
    int i;
    for(i = (heap->size - 1) / 2; i >= 0; i--)
        adjustHeap(heap, i);
    return;
}

int peek(Heap* heap){
    if(!heap){
        printf("The heap has not been initialized.\n");
        return ERR;
    }
    if(isEmpty(heap)){
        printf("The heap is empty.\n");
        return ERR;
    }
    return heap->arr[0];
}

int pop(Heap* heap){
    if(!heap){
        printf("The heap has not been initialized.\n");
        return ERR;
    }
    if(isEmpty(heap)){
        printf("The heap is empty.\n");
        return ERR;
    }
    int res = heap->arr[0];
    for(int i = 1; i < heap->size; i++){
        int temp = heap->arr[i - 1];
        heap->arr[i - 1] = heap->arr[i];
        heap->arr[i] = temp;
    }
    heap->size--;
    return res;
}

void test(){
    Heap* heap = init_heap();
    insert(heap, 5);
    insert(heap, 6);
    printHeap(heap);
    insert(heap, 1);
    insert(heap, 2);
    printHeap(heap);
    printf("%d\n", peek(heap));
    printHeap(heap);
    printf("%d\n", pop(heap));
    printHeap(heap);
    printf("%d\n", pop(heap));
    printHeap(heap);
    printf("%d\n", pop(heap));
    printHeap(heap);
    printf("%d\n", pop(heap));
    printHeap(heap);
    insert(heap, 2);
    printHeap(heap);
    heap = destroy_heap(heap);
    printHeap(heap);
}

int main(){
    test();
    return 0;
}