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
        for (int j = 0; j < newSize; ++j) {
            int newIndex = (newhashNum + j * j) % newSize;
            if (!table[newIndex].isOccupied) {
                table[newIndex] = tempTable[i];
                break;
            }
        }
    }
}
return false;
}

//I create a display function with client status
void HashTable::display() const {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        cout << "[" << i << "] ";

        if (table[i].isOccupied) {
            cout << "ID: " << table[i].key 
                 << "| Subscription: " << table[i].value.subscription
                 << "| Days Since Last Contact: " << table[i].value.lastContacted 
                 << endl;
        }
       
        else {
            cout << "EMPTY" << endl;
        }
    }
}

//I will create a function to gathher only unsubscribed clients and insert them into the hash table.
void HashTable::unsubscribedClients(AllClientData* clientFile, int capacity) {
    for (int i = 0; i < capacity; ++i) {
        if (clientFile[i].campaignInfo.y == "\"no\"") {
            ClientStatus status;
            status.subscription = clientFile[i].campaignInfo.y;
            status.lastContacted = clientFile[i].campaignInfo.pdays;
            //call the insert function and pass in these client ids and status info
            insert(clientFile[i].clientInfo.id, status);
        }
    }
}
//here I will create a function to search by pdays with a threshold of 60 days.
void HashTable::searchPdays(int minDays) {
    cout << "Searching..." << endl;
    cout << "\nClients with " << minDays << " or more: \n";

    bool dayFound = false;

    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table[i].isOccupied && !table[i].isDeleted) {
            ClientStatus client = table[i].value;
            if (client.lastContacted < minDays) continue;

            cout << "\nID: " << table[i].key;
            cout << " | Subscription: " << client.subscription;
            cout << " | Days since last contact: " << client.lastContacted << endl;
            cout << "-------------------------------------------------------------";

            dayFound = true;
        }
    }

    if (!dayFound) {
        cout << "No matches";
    }
    cout << "" << endl;
}

//here i create a remove function that labels a slot as isDeleted
bool HashTable::remove(int key) {
    int hashCode = hash(key);

    for (int i = 0; i < TABLE_SIZE; i++) {
        int index = (hashCode + i * i) % TABLE_SIZE;
        //stop if slot is not in use
        if (!table[index].isOccupied && !table[index].isDeleted) {
            return false;
        }
        //update bucket values if key matches
        if (table[index].isOccupied && table[index].key == key) {
            table[index].isOccupied = false;
            table[index].isDeleted = true;
            return true;
        }
    }

    return false;
}


//creating function that updates clients follow up information and only removes from table if client subscribes. MOVE TO HASH.CPP
void HashTable::updateFollowups(AllClientData* clientFile, int capacity) {
    int id;
    cout << "Enter ID of client: ";
    cin >> id;

    for (int i = 0; i < capacity; ++i) {
        if (clientFile[i].clientInfo.id == id) {
            string input;
            cout << "Did you follow up? (yes/no): ";
            cin >> input;
            //if yes then increment followup and update day and month of contact
            if (input == "yes") {
                clientFile[i].campaignInfo.followups++;
                cout << "Day of contact: ";
                cin >> clientFile[i].campaignInfo.day;
                cout << "Month of contact: ";
                cin >> clientFile[i].campaignInfo.month;
                //update csv file accordingly
                ofstream outfile("bank_full.csv");
                if (outfile.is_open()) {
                    outfile << "age;job;marital;education;default;balance;housing;loan;contact;day;month;duration;;pdays;y;followUps\n";
                    for (int j = 0; j < capacity; j++) {
                        outfile << clientFile[j].clientInfo.age << ";"
                                << clientFile[j].clientInfo.job << ";"
                                << clientFile[j].clientInfo.marital << ";"
                                << clientFile[j].clientInfo.education << ";"
                                << clientFile[j].clientBankInfo.defaulted << ";"
                                << clientFile[j].clientBankInfo.balance << ";"
                                << clientFile[j].clientBankInfo.housing << ";"
                                << clientFile[j].clientBankInfo.loan << ";"
                                << clientFile[j].campaignInfo.contact << ";"
                                << clientFile[j].campaignInfo.day << ";"
                                << clientFile[j].campaignInfo.month << ";"
                                << clientFile[j].campaignInfo.duration << ";"
                                << clientFile[j].campaignInfo.pdays << ";"
                                << clientFile[j].campaignInfo.y << ";"
                                << clientFile[j].campaignInfo.followups << "\n";
                    }
                    outfile.close();
                }
            //only allow user to remove subscribed clients    
            cout << "Has the client subscribed? (yes/no): ";
            cin >> input;
            if (input == "yes") {
                clientFile[i].campaignInfo.y = "\"yes\"";
                //need to create remove function
                remove(id);
                cout << "Client removed from follow-up list.\n";
            }
        }
    }
}
cout << "-----------------------" << endl;
}

