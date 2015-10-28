#include <stdio.h>
#include "hash.h"

int main( int argc, char **argv ) {
    typedef struct myEntry {
        char* name;
        char* type;
    } myEntry;
    union {
        char* str;
        myEntry* e;
    } res;
    hashtable_t *hashtable = ht_create( 65536 );

    ht_put( hashtable, "key1", "inky", 0 );
    ht_put( hashtable, "key2", "pinky", 0 );
    ht_put( hashtable, "key3", "blinky", 0 );
    ht_put( hashtable, "key4", "floyd", 0 );
    myEntry e = {"hanuele", "uele"};
    ht_put( hashtable, "key5", &e, sizeof( e ) );
    myEntry e2 = {"wotuele", "uele"};
    ht_put( hashtable, "key6", &e2, sizeof( e2 ) );

    res.str = ht_get( hashtable, "key1" );
    if ( res.str != NULL ) printf( "%s\n", res.str );
    res.str = ht_get( hashtable, "key2" );
    if ( res.str != NULL ) printf( "%s\n", res.str );
    res.str = ht_get( hashtable, "key3" );
    if ( res.str != NULL ) printf( "%s\n", res.str );
    res.str = ht_get( hashtable, "key4" );
    if ( res.str != NULL ) printf( "%s\n", res.str );
    res.e = (struct myEntry*)ht_get( hashtable, "key5" );
    if ( res.e != NULL ) printf( "%s, %s\n", res.e->name, res.e->type );
    res.e = (struct myEntry*)ht_get( hashtable, "key6" );
    if ( res.e != NULL ) printf( "%s, %s\n", res.e->name, res.e->type );

    return 0;
}
