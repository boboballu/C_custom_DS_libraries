/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>

using namespace std;


typedef struct {
    double key;
    char value[256];
} entry_t;


uint32_t compute_hash(entry_t entry) {
    // a simple hash function - computing hash based on sum of
    // ascii values of the key string.
    uint32_t hash   = 0;
    char* key       = (char*) &entry;
    for (int i=0; i<(int)sizeof(entry.key); i++) {
        hash += ((uint32_t) key[i]);
    }
    // printf("hash : %d\n", hash);
    hash = hash * (uint32_t) key[0];
    hash = (hash / 1000) % 10;
    return hash;
}


int main()
{
    for (double i=0; i<100; i=i+0.77) {
        printf("hash computed for %f is : %d\n", i, compute_hash( (entry_t){i,"dummy"} ));
    }
    return 0;
}
