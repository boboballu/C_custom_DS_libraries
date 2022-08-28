# This repo has custom C / C++ data structures.
# Most of the common datastructures are written from scratch

# hash_table / Map / Dictionary implementation
Sun Aug 28 01:27:40 2022
- hash_table:
Theory:
**[Data]**
- store the entry structure with {key ,value} pair in a array dynamically allocated in Heap.
**[Control]**
- an array of pointers, pointing to each stored entry in the table.
- the array of pointers are initialized to NULL, meaning the table is empty.
- **[Hashfunction]**
    - Compute a hash from the key of the entry structure variable. 
    - Simple hash can be: hash = (sum of all the chars in key, if key is a string); index = hash % HASH_TABLE_SIZE
    - Point the array
- **[Collision]** 2 or more entries can fall to the same index.
    - linear probing / open addressing ( insert - look for the next empty location; search - search forward until the key matches )
    - external chaining (point to a linked list for overlaps and search through it linearly)
    - double hashing (point to another hash_table)