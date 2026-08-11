
#define MAX_NB_KEYS 10000

typedef struct Node {
    struct Node *prev;
    struct Node *next;
    int key;
    int value;
} Node;

typedef struct LRUCache {
    int capacity;
    int length;
    Node *head;
    Node *tail;
    Node **map;
} LRUCache;

Node *NodeCreate(int key, int value);
void moveNodeFront(LRUCache *obj, int key);

Node *NodeCreate(int key, int value) {
    Node *new = malloc(sizeof(Node));
    *new = (Node){NULL, NULL, key, value};
    return new;
}

LRUCache* lRUCacheCreate(int capacity) {
    LRUCache *obj = malloc(sizeof(LRUCache));

    obj->capacity = capacity;
    obj->length = 0;
    obj->head = NULL;
    obj->tail = NULL;

    obj->map = malloc(sizeof(Node *) * MAX_NB_KEYS);
    
    for(int i=0; i < MAX_NB_KEYS; i++) {
        obj->map[i] = NULL;
    }

    return obj;
}

void lRUCacheFree(LRUCache* obj) {
    for (int i=0; i<MAX_NB_KEYS; i++) {
        if (obj->map[i] != NULL) {
            free(obj->map[i]);
        }
    }
    free(obj->map);
    free(obj);
    obj = NULL;
}


void lRUCachePut(LRUCache* obj, int key, int value) {
    if(obj->map[key] == NULL) {
        Node *new = NodeCreate(key, value);

        if (obj->length >= 1) obj->head->prev = new;
        new->next = obj->head;
        obj->head = new;    
        obj->map[key] = new;


        if(obj->length == 0) obj->tail = new;
        if (obj->length >= obj->capacity) {
            Node *temp = obj->tail;
            obj->tail = obj->tail->prev;
            if (obj->tail != NULL) obj->tail->next = NULL;
            obj->map[temp->key] = NULL;
            free(temp); 
        } else { 
            obj->length++;
        }

    } else {
        obj->map[key]->value = value;
        moveNodeFront(obj, key);
    }
}


int lRUCacheGet(LRUCache* obj, int key){
    if (obj->length == 0 || obj->map[key] == NULL) return -1;

     moveNodeFront(obj, key);

    return obj->map[key]->value;
}


void PrintCache(LRUCache *obj) {
    Node *temp = obj->head;
    while(temp != NULL) {
        printf("{%d : %d} -> ", temp->key, temp->value);
        temp = temp->next;
    }
    printf("\n");
}

void moveNodeFront(LRUCache *obj, int key) {
    if (obj->map[key]->prev != NULL) {
        if (obj->map[key]->next == NULL){
            obj->tail = obj->map[key]->prev;
            obj->tail->next = NULL;
        } else {
            obj->map[key]->prev->next = obj->map[key]->next;
            obj->map[key]->next->prev = obj->map[key]->prev;
        }
        //A -> C become B -> A -> C
        obj->map[key]->next = obj->head;
        obj->head->prev = obj->map[key];
        obj->map[key]->prev = NULL;
        obj->head = obj->map[key];
    }

}