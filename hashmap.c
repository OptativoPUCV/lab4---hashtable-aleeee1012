#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"

typedef struct HashMap HashMap;
int enlarge_called = 0;

struct HashMap
{
  Pair ** buckets;
  long size; //cantidad de datos/pairs en la tabla
  long capacity; //capacidad de la tabla
  long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value)
{
  Pair * new = (Pair *)malloc(sizeof(Pair));
  new->key = key;
  new->value = value;
  return new;
}

long hash( char * key, long capacity)
{
  unsigned long hash = 0;
  char * ptr;
  for (ptr = key; *ptr != '\0'; ptr++)
  {
    hash += hash*32 + tolower(*ptr);
  }
  return hash%capacity;
}

int is_equal(void* key1, void* key2)
{
  if(key1==NULL || key2==NULL) return 0;
  if(strcmp((char*)key1,(char*)key2) == 0) return 1;
  return 0;
}

void insertMap(HashMap * map, char * key, void * value)
{
  long codigo = hash(key, map->capacity);
  int i = 0;

  if(map->size > (map->capacity * 0.7)) //Si la capacidad ya esta sobre o cerca del 70%
  {
    enlarge(map);
  }

  while(map->buckets[codigo] != NULL && i < map->capacity)
  {
    if(is_equal(map->buckets[codigo]->key, key))
    {
      return;
    }
    codigo = (codigo + 1) % map->capacity;
    i++;
  }

  if(i == map->capacity)
  {
    return;
  }
  map->buckets[codigo] = createPair(key, value);
  map->current = codigo;
  map->size++;
}

void enlarge(HashMap * map)
{
  enlarge_called = 1; //no borrar (testing purposes)
}

HashMap * createMap(long capacity)
{
  HashMap *mapa = (HashMap*) malloc(sizeof(HashMap));
  
  mapa->buckets = (Pair**) malloc(capacity * sizeof(Pair*));
  mapa->size = 0;
  mapa->capacity = capacity;
  mapa->current = -1;
  return mapa;
}

void eraseMap(HashMap * map,  char * key)
{
  Pair *dato = searchMap(map, key);
  
  if(dato != NULL)
  {
    dato->key = NULL;
    map->size--;
  }
}

Pair * searchMap(HashMap * map,  char * key)
{
  long codigo = hash(key, map->capacity);
  int i = 0;

  while(i < map->capacity)
  {
    if(map->buckets[codigo] == NULL)
    {
      break;
    }
    
    if(is_equal(map->buckets[codigo]->key, key))
    {
      map->current = codigo;
      return map->buckets[codigo];
    }
    codigo = (codigo + 1) % map->capacity;
    i++;
  }
  return NULL;
}

Pair * firstMap(HashMap * map)
{
  map->current = 0;
  
  while(map->current < map->capacity)
  {
    if(map->buckets[map->current] != NULL && map->buckets[map->current]->key != NULL)
    {
      map->current++;
      return (map->buckets[map->current-1]);
    }
    map->current++;
  }
  return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
