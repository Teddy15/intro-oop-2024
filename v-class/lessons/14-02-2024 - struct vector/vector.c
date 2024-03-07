#include<stdio.h>
#include<stdlib.h>

struct vector_t {
    int capacity;
    int size;
    int* array;
};

typedef struct vector_t vector;

void initialize_vector(vector v) {
    for (int i = 0; i < v-size; i++) {
        v->array[i] = i * 5;
    }
}

void print_vector(vector v) {
    for (int i = 0; i < v-size; i++) {
        printf("%d" , v->array[i]);
    }
    printf("\n");
}

void create_vector(vector v, int capacity, int size) {
    v->size = size;
    v->capacity = capacity;
    v->array = (int) malloc(sizeof(int) * size);
}

void add(vector v, int value) {
    if (v->size == v->capacity) {
        v->capacity = v->capacity * 2;
        v->array = (int) realloc(v->array, v->capacity);
    }

    v->array[v->size] = value;
    v->size++;
}

int main() {
    vector v;
    
    const int SIZE = 2;
    const int CAPACITY = 5;
    
    create_vector(&v, CAPACITY, SIZE);
    initialize_vector(&v);
    print_vector(&v);

    add(&v, 1);
    add(&v, 2);
    add(&v, 3);
    add(&v, 4);

    print_vector(&v);

    return 0;
}