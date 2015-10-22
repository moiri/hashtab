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
    myEntry e = {"hanuele", "id"};
    ht_put( hashtable, "key5", &e, sizeof (e) );

    printf( "key1: " );
    res.str = ht_get( hashtable, "key1" );
    if ( res.str != NULL ) printf( "%s\n", res.str );
    printf( "key2: " );
    res.str = ht_get( hashtable, "key2" );
    if ( res.str != NULL ) printf( "%s\n", res.str );
    printf( "key3: " );
    res.str = ht_get( hashtable, "key3" );
    if ( res.str != NULL ) printf( "%s\n", res.str );
    printf( "key4: " );
    res.str = ht_get( hashtable, "key4" );
    if ( res.str != NULL ) printf( "%s\n", res.str );
    printf( "key5: " );
    res.e = (struct myEntry*)ht_get( hashtable, "key5" );
    if ( res.e != NULL ) printf( "%s, %s\n", res.e->name, res.e->type );
    printf( "\n" );

    return 0;
}
