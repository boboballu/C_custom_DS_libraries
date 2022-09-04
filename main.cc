#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

// local .h files
#include "hash_table.h"

int main(){
    hash_table<char[8], char[8]> ht(15, true);

    hash_table_entry_t<char[8], char[8]> entry1 = {"tree", "leaf"};
    hash_table_entry_t<char[8], char[8]> entry2 = {"foot", "ball"};
    hash_table_entry_t<char[8], char[8]> entry3 = {"bird", "wing"};
    hash_table_entry_t<char[8], char[8]> entry4 = {"bike", "cars"};
    hash_table_entry_t<char[8], char[8]> entry5 = {"pen", "ink"};
    hash_table_entry_t<char[8], char[8]> entry6 = {"cell", "phone"};
    hash_table_entry_t<char[8], char[8]> entry7 = {"ear", "ring"};
    hash_table_entry_t<char[8], char[8]> entry8 = {"tree", "top"};

    // construct a hash table (use only the control portion of the hash_table)
    ht.table_insert(entry1);
    ht.table_insert(entry2);
    ht.table_insert(entry3);
    ht.table_insert(entry4);
    ht.table_insert(entry5);
    ht.table_insert(entry6);
    ht.table_insert(entry7);
    ht.table_insert(entry8);
    // delete a entry in the hash table
    ht.table_delete(entry3);

    // checking STORE_LOCAL_DATA option, the below change shouldnot affect STORE_LOCAL_DATA, but should affect
    strcpy( entry8.key, "abc");
    strcpy(entry8.value,"xyz");

    printf("--------- print the table -----------\n");
    ht.table_print();

    // search the hash table
    hash_table_entry_t<char[8], char[8]>* search_ptr = ht.table_search((hash_table_entry_t<char[8], char[8]>){"bike", ""});
    if (search_ptr != NULL) {
        printf("search:\t|\t --key %s \t --value: %s \t|\n", search_ptr->key, search_ptr->value);
    }
    else {
        printf("search:\t|\t-- NULL --\t|\n");
    }
}