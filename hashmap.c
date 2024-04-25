#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}

void insertMap(HashMap * map, char * key, void * value) {
    if (map == NULL || key == NULL) return;

    long index = hash(key, map->capacity);

    if (map->buckets[index] == NULL) {
        Pair *new_pair = createPair(key, value);
        map->buckets[index] = new_pair;
        map->size++;
    } else {
        // Manejo de colisión de hash utilizando una lista enlazada
        Pair *current = map->buckets[index];
        while (current->next != NULL) {
            if (is_equal(current->key, key)) {
                free(current->value);
                current->value = value;
                return;
            }
            current = current->next;
        }
        Pair *new_pair = createPair(key, value);
        current->next = new_pair;
        map->size++;
    }
}


void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)

}


HashMap * createMap(long capacity) {
    HashMap * map = (HashMap *)malloc(sizeof(HashMap));
    if (map == NULL) {
        return NULL;
    }

    map->buckets = (Pair **)malloc(capacity * sizeof(Pair *));
    if (map->buckets == NULL) {
        free(map);
        return NULL;
    }

    map->size = 0;
    map->capacity = capacity;
    map->current = -1;

    for (long i = 0; i < capacity; i++) {
        map->buckets[i] = NULL;
    }

    return map;
}


void eraseMap(HashMap * map,  char * key) {    


}

Pair * searchMap(HashMap * map,  char * key) {   


    return NULL;
}

Pair * firstMap(HashMap * map) {

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
