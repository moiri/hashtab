#include <stdio.h>
#include "hash.h"

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
    printf( "\n" );

    return 0;
}
