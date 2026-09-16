# Secured

> Elementary Programming in C — Epitech

A C library implementing a hash table (`libhashtable.a`), built with a custom hash function and separate chaining for collision resolution.

## Table of Contents

- [Goal](#goal)
- [Compilation](#compilation)
- [Skills](#skills)
- [Hash function](#hash-function)
- [Hash table](#hash-table)
- [Dump](#dump)
- [Insert](#insert)
- [Delete](#delete)
- [Search](#search)
- [Collisions](#collisions)

## Goal

The project introduces hash tables by building two things from scratch:

- a custom hash function
- a custom hash table using that function

The table must be able to handle a large number of entries efficiently.

## Compilation

```bash
make          # builds the `libhashtable.a` library
make clean    # removes object files
make fclean   # removes object files and the library
make re       # fclean then rebuild
```

## Skills

- 1D/2D arrays
- Linked lists
- File handling
- Library handling
- `void *` pointers
- Dynamic programming algorithm
- Sorting algorithm
- Argument handling
- Merging arrays and linked lists
- Pointer to functions
- Library compilation
- Hash algorithm

## Hash function

```c
int hash(char *key, int len);
```

`key` is the value to hash, `len` the size of the hash table. The function returns the hashed value; the modulo by table size is applied separately, later.

A good hash function must satisfy 4 criteria:

1. The output is entirely determined by the hashed data (constants are allowed but must be justified).
2. All input data is used in the hashing process.
3. Two almost identical inputs produce very different outputs.
4. The data is evenly distributed across the hash table.

## Hash table

`hashtable.h`:

```c
typedef struct hashtable_s {
    // ...
} hashtable_t;

int hash(char *key, int len);

hashtable_t *new_hashtable(int (*hash)(char *, int), int len);
void delete_hashtable(hashtable_t *ht);

int ht_insert(hashtable_t *ht, char *key, char *value);
int ht_delete(hashtable_t *ht, char *key);
char *ht_search(hashtable_t *ht, char *key);
void ht_dump(hashtable_t *ht);
```

`new_hashtable` takes a pointer to a hash function, so each table can use its own. The internal structure and underlying data structure for the table are left to the implementer. `ht_insert`, `ht_delete` and `ht_search` must handle errors through their return values.

## Dump

`ht_dump` displays the current state of the table:

```c
hashtable_t *ht = new_hashtable(&hash, 4);
ht_dump(ht);
```

```
[0]:
[1]:
[2]:
[3]:
```

## Insert

`ht_insert` hashes the key to determine the index where the value is stored:

```c
ht_insert(ht, "Vision", "./Documents/Tournament/Modules/Vision");
ht_insert(ht, "Kratos", "./Trash/Hollidays_Pics/.secret_folder/kratos.ai");
ht_insert(ht, "<3", "+33 6 31 45 61 23 71");
```

```
[0]:
> 13116 - +33 6 31 45 61 23 71
[1]:
> 1769199557 - ./Documents/Tournament/Modules/Vision
[2]:
> 1952572858 - ./Trash/Hollidays_Pics/.secret_folder/kratos.ai
[3]:
```

Inserting a value under a key that already exists must update the existing value.

## Delete

`ht_delete` hashes the key, locates the index, and removes the associated value:

```c
ht_delete(ht, "Vision");
```

```
[0]:
> 13116 - +33 6 31 45 61 23 71
[1]:
[2]:
> 1952572858 - ./Trash/Hollidays_Pics/.secret_folder/kratos.ai
[3]:
```

## Search

`ht_search` hashes the key, goes to the matching index, and returns the associated value if found:

```c
ht_search(ht, "Kratos");
// -> "./Trash/Hollidays_Pics/.secret_folder/kratos.ai"
```

## Collisions

When two keys hash to the same index after modulo, a collision occurs. This implementation resolves collisions through **separate chaining**: a list of elements is kept at each index.

```c
ht_insert(ht, "<3", "+33 6 31 45 61 23 71");
ht_insert(ht, "</3", "+33 7 51 49 01 38 11"); // same index as "<3"
```

```
[0]:
> 3354428 - +33 7 51 49 01 38 11
> 13116 - +33 6 31 45 61 23 71
[1]:
> 1769199557 - ./Documents/Tournament/Modules/Vision
[2]:
> 1952572858 - ./Trash/Hollidays_Pics/.secret_folder/kratos.ai
[3]:
```