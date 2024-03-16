#include "e2d_phys.h"

typedef struct node_t {
    Shape particle;
    int lifespan;
    struct node_t* next;
} Node;

typedef struct list_t {
    Node* head;
    Node* tail;
    int size;
} List;

void listAppend(List* list, Shape shape) {
    Node* new = malloc(sizeof(Node));
    new->particle = shape;
    new->lifespan = 256;
    new->next = NULL;
    
    if (list->size == 0) {
        list->head = new;
    } else {
        list->tail->next = new;
    }
    list->tail = new;
    list->size++;
    
}

Node* listRemove(List* list) {
    if (list->size > 0) {
        Node* tmp = list->head->next;
        free(list->head);
        list->head = tmp;
        list->size--;

        if (list->size == 0) {
            list->tail = NULL;
        }
    }
    return list->head;
}

int main() {
    List list = {NULL, NULL, 0}; //init linked-list
    Shape walls[2] = {e2_Box(400, 700, 400, 50), e2_Box(600, 900,800,50)};
    _rotateBox(&walls[0], 0.5);
    _rotateBox(&walls[1], -0.5);
    walls[0].mass = INFINITY;
    walls[0].inertia = INFINITY;
    walls[1].mass = INFINITY;
    walls[1].inertia = INFINITY;

    const int screenWidth = 1600;
    const int screenHeight = 1200; 

    InitWindow(screenWidth, screenHeight, "raylib");
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    // Main game loop
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        Shape particle = e2_Ball(GetMouseX(),GetMouseY(), 10);
        particle.velocity = (Vector2) {e2_random(-5,5), e2_random(-5,5) };
        listAppend(&list, particle);
        //printf("Anzahl Particel: %i\n", list.size);
        Node* current = list.head;
        if (current->lifespan == 0) {
            //printf("head vorher: %p ", current);
            current = listRemove(&list);
            //printf("head nacher: %p\n", current);
        };

        while (current != NULL) {
            // check walls
            for (size_t i = 0; i < 2; i++) {
                e2_checkColl(&walls[i], &current->particle);
                e2_shapeUpdate(&walls[i]);
                e2_shapeDraw(&walls[i], 3, RED);
            }
            Node* next = current->next;
            while (next != NULL) {
                e2_checkColl(&current->particle, &next->particle);
                next = next->next;
            };
            
            e2_applyForce(&current->particle, (Vector2){0, 4}, 0); //gravity
            e2_shapeUpdate(&current->particle);
            e2_shapeDraw(&current->particle, 1, (Color){0, 0, 0, current->lifespan});
            current->lifespan = current->lifespan - 1;
            if (current->lifespan <0) current->lifespan = 0;
            current = current->next;
        }       
    	EndDrawing();
    }

    CloseWindow();   

    return EXIT_SUCCESS;
}
