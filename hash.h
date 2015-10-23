/**
 * @author Simon Maurer (forked)
 * @author Tony Thompson https://gist.github.com/tonious/1377667
 * */

#ifndef HASH_H
#define HASH_H

#include <stdlib.h>     // size_t
#include <stdbool.h>    // bool

struct entry_s {
    void *key;
    size_t keyLength;
    void *value;
    struct entry_s *next;
};

typedef struct entry_s entry_t;

struct hashtable_s {
    int size;
    struct entry_s **entry;
};

typedef struct hashtable_s hashtable_t;

hashtable_t *ht_create( int size );
void ht_put( hashtable_t *hashtable, void *key, size_t keyLength,
        void *value, size_t valLength );
void *ht_get( hashtable_t *hashtable, void *key, size_t keyLength );

#endif // HASH_H
