/**
 * @author Simon Maurer
 * @author Tony Thompson https://gist.github.com/tonious/1377667
 * */

#define _XOPEN_SOURCE 500 /* Enable certain library functions (strdup) on linux.  See feature_test_macros(7) */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct entry_s {
    char *key;
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
int ht_put( hashtable_t *hashtable, char *key, void *value, size_t size ) {
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
        /* printf("get position\n"); */
    }

    /* There's already a such a key.  Let's replace that string. */
    if( currentItem != NULL
            && currentItem->key != NULL
            && keyLength == currentItem->keyLength
            && memcmp( key, currentItem->key, keyLength ) == 0 ) {
        free( currentItem->value );
        currentItem->value = memcpy( malloc( size ), value, size );
        /* printf( "overwrite %d\n", list ); */

    /* Nope, could't find it.  Time to grow a pair. */
    } else {
        thisItem = ht_newItem( key, keyLength, value, size );
        thisItem->next = primaryItem;
        hashtable->entry[ list ] = thisItem;
        /* printf( "add item %s / %d\n", thisItem->key, list ); */
    }
    return 0;
}

/* Retrieve a key-value pair from a hash table. */
void *ht_get( hashtable_t *hashtable, char *key ) {
    int list = 0;
    size_t keyLength = strlen( key );
    entry_t *entryItem;

    list = ht_hash( hashtable, key, keyLength );
    /* printf( "search %s / %d\n", key, list ); */

    /* Step through the list, looking for our value. */
    entryItem = hashtable->entry[ list ];
    /* printf( "start in bucket %s\n", entryItem->key ); */
    /* if ( entryItem != NULL ) printf( "entryItem is not NULL\n" ); */
    /* if ( entryItem->key != NULL ) printf( "eintryItem->key is not NULL\n" ); */
    /* if ( keyLength > entryItem->keyLength ) printf( "keyLength (%lu) > entryItem->keyLength (%lu)\n", keyLength, entryItem->keyLength ); */
    /* if ( keyLength == entryItem->keyLength ) printf( "keyLengths are equal\n" ); */
    /* if ( memcmp( key, entryItem->key, keyLength ) != 0 ) printf( "key > entryItem->key\n" ); */
    while( entryItem != NULL
            && entryItem->key != NULL
            && ( keyLength > entryItem->keyLength
                || ( keyLength == entryItem->keyLength
                    && memcmp( key, entryItem->key, keyLength ) != 0 ) ) ) {
        /* printf( "not %s, go to next\n", entryItem->key ); */
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


int main( int argc, char **argv ) {
    char* res;
    hashtable_t *hashtable = ht_create( 65536 );

    ht_put( hashtable, "key1", "inky", 0 );
    ht_put( hashtable, "key2", "pinky", 0 );
    ht_put( hashtable, "key3", "blinky", 0 );
    ht_put( hashtable, "key4", "floyd", 0 );

    printf( "key1: " );
    res = ht_get( hashtable, "key1" );
    if ( res != NULL ) printf( "%s\n", res );
    printf( "key2: " );
    res = ht_get( hashtable, "key2" );
    if ( res != NULL ) printf( "%s\n", res );
    printf( "key3: " );
    res = ht_get( hashtable, "key3" );
    if ( res != NULL ) printf( "%s\n", res );
    printf( "key4: " );
    res = ht_get( hashtable, "key4" );
    if ( res != NULL ) printf( "%s\n", res );
    printf( "key5: " );
    res = ht_get( hashtable, "key5" );
    if ( res != NULL ) printf( "%s\n", res );

    return 0;
}
