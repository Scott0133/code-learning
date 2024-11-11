// 利用二次探测法解决冲突插入关键字
// 增量序列di = 1, -1, 4, -4, 8, -8, ...

#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 13
#define EMPTY -1

typedef struct HashTable {
    int *table;
} HashTable;

HashTable* createTable() {
    HashTable *hashTable = (HashTable *)malloc(sizeof(HashTable));
    hashTable->table = (int *)malloc(TABLE_SIZE * sizeof(int));
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable->table[i] = EMPTY;
    }
    return hashTable;
}

int hashFunction(int key) {
    return key % TABLE_SIZE;
}

int dynamicIncrementSequence(int i) {
    // 根据 i 生成动态的增量值
    if (i % 2 == 0) {
        return (i / 2) * (i / 2);
    } else {
        return -((i + 1) / 2) * ((i + 1) / 2);
    }
}

void insert(HashTable *hashTable, int key) {
    int index = hashFunction(key);
    int originalIndex = index;
    int i = 0;

    while (hashTable->table[index] != EMPTY) {
        index = (originalIndex + dynamicIncrementSequence(i)) % TABLE_SIZE;
        if (index < 0) {
            index += TABLE_SIZE;
        }
        i++;

        // Prevent infinite loop in case of table full
        if (i == TABLE_SIZE) {
            printf("HashTable is full, cannot insert key %d\n", key);
            return;
        }
    }
    hashTable->table[index] = key;
}

void display(HashTable *hashTable) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hashTable->table[i] != EMPTY) {
            printf("Index %d: %d\n", i, hashTable->table[i]);
        } else {
            printf("Index %d: EMPTY\n", i);
        }
    }
}

int main() {
    HashTable *hashTable = createTable();

    int keys[] = {56, 78, 14, 27, 41, 70, 51, 66, 24, 50, 36};
    int n = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < n; i++) {
        insert(hashTable, keys[i]);
    }

    display(hashTable);

    free(hashTable->table);
    free(hashTable);

    return 0;
}
