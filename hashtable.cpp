#include "HashTable.h"
#include "clients.h"
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

//create a temp pointer equivalent to table pointer.
Bucket* tempTable = table;
table = new Bucket[newSize];
//here I generate a new hash number
for (int i = 0; i < tempSize; ++i) {
    if (tempTable[i].isOccupied) {
        int newhashNum = tempTable[i].key % newSize;
        //repeat quadratic probing
        for (int i = 0; i < newSize; ++i) {
            int index = (newhashNum + i * i) % newSize;
            if (!table[index].isOccupied) {
                table[newIndex] = tempTable[i];
                break;
            }
        }
    }
}
}

//I will create a function to gathher only unsubscribed clients and insert them into the hash table.
void HashTable::unsubcsribedClients(AllClientData* clientFile, int capacity) {
    for (int i = 0, i < capacity; ++i) {
        if (clientFile[i].campaignInfo.y == "no") {
            ClientStatus status;
            status.subscription = clientFile[i].campaignInfo.y;
            status.lastContacted = clientFile[i].campaignInfo.pdays;
            //call the insert function and pass in these client ids and status info
            insert(clientFile[i].clientInfo.id, status)
        }
    }
}