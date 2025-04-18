#ifdef HASHTABLE_H
#define HASHTABLE_H

#include <string>
using namespace std;


//creating a struct to hold each clients sub status and last day contacted in each bucket.
struct ClientStatus {
    string subscription;
    int lastContacted;
};

//here I create a struct for bucket to store the key, client status, and whether the slot is occupied or deleted.
struct Bucket {
    int key;
    ClientStatus value;
    bool isOccupied;
    bool isDeleted;

    Bucket() {
        key = -1;
        isOccupied = false;
        isDeleted = false;
    }
}

#endif