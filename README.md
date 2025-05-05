
(Clear explanation of hash table operations, hashing function, collision handling, and time complexities.)


1. Hash Table Implementation:

   - Correct hash table structure implementation:(Hash table is implemented correctly, and data is stored and retrieved efficiently.)
      The hash table is implemented in hashtable.cpp and HashTable.h. I used a struct for ClientStatus, Bucket, and HashTable. The hashtable dynamically resizes when full and supports insertion, search, display, and removing clients based on their ID and subscription follow-up status.
   
   - Hashing function implementation:(Uses a suitable hashing function to distribute keys effectively.)
      Inside the HashTable.h under HashTable class. The hash function I used is a simple modulus operation on the client's ID (key):

      int hash(int key) const {
         return key % TABLE_SIZE;
      }
      This ensures distribution of keys within the bounds of the current table size.

   - Collision handling:(Implements proper collision handling using chaining or open addressing.)
      I used quadratic probing to handle collisions. When a collision occurs the index is incremented using the following code:
      index = (hashNum + i * i) % TABLE_SIZE;
      This reduces clustering and spreads out entries more evenly.

2. User Interface
   - Menu options for hash table management:(Includes options for adding, searching, removing, and displaying items.)
      All menu options are found inside clients.cpp under, Clients::followUps(HashTable& hashTable) function.

3. Integration with previous functionalities:
   - (UI seamlessly integrates hash table management with functionalities from previous projects.)
      AllClientData* is used to insert clientInfo, clientBankInfo, & campaignInfo when needed and to overwrite external csv when updating values (day, month, subscription status, etc.)

   - (Hash table interacts meaningfully with other components, such as linked list or dynamic array.)
      The hashtable relies on dynamic array clientFile[] from AllClientData for inserting, removing, and updating

   - Time complexity reporting:(Accurate explanation of time complexities for hash table operations in README.mdLinks to an external site.)
                 Best:     Worst:
      Insert():	O(1)	   O(n) (due to collisions and resizing)
      Search():	O(1)	   O(n) (probing through filled or deleted slots)
      Remove():	O(1)	   O(n) (worst case search before marking as deleted)


   - Handling of edge cases:(Handles cases like collisions, searching/removing non-existent items, and edge scenarios robustly.)
      In the insert() when no empty slots are found, the table is resized (doubled) and all entries are rehashed to new positions. I use cin.fail() in most inputs, range checks for day input, and string validation for month input which all prevent crashes or incorrect data.