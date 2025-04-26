#include "HashTable.h"
#include <iostream>

using namespace std;

//initialzing table size in constructor
HashTable::HashTable() {
    TABLE_SIZE = 19;
    table = new Bucket[TABLE_SIZE];
}

HashTable::~HashTable() {
    delete[] table;
}


//here I create an insert function
bool HashTable::insert(int key, const ClientStatus& value) {
    int hashNum = hash(key);

for (int i = 0; i < TABLE_SIZE; ++i) {
    int index = (hashNum + i * i) % TABLE_SIZE;
    
    if (!table[index].isOccupied) {
        table[index].key = key;
        table[index].value = value;
        table[index].isOccupied = true;
        table[index].isDeleted = false;

        return true;
    }
}
//here I will resize the table
int tempSize = TABLE_SIZE;
int newSize = tempSize * 2;

}
