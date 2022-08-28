#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_
#include <stdint.h>

typedef struct  {
    char key[256];
    char value[256];
} hash_table_entry_t;

class hash_table {
private:
    hash_table_entry_t* table[10];
public:

    static uint32_t compute_hash(hash_table_entry_t entry);

    bool table_initialize(); // initializes the table; called in cusntructor
    bool table_insert(hash_table_entry_t& entry);
    bool table_create_and_insert_enrty(hash_table_entry_t entry);
    bool table_delete(hash_table_entry_t entry);
    hash_table_entry_t* table_search(hash_table_entry_t); // only the key is required in the input arg; returns the entry if hits else returns null
    void table_print();
    hash_table(); // constructor. calls table_initialize which initializes the entries to null
};

#endif