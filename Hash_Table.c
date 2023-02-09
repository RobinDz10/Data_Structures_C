#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define ARR_LEN UINT_MAX
#define ERR INT_MIN

typedef struct HashNode{
    char* key;
    int val;
    struct HashNode* next;
} HNode;

typedef struct{
    HNode* table[ARR_LEN];
    int size;
} HTable;

HTable* init_table(){
    HTable* t = (HTable*)malloc(sizeof(HTable));
    if(!t){
        printf("Insufficient memory to initialize the hash table.\n");
        return NULL;
    }
    t->size = 0;
    return t;
}

HTable* destroy_table(HTable* t){
    if(!t){
        printf("This table has not been initialized.\n");
        return NULL;
    }
    for(int i = 0; i < ARR_LEN; i++){
        if(t->table[i] != NULL){
            HNode* head = t->table[i];
            HNode* temp = NULL;
            while(head){
                temp = head;
                head = head->next;
                free(temp);
                temp = NULL;
            }
        }
    }
    free(t);
    return NULL;
}

bool isEmpty(HTable* t){
    if(!t){
        printf("This table has not been initialized.\n");
        return false;
    }
    return 0 == t->size;
}

unsigned int hashCode(const char* str){
    int len = strlen(str);
    unsigned int seed = 131;
    unsigned int hash = 0;
    for(int i = 0; i < len; i++)
        hash = (hash * seed) + (*str++);
    return hash;
}

bool isSameKey(char* str1, const char* str2){
    int len1 = strlen(str1), len2 = strlen(str2);
    if(len1 != len2) return false;
    for(int i = 0; i < len1; i++){
        if(str1[i] != str2[i])
            return false;
    }
    return true;
}

HNode* search_element(HTable* t, const char* str){
    if(!t){
        printf("The table has not been initialized.\n");
        return NULL;
    }
    unsigned int index = hashCode(str);
    if(NULL == t->table[index]){
        printf("The table does not contain this element.\n");
        return NULL;
    }
    HNode* node = t->table[index];
    while(node){
        char* curr = node->key;
        if(isSameKey(curr, str))
            return node;
        node = node->next;
    }
    return NULL;
}

void insert_element(HTable* t, const char* str){
    if(!t){
        printf("The table has not been initialized.\n");
        return;
    }
    HNode* temp = search_element(t, str);
    if(NULL != temp){
        temp->val++;
        return;
    }
    temp = (HNode*)calloc(1, sizeof(HNode));
    if(!temp){
        printf("Calloc node failed.\n");
        return;
    }
    temp->key = (char*)str;
    temp->val = 1;
    temp->next = NULL;
    unsigned int index = hashCode(str);
    if(t->table[index] == NULL)
        t->table[index] = temp;
    else{
        temp->next = t->table[index];
        t->table[index] = temp;
    }
    t->size++;
    return;
}

int get_element_val(HTable* t, const char* str){
    if(!t){
        printf("The table has not been initialized.\n");
        return ERR;
    }
    HNode* temp = search_element(t, str);
    if(NULL == temp){
        printf("The table does not contain this element.\n");
        return ERR;
    }
    return temp->val;
}

void remove_element(HTable* t, const char* str){
    if(!t){
        printf("The table has not been initialized.\n");
        return;
    }
    if(isEmpty(t)){
        printf("The table is empty.\n");
        return;
    }
    HNode* node = search_element(t, str);
    if(NULL != node){
        printf("The table does not contain this element.\n");
        return;
    }
    unsigned int index = hashCode(str);
    HNode* curr = t->table[index];
    if(curr == node){
        if(!curr->next){
            free(curr);
            t->table[index] = NULL;
        }
        else{
            HNode* temp = curr;
            t->table[index] = curr->next;
            free(temp);
            temp = NULL;
        }
    }
    else{
        while(curr->next){
            HNode* prev = curr;
            if(curr->next == node){
                prev->next = curr->next->next;
                free(curr->next);
                curr->next = NULL;
            }
            curr = curr->next;
        }
    }
    t->size--;
    return;
}

void test(){
    HTable* t = init_table();
    insert_element(t, "123");
    printf("%d\n", get_element_val(t, "123"));
    insert_element(t, "123");
    printf("%d\n", get_element_val(t, "123"));
    // printf("%d\n", get_element_val(t, "456"));
    printf("%d\n", t->size);
    return;
}

int main(){
    test();
    return 0;
}
