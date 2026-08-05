#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

typedef struct Node {
    int value;
    struct Node *next;
    int key;
} Node;

typedef struct {
    struct Node **table;
    int capacity;
    int length;
} MyHashMap;

MyHashMap *myHashMapCreate();
void myHashMapFree(MyHashMap *obj);
Node *initNode(int key, int value);
int hashFunction(int key, int tableLength);
void myHashMapPut(MyHashMap *obj, int key, int value);
void myHashMapRemove(MyHashMap *obj, int key);
void printHashMap(MyHashMap *obj);
float loadFactor(int capacity, int length);
void extendHashMap(MyHashMap *obj);
bool isEmptyHashMap(MyHashMap *obj);
int myHashMapGet(MyHashMap *obj, int key);

#define INIT_ARRAY_SIZE 8

Node *initNode(int key, int value) {
    Node *newNode = malloc(sizeof(Node));
    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL;

    return newNode;
}

MyHashMap *myHashMapCreate() {
    Node **table = malloc(sizeof(Node *) * INIT_ARRAY_SIZE);
    MyHashMap *obj = malloc(sizeof(*obj));

    if (table == NULL || obj == NULL) {
        printf("Errors using malloc -> consider check u're pc <3");
        exit(1);
    }

    obj->capacity = INIT_ARRAY_SIZE;
    obj->length = 0;

    for(int i=0; i<INIT_ARRAY_SIZE; i++) {
        table[i] = NULL;
    }

    obj->table = table;

    return obj;
}


bool isEmptyHashMap(MyHashMap *obj) {
    return obj->length == 0;
}


void myHashMapFree(MyHashMap *obj) {
    Node *temp = NULL;

    for (int i=0; i < obj->capacity; i++) {
        while(obj->table[i] != NULL) {
            temp = obj->table[i]->next;
            free(obj->table[i]);
            obj->table[i] = temp;
        }
    }

    free(obj->table);
    free(obj);
    obj = NULL;

}

int hashFunction(int key, int tableLength) {
    return key % tableLength;
}


void printHashMap(MyHashMap *obj) {
    for (int i=0; i < obj->capacity; i++) {
        if (obj->table[i] != NULL) {
            Node *temp = obj->table[i];
            while(temp != NULL) {
                printf("%d : %d\n", temp->key, temp->value);
                temp = temp->next;
            }
        }
    }
}


void myHashMapPut(MyHashMap *obj, int key, int value) {
    
    if (loadFactor(obj->capacity, obj->length) >= 0.75) extendHashMap(obj);

    bool updateLength = true;

    int index = hashFunction(key, obj->capacity);
    Node *temp = obj->table[index];

    if (temp == NULL) {
        obj->table[index] = initNode(key, value);
    } else {
        while (temp->key != key && temp->next != NULL) {
            temp = temp->next;
        }

        if (temp->key == key) {
            temp->value = value;
            updateLength = false;
        } else {
            temp->next = initNode(key, value);
        }
    }

    if (updateLength) obj->length++;

}


int myHashMapGet(MyHashMap *obj, int key) {
    if(key == 421) {
        printHashMap(obj);
        //exit(1);
    }
    if (isEmptyHashMap(obj)) return -1;
    int index = hashFunction(key, obj->capacity);
    Node *temp = obj->table[index];

    while(temp != NULL && temp->key != key) {
        temp = temp->next;
    }

    if (temp == NULL) {
        return -1;
    } else {
        return temp->value;
    }
}

void myHashMapRemove(MyHashMap *obj, int key) {

    int index = hashFunction(key, obj->capacity);
    Node *temp = obj->table[index];

    bool isDelete = false;
    

    if (temp == NULL) {
        //printf("Can't delete if key dont belong to this map");
        //exit(1);
    } else if (temp->key == key) {
        obj->table[index] = temp->next;
        free(temp);
        isDelete = true;
    } else {
        while (temp->next != NULL && temp->next->key != key ) {
            temp = temp->next;
        }

        if (temp->next == NULL) {
            //printf("Can't delete if key dont belong to this map");
            //exit(1);
        } else {
            Node *toDelete = temp->next;
            temp->next = toDelete->next;
            free(toDelete);
            isDelete = true;
        }
    }

    if(isDelete) obj->length--;
}


float loadFactor(int capacity, int length) {
    return capacity > 0 ? (float)length / capacity : 0.0;
}

void extendHashMap(MyHashMap *obj) {
    int newCapacity = obj->capacity * 2;
    Node **newTable = malloc(sizeof(Node *) * newCapacity);
    if (newTable == NULL) {
        printf("Errors using malloc -> consider check u're pc <3\n");
        exit(1);
    }

    for (int i = 0; i < newCapacity; i++) {
        newTable[i] = NULL;
    }

    for (int i = 0; i < obj->capacity; i++) {
        Node *temp = obj->table[i];
        while (temp != NULL) {
            Node *next = temp->next;      
            int newIndex = hashFunction(temp->key, newCapacity);

            temp->next = newTable[newIndex];
            newTable[newIndex] = temp;

            temp = next;                 
        }
    }

    free(obj->table);   
    obj->table = newTable;
    obj->capacity = newCapacity;
}