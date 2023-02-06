#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>

#define ERR INT_MIN
#define MAX_ELEMENTS 100
#define ARR_LEN INT_MAX

typedef struct HashNode{
    char* key;
    int val;
    struct HashNode* next;
} HNode;

typedef struct{
    HNode* arr[ARR_LEN];
    int nums;
} HTable;

HTable* init(){
    HTable* table = (HTable*)malloc(sizeof(HTable));
    if(!table){
        printf("Insufficient memory to initialize the hash table.\n");
        return NULL;
    }
    table->nums = 0;
    return table;
}

HTable* destroy(HTable* table){
    if(!table){
        printf("This table has not been initialized.\n");
        return NULL;
    }
    for(int i = 0; i < ARR_LEN; i++){
        if(table->arr[i] != NULL){
            HNode* head = table->arr[i];
            HNode* temp = NULL;
            while(head){
                temp = head;
                head = head->next;
                free(temp);
                temp = NULL;
            }
        }
    }
    free(table);
    return NULL;
}

bool isFull(HTable* table){
    if(!table){
        printf("This table has not been initialized.\n");
        return false;
    }
    return MAX_ELEMENTS == table->nums;
}

bool isEmpty(HTable* table){
    if(!table){
        printf("This table has not been initialized.\n");
        return false;
    }
    return 0 == table->nums;
}

bool isSame(char* str1, char* str2){
    int len1 = strlen(str1), len2 = strlen(str2);
    if(len1 != len2) return false;
    for(int i = 0; i < len1; i++){
        if(str1[i] != str2[i])
            return false;
    }
    return true;
}

unsigned int hash_code(char* str){
    unsigned int seed = 131;
    unsigned int hash = 0;
    unsigned int len = strlen(str);
    for(int i = 0; i < len; i++)
        hash = (hash * seed) + (*str++);
    return hash;
}

HNode* search_element(HTable* table, char* str){
    if(!table){
        printf("This table has not been initialized.\n");
        return NULL;
    }
    unsigned int index = hash_code(str);
    if(NULL == table->arr[index]){
        printf("The key is not contained in the table.\n");
        return NULL;
    }
    HNode* curr = table->arr[index];
    while(curr){
        if(isSame(curr->key, str))
            return curr;
        curr = curr->next;
    }
    return NULL;
}

int put_element(HTable* table, char* str){
    if(!table){
        printf("This table has not been initialized.\n");
        return ERR;
    }
    unsigned int index = hash_code(str);
    HNode* node = search_element(table, str);
    if(NULL != node){
        node->val += 1;
        return node->val;
    }
    node = (HNode*)calloc(1, sizeof(HNode));
    if(!node){
        printf("Insufficient memory to add a new element.\n");
        return ERR;
    }
    node->key = str;
    node->val = 1;
    node->next = NULL;
    if(NULL == table->arr[index])
        table->arr[index] = node;
    else{
        node->next = table->arr[index];
        table->arr[index] = node->next;
    }
    table->nums++;
    return node->val;
}

int get_element(HTable* table, char* str){
    if(!table){
        printf("This table has not been initialized.\n");
        return ERR;
    }
    unsigned int index = hash_code(str);
    if(NULL == table->arr[index]){
        printf("The element is not contained in the table.\n");
        return ERR;
    }
    HNode* temp = table->arr[index];
    while(temp){
        if(isSame(temp->key, str))
            return temp->val;
        temp = temp->next;
    }
    return ERR;
}

void remove_element_entirely(HTable* table, char* str){
    if(!table){
        printf("This table has not been initialized.\n");
        return;
    }
    HNode* temp = search_element(table, str);
    if(NULL == temp){
        printf("This table does not contain this element.\n");
        return;
    }
    unsigned int index = hash_code(str);
    temp = table->arr[index];
    if(NULL == temp){
        printf("This table does not contain this element.\n");
        return;
    }
    HNode* curr = table->arr[index];
    HNode* prev = NULL;
    if(NULL == table->arr[index]->next){
        free(curr);
        curr = NULL;
        table->arr[index] = NULL;
    }
    else{
        if(isSame(curr->key, str)){
            table->arr[index] = curr->next;
            free(curr);
            curr = NULL;
        }
        else{
            while(curr->next){
                prev = curr;
                curr = curr->next;
                if(isSame(curr->key, str)){
                    prev->next = curr->next;
                    free(curr);
                    curr = NULL;
                }
            }
        }
    }
    table->nums--;
    return;
}

void remove_element_once(HTable* table, char* str){
    if(!table){
        printf("This table has not been initialized.\n");
        return;
    }
    unsigned int index = hash_code(str);
    if(NULL == table->arr[index]){
        printf("The element is not contained in the table.\n");
        return;
    }
    HNode* temp = table->arr[index];
    while(temp){
        if(isSame(temp->key, str)){
            if(1 == temp->val){
                remove_element_entirely(table, str);
                return;
            }
            temp->val -= 1;
            return;
        }
        temp = temp->next;
    }
    return;
}

void test(){
    HTable* table = init();
    char* str1 = "123";
    char* str2 = "456";
    put_element(table, str1);
    put_element(table, str2);
    put_element(table, str1);
    HNode* temp = search_element(table, str1);
    printf("%d\n", temp->val);
    remove_element_once(table, str2);
    temp = search_element(table, str2);
    remove_element_once(table, str1);
    temp = search_element(table, str1);
    printf("%d\n", temp->val);
    return;
}

int main(){
    test();
    return 0;
}
