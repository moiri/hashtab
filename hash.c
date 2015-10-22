/**
 * @author Simon Maurer (forked)
 * @author Tony Thompson https://gist.github.com/tonious/1377667
 * */

#include <stdio.h>
#include <string.h>
#include "hash.h"

/* Create a new hashtable. */
hashtable_t *ht_create( int size ) {

    hashtable_t *hashtable = NULL;
    int i;

    if( size < 1 ) return NULL;

    /* Allocate the table itself. */
    if( ( hashtable = malloc( sizeof( hashtable_t ) ) ) == NULL ) {
        return NULL;
    }

    /* Allocate pointers to the head nodes. */
    if( ( hashtable->entry = malloc( sizeof( entry_t * ) * size ) ) == NULL ) {
        return NULL;
    }
    for( i = 0; i < size; i++ ) {
        hashtable->entry[i] = NULL;
    }

    hashtable->size = size;

    return hashtable;
}

/* Hash a string for a particular hash table. */
int ht_hash( hashtable_t *hashtable, char *key, size_t keyLength ) {
    size_t hash, i;

    // http://en.wikipedia.org/wiki/Jenkins_hash_function
    for ( hash = i = 0; i < keyLength; ++i ) {
        hash += key[i];
        hash += ( hash << 10 );
        hash ^= ( hash >> 6 );
    }
    hash += ( hash << 3 );
    hash ^= ( hash >> 11 );
    hash += ( hash << 15 );

    return hash % hashtable->size;
}

/* Create a key-value pair. */
entry_t *ht_newItem( char *key, size_t keyLength, void *value, size_t size ) {
    entry_t *thisItem;

    if( ( thisItem = malloc( sizeof( entry_t ) ) ) == NULL ) {
        return NULL;
    }

    if( ( thisItem->key = memcpy( malloc( keyLength ), key, keyLength ) ) == NULL ) {
        return NULL;
    }

    if( ( thisItem->value = memcpy( malloc( size ), value, size ) ) == NULL ) {
        return NULL;
    }

    thisItem->keyLength = keyLength;
    thisItem->next = NULL;

    return thisItem;
}

/* Insert a key-value pair into a hash table. */
void ht_put( hashtable_t *hashtable, char *key, void *value, size_t size ) {
    int list = 0;
    size_t keyLength = strlen( key );
    entry_t *thisItem = NULL;
    entry_t *currentItem = NULL;
    entry_t *previousItem = NULL;
    entry_t *primaryItem = NULL;

    if ( size == 0 ) size = strlen( value );

    list = ht_hash( hashtable, key, keyLength );

    primaryItem = currentItem = hashtable->entry[ list ];

    while( currentItem != NULL
            && currentItem->key != NULL
            && ( keyLength > currentItem->keyLength
                || ( keyLength == currentItem->keyLength
                    && memcmp( key, currentItem->key, keyLength ) > 0 ) ) ) {
        previousItem = currentItem;
        currentItem = currentItem->next;
    }

    /* There's already a such a key.  Let's replace that string. */
    if( currentItem != NULL
            && currentItem->key != NULL
            && keyLength == currentItem->keyLength
            && memcmp( key, currentItem->key, keyLength ) == 0 ) {
        free( currentItem->value );
        currentItem->value = memcpy( malloc( size ), value, size );

    /* Nope, could't find it.  Time to grow a pair. */
    } else {
        thisItem = ht_newItem( key, keyLength, value, size );
        thisItem->next = primaryItem;
        hashtable->entry[ list ] = thisItem;
    }
}

/* Retrieve a key-value pair from a hash table. */
void *ht_get( hashtable_t *hashtable, char *key ) {
    int list = 0;
    size_t keyLength = strlen( key );
    entry_t *entryItem;

    list = ht_hash( hashtable, key, keyLength );

    /* Step through the list, looking for our value. */
    entryItem = hashtable->entry[ list ];
    while( entryItem != NULL
            && entryItem->key != NULL
            && ( keyLength > entryItem->keyLength
                || ( keyLength == entryItem->keyLength
                    && memcmp( key, entryItem->key, keyLength ) != 0 ) ) ) {
        entryItem = entryItem->next;
    }

    /* Did we actually find anything? */
    if( entryItem != NULL
            && entryItem->key != NULL
            && keyLength == entryItem->keyLength
            && memcmp( key, entryItem->key, keyLength ) == 0 ) {
        return entryItem->value;
    } else {
        return NULL;
    }
}
