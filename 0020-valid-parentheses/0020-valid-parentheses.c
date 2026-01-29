#include <stdlib.h>
#define MAX 10001

typedef struct elem {
    char val;
    struct elem *next;
} elem;

typedef struct pile {
    elem *elem;
    int head;
} pile;


pile *create_pile() {
    pile *new_pile = malloc(sizeof(pile));
    new_pile->elem = NULL;
    new_pile->head = 0;
    return new_pile;
}   

bool pile_empty(pile *pile) {return pile->head == 0;}
bool pile_full(pile *pile) {return pile->head == MAX;}

void empiler(pile *pile, char val) {
    if (!pile_full(pile)) {
        elem *new_elem = malloc(sizeof(elem));
        new_elem->val = val;
        new_elem->next = pile->elem;
        pile->elem = new_elem;
        pile->head++;
    }
}

char depiler(pile *pile) {
    if(!pile_empty(pile)) {
        elem *temp = pile->elem;
        pile->elem = temp->next;
        pile->head--;
        return temp->val;
    }
    return '\0';
}

int is_ouvrante(char c) {
    return c == '(' || c == '{' || c == '[';
}

int fermante(char ouvrante) {
    if (ouvrante == '(') return ')';
    else if (ouvrante == '[') return ']';
    else return '}';
}
 
bool isValid(char* s) {
    pile *pile = create_pile();
    int i = 0;
    while (s[i] != '\0' && !pile_full(pile)) {
        if (is_ouvrante(s[i])) empiler(pile, s[i]);
        else if (pile_empty(pile) || pile_full(pile) || fermante(depiler(pile)) != s[i]) return false;
        i++;
    }
    return pile_empty(pile);
}