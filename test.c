#include <stdio.h>
#include "hash.h"

int main( int argc, char **argv ) {
    typedef struct myEntry {
        char* name;
        char* type;
    } myEntry;
    typedef struct myKey {
        char* key;
        int scope;
    } myKey;
    union {
        char* str;
        myEntry* e;
    } res;
    hashtable_t *hashtable = ht_create( 65536 );

    ht_put( hashtable, "key1", 0, "inky", 0 );
    ht_put( hashtable, "key2", 0, "pinky", 0 );
    ht_put( hashtable, "key3", 0, "blinky", 0 );
    ht_put( hashtable, "key4", 0, "floyd", 0 );
    myEntry e = {"hanuele", "uele"};
    myKey k = {"key5", 2};
    ht_put( hashtable, &k, sizeof( k ), &e, sizeof( e ) );
    myEntry e2 = {"wotuele", "uele"};
    myKey k2 = {"key6", 18};
    ht_put( hashtable, &k2, sizeof( k2 ), &e2, sizeof( e2 ) );

    res.str = ht_get( hashtable, "key1", 0 );
    if ( res.str != NULL ) printf( "%s\n", res.str );
    res.str = ht_get( hashtable, "key2", 0 );
    if ( res.str != NULL ) printf( "%s\n", res.str );
    res.str = ht_get( hashtable, "key3", 0 );
    if ( res.str != NULL ) printf( "%s\n", res.str );
    res.str = ht_get( hashtable, "key4", 0 );
    if ( res.str != NULL ) printf( "%s\n", res.str );
    res.e = (struct myEntry*)ht_get( hashtable, &k, sizeof( k ) );
    if ( res.e != NULL ) printf( "%s, %s\n", res.e->name, res.e->type );
    res.e = (struct myEntry*)ht_get( hashtable, &k2, sizeof( k2 ) );
    if ( res.e != NULL ) printf( "%s, %s\n", res.e->name, res.e->type );

    return 0;
}
