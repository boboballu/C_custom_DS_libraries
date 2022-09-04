#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_
#include <stdint.h>

// define a address to point to if an entry gets deleted
#define TABLE_DELETED (void*)0xdeadbeef
// Data
template <typename K, typename V> struct hash_table_entry_t{
    K key;
    V value;
};
template <typename K, typename V> class hash_table {
private:
    uint32_t size;
    bool STORE_LOCAL_DATA = false;
    hash_table_entry_t<K, V>** table;           // For the control portion of the hash table (Array of pointers)
    hash_table_entry_t<K, V>* table_data;       // for the data portion of the hash table -> set STORE_LOCAL_DATA to true in constructor
public:
    char CONFIG;
    uint32_t compute_hash(hash_table_entry_t<K, V> entry);
    bool table_initialize(); // initializes the control table; called in constructor
    bool table_insert(hash_table_entry_t<K, V>& entry);
    bool table_delete(hash_table_entry_t<K, V> entry);
    hash_table_entry_t<K, V>* table_search(hash_table_entry_t<K, V>); // only the key is required in the input arg; returns the entry if hits else returns null
    void table_print();
    hash_table(uint32_t size, bool STORE_LOCAL_DATA=false); // constructor. takes in the size calls table_initialize which initializes the entries to null
    ~hash_table(); // destructor. Clears all the memory allocated.
};


// ---------------------------- All Function definition goes here ------------------------------- //
// Note: if a class uses templates, keep both the declaration and definition in the same file
// Else there will be linking errors
// Theory:
// [1] The template class and the member functions are created during the compilation only if the
// the class object declaration with the template datatypes are specified in a cc file.
// Hence, if 2 cc files have 2 class object declarations, the template will create separate class
// functions for those 2 object declarations.
// [2] A regular class class function definitions should be done ic cc files,
// they are created when the class function defenitions are compiled.
// ----------------------------------------------------------------------------------------------//

// generic compute_hash function
// [1] key datatype agnostic
template <typename K, typename V> uint32_t hash_table<K,V>::compute_hash(hash_table_entry_t<K, V> entry) {
    // a simple hash function - computing hash based on sum of
    // ascii values of the key string.
    uint32_t hash   = 0;
    char* key       = (char*) &entry;
    for (int i=0; i<(int)sizeof(entry.key); i++) {
        hash += ((uint32_t) key[i]);
    }
    // printf("hash : %d\n", hash);
    hash = hash * (uint32_t) key[0];
    hash = hash % this->size;
    return hash;
}

// Constructor - call initialize() function to initialize the CONTROL 'table' pointer and DATA structures
template <typename K, typename V> hash_table<K,V>::hash_table(uint32_t size, bool STORE_LOCAL_DATA) {
    this->size = size;
    this->STORE_LOCAL_DATA = STORE_LOCAL_DATA;
    this->table = new hash_table_entry_t<K, V>*[this->size];
    if (STORE_LOCAL_DATA) {
        this->table_data = new hash_table_entry_t<K, V>[this->size];
    }
    table_initialize();
}

// distructor - function to delete the CONTROL 'table' pointer and DATA structures
template <typename K, typename V> hash_table<K,V>::~hash_table() {
    // Delete the control table
    delete[] this->table;
    if (STORE_LOCAL_DATA) {
        delete[] this->table_data;
    }
}

// initialize the table - called in constructor
// [1] returns true always
template <typename K, typename V> bool hash_table<K,V>::table_initialize() {
    for (int i=0; i<this->size; i++) {
        this->table[i] = NULL;
        if (STORE_LOCAL_DATA) {
            this->table_data[i] = (hash_table_entry_t<K, V>){0, 0};
        }
    }
    return 1;
}

// print the table values
// [1] GENERIC - works for both control and CONTROL+DATA methods
template <typename K, typename V> void hash_table<K,V>::table_print() {
    for (int i=0; i<this->size; i++) {
        if (this->table[i] == NULL) {
            printf("%d\t|\t-- NULL --\t|\n", i);
        }
        else if(this->table[i] == (hash_table_entry_t<K,V>*) TABLE_DELETED) {
            printf("%d\t|\t-- DELETED --\t|\n", i);
        }
        else {
            printf("%d\t|\t--key: %s \t --value: %s \t|\n", i, this->table[i]->key, this->table[i]->value);
        }
    }
}

// insert to the hash "table" (Only CONTROL)
// [1] "table" is an array of pointer to the DATA, that keeps track
// [2] For CONTROL+DATA use table_insert_data
// [3] returns 'true' for successful insert | 'false' if the table is full
template <typename K, typename V> bool hash_table<K,V>::table_insert(hash_table_entry_t<K, V>& entry) {
    uint32_t hash = compute_hash(entry);
    // collision - linear probing / open addressing
    int first_deleted_entry = -1;
    for(int i=0; i < this->size; i++) {
        int linear_probe_hash = (hash + i) % this->size;
        // insert new entry
        if (this->table[linear_probe_hash] == NULL) {
            if (STORE_LOCAL_DATA) {
                this->table_data[linear_probe_hash] = entry;
                this->table[linear_probe_hash] = &this->table_data[linear_probe_hash];
            } 
            else {
                this->table[linear_probe_hash] = &entry;
            }
            return true;
        }
        // overrite an existing entry
        else if (strcmp(this->table[linear_probe_hash]->key, entry.key) == 0) {
            this->table[linear_probe_hash] = &entry;
            if (STORE_LOCAL_DATA) {
                this->table_data[linear_probe_hash] = entry;
                this->table[linear_probe_hash] = &this->table_data[linear_probe_hash];
            } 
            else {
                this->table[linear_probe_hash] = &entry;
            }
            return true;
        }
        // keep track of first TABLE_DELETED entry of both the above options fail
        if ( (first_deleted_entry == -1) && (this->table[linear_probe_hash] == (hash_table_entry_t<K,V>*) TABLE_DELETED) ) {
            first_deleted_entry = i;
        }
    }
    if (first_deleted_entry != -1) {
        if (STORE_LOCAL_DATA) {
            this->table_data[first_deleted_entry] = entry;
            this->table[first_deleted_entry] = &this->table_data[first_deleted_entry];
        }
        else {
            this->table[first_deleted_entry] = &entry;
        }
        return true;
    }
    return false;
}

// delete the matching entry in the hash "table" (Only CONTROL)
// [1] "table" is an array of pointer to the DATA, that keeps track
// [2] Sets the matching pointer to NULL, so that the pointer can point to a new DATA
// [3] returns - 'true' if no matching entry to delete | 'false' if successful deletion
template <typename K, typename V> bool hash_table<K,V>::table_delete(hash_table_entry_t<K, V> entry) {
    uint32_t hash = compute_hash(entry);
    // cannot delete a pointer to a location which is not in heap
    // delete table[hash];
    //table[hash] = NULL;
    for(int i=0; i<this->size; i++) {
        int linear_probe_hash = (hash + i) % this->size;
        if (strcmp(this->table[linear_probe_hash]->key, entry.key) == 0) {
            this->table[linear_probe_hash] = (hash_table_entry_t<K,V>*) TABLE_DELETED;
            if (STORE_LOCAL_DATA) {
                this->table_data[linear_probe_hash] = (hash_table_entry_t<K, V>){0, 0};
            }
            return true;
        }
    }
    return false;
}

// search through the hash "table"
// [1] GENERIC - works for both control and CONTROL+DATA methods
// [2] returns 'table' pointer with a valid key match | NULL if no match
template <typename K, typename V> hash_table_entry_t<K, V>* hash_table<K,V>::table_search(hash_table_entry_t<K, V> entry) {
    uint32_t hash = compute_hash(entry);
    // collision  - linear probing / open addressing
    for(int i=0; i < this->size; i++) {
        int linear_probe_hash = (hash + i) % this->size;
        if( (this->table[linear_probe_hash] != NULL) && (this->table[linear_probe_hash] != (hash_table_entry_t<K,V>*) TABLE_DELETED) ) {
            if (strcmp(this->table[linear_probe_hash]->key, entry.key) == 0) {
                return this->table[linear_probe_hash];
            }
        }
    }
    return NULL;
}

#endif