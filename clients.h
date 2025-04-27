#ifndef CLIENTS_H
#define CLIENTS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "SortTracker.h"
#include "Queue.h"
#include "HashTable.h"

using namespace std;

struct ClientData {
    int id;
    int age;
    string job;
    string marital;
    string education;

    void print() const {
        cout << "ID Number: " << id << endl;
        cout << "Age: " << age << endl;
        cout << "Occupation: " << job << endl;
        cout << "Marital Status: " << marital << endl;
        cout << "Education: " << education << endl;
        cout << "-----------------------" << endl;
    }
};

struct ClientBankData {
    string defaulted; //could not use default since it is a keyword.
    int balance;
    string housing;
    string loan;
    
    void print() const {
        cout << "Default record: " << defaulted << endl;
        cout << "Average yearly balance: " << balance << endl;
        cout << "Housing Loans: " << housing << endl;
        cout << "Personal Loans: " << loan << endl;
        cout << "-----------------------" << endl;
    }
};

struct CampaignData {    
    string contact;
    int day;
    string month;
    int duration;
    int campaign;
    int pdays;
    int previous;
    string poutcome;
    string y;

    void print() const {
        cout << "Current Result: " << y << endl;
        cout << "Contact Type: " << contact << endl;
        cout << "Last day of the week contacted: " << day << endl;
        cout << "Last month contacted: " << month << endl;
        cout << "Call duration (sec): " << duration << endl;
        cout << "Days since last day contacted: " << pdays << endl;
        cout << "Number of contacts: " << previous << endl;
        cout << "Previous Result: " << poutcome << endl;
        cout << "-----------------------" << endl;
    }
};

struct AllClientData { //this struct is nested with previous 3 structs.
    ClientData clientInfo;
    ClientBankData clientBankInfo;
    CampaignData campaignInfo;
    
    void print() const {
        cout << "Client Information: " << endl;
        cout << "" << endl;
        clientInfo.print();
        cout << "Client Bank Information: " << endl;
        cout << "" << endl;
        clientBankInfo.print();
        cout << "Campaign Information: " << endl;
        cout << "" << endl;
        campaignInfo.print();
    }

};

class Clients;

class SinglyLinkedNode { //singly linked list to implement a trash bin.
    public:
    struct Node {
        AllClientData clientInfo;
        Node* next;
        
        Node(const AllClientData& data) {
            clientInfo = data;
            next = nullptr;
        }
    };
    
    class TrashList {
        private:
        Node* head;
        Node* tail;

        public:
        TrashList() {
            head = nullptr;
            tail = nullptr;
        }

        ~TrashList() {
            Node* current = head;
            while (current) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }
        //functions I will create in clients.cpp
        void Append(const AllClientData& deletedClient);
        void Prepend(const AllClientData& deletedClient);
        bool Search (int id) const;
        bool Remove(int id);
        bool Restore(Clients& clients, int id);
        void PrintDeletedClients() const;
    };
};

class Clients { //here I added a class to hold structs
    public:
    //here I create multiple structs to where the last struct is nested with the previous 3. This is critical for menu options.

        AllClientData* clientFile;
        int capacity;
        
        Clients();
        ~Clients();
        
        void sortClients();
        void loadfile();
        void search();
        void fullprint() const;
        void addClient();
        void removeClient();
        void restoreClient();
        void printTrash() const;
        void printQueue() const;
        void enqueueClient();
        void dequeueClient();
        void recentlyAdded();
        void followUps(HashTable& hashTable);


        private: 
         SinglyLinkedNode::TrashList trashbin;
         Queue followUpQueue;

         //helper functions to declare functions in private.
         int Partition(AllClientData* clientBalance, int lowIndex, int highIndex, SortTracker& tracker, bool isAscending);
         void QuickSort(AllClientData* clients, int lowIndex, int highIndex, SortTracker& tracker, bool isAscending);
    };
    
    #endif