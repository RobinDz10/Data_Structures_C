#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>

#define ERR INT_MIN
#define MAX_SIZE 100

typedef struct TrieNode{
    int val;
    bool isEnd;
    struct TrieNode* parent;
    struct TrieNode* next[128];
} TNode;

typedef struct{
    TNode* root;
    int size;
} Trie;

Trie* init(){
    Trie* t = (Trie*)malloc(sizeof(Trie));
    if(NULL == t){
        printf("Insufficient memory to initialize the trie.\n");
        return NULL;
    }
    t->root = (TNode*)malloc(sizeof(TNode));
    if(NULL == t->root){
        printf("Insufficient memory to initialize the trie.\n");
        return NULL;
    }
    t->size = 0;
    t->root->parent = NULL;
    t->root->isEnd = true;
    t->root->val = 0;
    return t;
}

TNode* destroy_all_nodes(TNode* root){
    for(int i = 0; i < 128; i++){
        if(root->next[i] != NULL){
            root->next[i] = destroy_all_nodes(root->next[i]);
        }
        free(root->next[i]);
        root->next[i] = NULL;
    }
    free(root);
    return NULL;
}

Trie* destroy(Trie* t){
    t->root = destroy_all_nodes(t->root);
    free(t);
    return NULL;
}

bool isEmpty(Trie* t){
    return 0 == t->size;
}

bool isFull(Trie* t){
    return MAX_SIZE == t->size;
}

bool isValidTrie(Trie* t){
    return NULL != t;
}

TNode* search_element(Trie* t, const char* key){
    if(!isValidTrie(t)){
        printf("The trie has not been initialized.\n");
        return NULL;
    }
    if(isEmpty(t)){
        printf("The trie is empty.\n");
        return NULL;
    }
    int len = strlen(key);
    TNode* curr = t->root;
    for(int i = 0; i < len; ++i){
        char ch = key[i];
        int index = (int)ch;
        if(curr->next[index] == NULL)
            return NULL;
        curr = curr->next[index];
    }
    if(0 == curr->val) return NULL;
    return curr;
}

void insert_element(Trie* t, const char* key){
    if(!isValidTrie(t)){
        printf("The trie has not been initialized.\n");
        return;
    }
    if(isFull(t)){
        printf("The trie is full.\n");
        return;
    }
    int len = strlen(key);
    TNode* temp = search_element(t, key);
    if(NULL != temp){
        temp->val++;
        return;
    }
    TNode* curr = t->root;
    for(int i = 0; i < len; ++i){
        char ch = key[i];
        int index = (int)ch;
        if(NULL != curr->next[index])
            curr = curr->next[index];
        else{
            curr->isEnd = false;
            TNode* nextNode = (TNode*)malloc(sizeof(TNode));
            nextNode->isEnd = true;
            nextNode->val = (i == len - 1 ? 1 : 0);
            curr->next[index] = nextNode;
            curr = curr->next[index];
        }
    }
    t->size++;
    return;
}

void remove_element(Trie* t, const char* key){
    if(!isValidTrie(t)){
        printf("The trie has not been initialized.\n");
        return;
    }
    if(isEmpty(t)){
        printf("The trie is empty.\n");
        return;
    }
    int len = strlen(key);
    TNode* temp = search_element(t, key);
    if(NULL == temp){
        printf("The trie does not contain such element.\n");
        return;
    }
    temp->val = 0;
    TNode* tempNode = NULL;
    for(int i = len - 1; i >= 0; i--){
        char ch = key[i];
        int index = (int)ch;
        if(temp->isEnd == true){
            tempNode = temp->parent;
            if(tempNode == NULL){
                free(t->root->next[index]);
                t->root->next[index] = NULL;
                break;
            }
            else{
                free(tempNode->next[index]);
                temp->next[index] = NULL;
            }
            temp = tempNode;
        }
    }
    t->size--;
    return;
}

void test(){
    Trie* t = init();
    const char* str1 = "123";
    const char* str2 = "456";
    insert_element(t, str1);
    insert_element(t, str2);
    const char* str3 = "12";
    const char* str4 = "12345";
    insert_element(t, str4);
    TNode* node1 = search_element(t, str1);
    TNode* node2 = search_element(t, str2);
    TNode* node3 = search_element(t, str3);
    TNode* node4 = search_element(t, str4);
    if(NULL != node1) printf("Y, str1.\n");
    if(NULL != node2) printf("Y, str2.\n");
    if(NULL == node3) printf("N, str3.\n");
    if(NULL != node4) printf("Y, str4.\n");
    printf("%d\n", t->size);
    t = destroy(t);
    TNode* node5 = search_element(t, str1);
}

int main(){
    test();
    return 0;
}
