#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/****
  Basic hash table key/value pair
 ****/
typedef struct Pair {
  char *key;
  char *value;
} Pair;

/****
  Basic hash table
 ****/
typedef struct BasicHashTable {
  int capacity;
  Pair **storage;
} BasicHashTable;

/****
  Create a key/value pair to be stored in the hash table.
 ****/
Pair *create_pair(char *key, char *value)
{
  Pair *pair = malloc(sizeof(Pair));
  pair->key = strdup(key);
  pair->value = strdup(value);

  return pair;
}

/****
  Use this function to safely destroy a hashtable pair.
 ****/
void destroy_pair(Pair *pair)
{
  if (pair != NULL) {
    free(pair->key);
    free(pair->value);
    free(pair);
  }
}

/****
  djb2 hash function

  Do not modify this!
 ****/
unsigned int hash(char *str, int max)
{
  unsigned long hash = 5381;
  int c;
  unsigned char * u_str = (unsigned char *)str;

  while ((c = *u_str++)) {
    hash = ((hash << 5) + hash) + c;
  }

  return hash % max;
}


/****
  Fill this in.

  All values in storage should be initialized to NULL
  (hint: look up `calloc`)
 ****/
BasicHashTable *create_hash_table(int capacity)
{
  // Allocate memory for the HasTable struct
  BasicHashTable *ht = malloc(sizeof(BasicHashTable));

  // Allocate memory for key/value pair storage
  ht->storage = calloc(capacity, sizeof(Pair *));
  ht->capacity = capacity;

  return ht;
}

/****
  Fill this in.
  If you are overwriting a value with a different key, print a warning.
  Don't forget to free any malloc'ed memory!
 ****/
void hash_table_insert(BasicHashTable *ht, char *key, char *value)
{

  // Hash the key
  unsigned int index = hash(key, ht->capacity);
  // Create a key/value pair
  Pair *pair = create_pair(key, value);

  Pair *stored_pair = ht->storage[index];

  // If there is something already there
  if (stored_pair != NULL)
  {

    if (strcmp(key, stored_pair->key) != 0)
    {
      printf("WARNING: overwriting previous values\n");
    }
    destroy_pair(stored_pair);
  }

  // Add the hashedkey to the appropriate spot in ht
  ht->storage[index] = pair;

}

/****
  Fill this in.
  Don't forget to free any malloc'ed memory!
 ****/
void hash_table_remove(BasicHashTable *ht, char *key)
{
  unsigned int index = hash(key, ht->capacity);

  if (ht->storage[index] == NULL || (
      strcmp(ht->storage[index]->key, key) != 0))
  {
    printf("Unable to remove entry\n");
  }
  else
  {
    destroy_pair(ht->storage[index]);
    ht->storage[index] = NULL;
  }
}

/****
  Fill this in.
  Should return NULL if the key is not found.
 ****/
char *hash_table_retrieve(BasicHashTable *ht, char *key)
{
  // hash the provided key to get the index
  unsigned int index = hash(key, ht->capacity);

  // if there is nothing there or the key's don't match
  if (ht->storage[index] == NULL || (
      strcmp(ht->storage[index]->key, key) != 0))
  {
    printf("Unable to retrieve entry\n");

    return NULL;
  }

  // otherwise return the value at the given key
  return ht->storage[index]->value;
}

/****
  Fill this in.
  Don't forget to free any malloc'ed memory!
 ****/
void destroy_hash_table(BasicHashTable *ht)
{

// free every individual element in storage first

for (int i = 0; i < ht->capacity; i++) {
  if (ht->storage[i] != NULL) {
    destroy_pair(ht->storage[i]);
  }
}
  free(ht->storage);
  free(ht);

}


#ifndef TESTING
int main(void)
{
  struct BasicHashTable *ht = create_hash_table(16);

  hash_table_insert(ht, "line", "Here today...\n");

  printf("%s", hash_table_retrieve(ht, "line"));

  hash_table_remove(ht, "line");

  if (hash_table_retrieve(ht, "line") == NULL) {
    printf("...gone tomorrow. (success)\n");
  } else {
    fprintf(stderr, "ERROR: STILL HERE\n");
  }

  destroy_hash_table(ht);

  return 0;
}
#endif
