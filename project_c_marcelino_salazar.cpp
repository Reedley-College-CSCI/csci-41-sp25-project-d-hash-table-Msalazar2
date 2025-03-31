/* TO RUN USE:
g++ -std=c++11 project_c_marcelino_salazar.cpp clients.cpp queue.cpp -o project_c_marcelino_salazar
./project_c_marcelino_salazar
*/

#include <iostream>
#include "clients.h"
#include "SortTracker.h"
#include "Queue.h"

using namespace std;

int main() {
    Clients viewClients; //this class pushes capacity to constructor
   
    while(true) {
    cout << "MAIN MENU" << endl;
    cout << "1. View all clients" << endl;
    cout << "2. Search ID" << endl;
    cout << "3. Add new client file" << endl;
    cout << "4. Remove client file" << endl;
    cout << "5. Sort Descending (highest to lowest balance)" << endl;
    cout << "6. View Trash bin" << endl;
    cout << "7. Restore client" << endl;
    cout << "8. Enqueue recently added client" << endl;
    cout << "9. Dequeue client" << endl;
    cout << "10. View Follow up queue" << endl;
    cout << "11. Quit" << endl;
    cout << "Enter option (1,2,3,4,5,6,7,8,9,10,11): ";
    int option;
    cin >> option;
    cout << "-----------------------" << endl;

    if (cin.fail()) {
        cout << "Invalid input. Enter valid input: 1,2,3,4,5,6,7,8,9,10,11" << endl;
        cout << "-----------------------" << endl;
        
    } else if (option == 1) {
        viewClients.fullprint();

    } else if (option == 2) {
        viewClients.search();

    } else if (option == 3) {
        viewClients.addClient();
    
    } else if (option == 4) {
        viewClients.removeClient();
    
    } else if (option == 5) {
        viewClients.sortClients();
        cout << "Clients sorted:\n";
        viewClients.fullprint();
    
    } else if (option == 6) {
        viewClients.printTrash();

    } else if (option == 7) {
        viewClients.restoreClient();

    } else if (option == 8) {
        viewClients.enqueueClient();

    } else if (option == 9) {
        viewClients.dequeueClient();

    } else if (option == 10) {
        viewClients.printQueue();

    } else if (option == 11) {
        cout << "Closing...";
        break;
    
    } else {
        cout << "Invalid input. Enter valid input: 1,2,3,4,5,6,7,8,9,10,11" << endl;
        cout << "-----------------------" << endl;
    }
}


    return 0;

}
