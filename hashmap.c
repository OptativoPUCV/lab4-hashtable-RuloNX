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
      int hashIndex = index;
      while (map->buckets[hashIndex] != NULL) {
          hashIndex = (hashIndex + 1) % map->capacity;
      }
      Pair *new_pair = createPair(key, value);
      map->buckets[hashIndex] = new_pair;
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


void eraseMap(HashMap * map, char * key) {
    if (map == NULL || key == NULL) return;

    long index = hash(key, map->capacity);
    Pair *current = map->buckets[index];
    Pair *prev = NULL;

    while (current != NULL) {
        if (is_equal(current->key, key)) {
            if (prev == NULL) {
                map->buckets[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current->key);
            free(current->value);
            free(current);
            map->size--;
            return;
        }
        prev = current;
        current = current->next;
    }
}

Pair * searchMap(HashMap * map, char * key) {
    if (map == NULL || key == NULL) return NULL;

    long index = hash(key, map->capacity);
    Pair *current = map->buckets[index];

    while (current != NULL) {
        if (is_equal(current->key, key)) {
            map->current = index;
            return current;
        }
        current = current->next;
    }
    return NULL;
}

Pair * firstMap(HashMap * map) {
    if (map == NULL) return NULL;

    for (long i = 0; i < map->capacity; ++i) {
        if (map->buckets[i] != NULL) {
            map->current = i;
            return map->buckets[i];
        }
    }
    return NULL;
}

Pair * nextMap(HashMap * map) {
    long i;
    for (i = map->current + 1; i < map->capacity; i++) {
        if (map->buckets[i] != NULL && map->buckets[i]->key != NULL) {
            map->current = i;
            return map->buckets[i];
        }
    }
    for (i = 0; i <= map->current; i++) {
        if (map->buckets[i] != NULL && map->buckets[i]->key != NULL) {
            map->current = i;
            return map->buckets[i];
        }
    }
    return NULL;
}