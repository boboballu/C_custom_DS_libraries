#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

// local .h files
#include "hash_table.h"

// public functions
uint32_t hash_table::compute_hash(hash_table_entry_t entry) {
    // a simple hash function computing hash based on sum of
    // ascii values of the key string.
    uint32_t hash=0;
    for (int i=0; entry.key[i] != '\0'; i++) {
        hash += (uint32_t) entry.key[i];
    }
    hash = hash * entry.key[0];
    hash = hash % 10;
    return hash;
}

hash_table::hash_table() {
    table_initialize();
}

bool hash_table::table_initialize() {
    for (int i=0; i<10; i++) {
        table[i] = NULL;
    }
    return 1;
}

void hash_table::table_print() {
    for (int i=0; i<10; i++) {
        if (table[i] == NULL) {
            printf("%d\t|\t-- NULL --\t|\n", i);
        }
        else {
            printf("%d\t|\t--key: %s \t --value: %s \t|\n", i, table[i]->key, table[i]->value);
        }
    }
}

bool hash_table::table_insert(hash_table_entry_t& entry) {
    uint32_t hash = compute_hash(entry);
    // insert if the table is empty
    // if (table[hash] == NULL) {
    //     table[hash] = &entry;
    // }
    // // overrite
    // else if (strcmp(entry.key, table[hash]->key) == 0) {
    //     // printf("--key: %s | --value %s | overrite\n", entry.key, entry.value);
    //     table[hash] = &entry;
    // }
    // // collision
    // else {
    //     printf("--key: %s | --value: %s | Collision at %d\n", entry.key, entry.value, hash);
    // }
    
    
    // collision - linear probing / open addressing
    // printf("--key: %s | --value: %s | Collision at %d\n", entry.key, entry.value, hash);
    for(int i=0; i<10; i++) {
        int linear_probe_hash = (hash + i) % 10;
        if (table[linear_probe_hash] == NULL) {
            table[linear_probe_hash] = &entry;
            // break;
        }
    }
    return true;
}

hash_table_entry_t* hash_table::table_search(hash_table_entry_t entry) {
    uint32_t hash = compute_hash(entry);
    if (table[hash]==NULL) {
        return NULL;
    }
    // else if (strcmp(table[hash]->key, entry.key) == 0) {
    //     return table[hash];
    // }
    // collision  - linear probing / open addressing
    else {
        for(int i=0; i<10; i++) {
            int linear_probe_hash = (hash + i) % 10;
            if (strcmp(table[linear_probe_hash]->key, entry.key) == 0) {
                return table[linear_probe_hash];
            }
        }
    }
    return NULL;
}


bool hash_table::table_create_and_insert_enrty(hash_table_entry_t entry) {
    hash_table_entry_t* ptr = new hash_table_entry_t;
    *ptr = entry;
    table_insert(*ptr);
}


int main(){
    hash_table ht;

    hash_table_entry_t entry1 = {"tree", "leaf"};
    hash_table_entry_t entry2 = {"foot", "ball"};
    hash_table_entry_t entry3 = {"bird", "wing"};
    hash_table_entry_t entry4 = {"bike", "cars"};
    hash_table_entry_t entry5 = {"pen", "ink"};
    hash_table_entry_t entry6 = {"cell", "phone"};
    hash_table_entry_t entry7 = {"ear", "ring"};
    hash_table_entry_t entry8 = {"tree", "top"};

    printf("key: %s | value: %s\n", entry1.key, entry1.value);
    printf("hash for the entry is %d\n", hash_table::compute_hash(entry1));
    ht.table_insert(entry1);
    ht.table_insert(entry2);
    ht.table_insert(entry3);
    ht.table_insert(entry4);
    ht.table_insert(entry5);
    ht.table_insert(entry6);
    ht.table_insert(entry7);
    ht.table_insert(entry8);

    printf("--------- print the table -----------\n");
    ht.table_print();

    hash_table_entry_t* search_ptr = ht.table_search((hash_table_entry_t){"bike", ""});
    if (search_ptr != NULL) {
        printf("search:\t|\t --key %s \t --value: %s \t|\n", search_ptr->key, search_ptr->value);
    }
    else {
        printf("search:\t|\t-- NULL --\t|\n");
    }
}