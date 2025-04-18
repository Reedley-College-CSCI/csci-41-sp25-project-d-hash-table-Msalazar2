#ifdef HASHTABLE_H
#define HASHTABLE_H

#include <string>
using namespace std;


//creating a struct to hold each clients sub status and last day contacted in each bucket.
struct ClientStatus {
    string subscription;
    int lastContacted;
};

#endif