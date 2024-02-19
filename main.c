#include "e2d_phys.h"

typedef struct node_t {
    Shape particle;
    struct node_t* next;
} Node;

typedef struct list_t {
    Node* head;
    Node* tail;
    int size;
} List;

void appendList(List* list, Shape shape) {
    Node* new = NULL;
    new = malloc(sizeof(Node));
    new->particle = shape;
    new->next = NULL;
    
    if (list->size == 0) {
        list->head = new;
    } else {
        list->tail->next = new;
    }
    list->tail = new;
    list->size++;
    
}

int main() {
    List list = {NULL, NULL, 0}; //init linked-list

    appendList(&list, e2_Ball(10,10,5));
    appendList(&list, e2_Box(10,10,20,20));
    appendList(&list, e2_Ball(20,30,10));

    Node* current = list.head;
    while (current != NULL) {
        printf("%f\n", current->particle.mass);
        current = current->next;
    }    



    /*
    Node* new = NULL;
    Node* head = NULL;
    Node* current = NULL;


    // First
    new = malloc(sizeof(Node));
    new->particle = e2_Ball(10,10,5);
    new->next = NULL;
    head = new;
    current = new;

    // Second
    new = malloc(sizeof(Node));
    new->particle = e2_Ball(10,10,6);
    new->next = NULL;
    current->next = new;
    current = new;

    // Third
    new = malloc(sizeof(Node));
    new->particle = e2_Ball(10,10,7);
    new->next = NULL;
    current->next = new;
    current = new;
    
    current = head;
    while (current != NULL) {
        printf("%f\n", current->particle.mass);
        current = current->next;
    }    
    */

    return EXIT_SUCCESS;
}
