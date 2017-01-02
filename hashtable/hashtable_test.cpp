#include <iostream>
#include "hashtable.h"
using namespace std;

void size_test_table(kirthi::hashtable<int, int>& table) {
    cout << "The size of the table is currently: " << table.size() << endl;
}

void insert_test_table(kirthi::hashtable<int, int>& table) {
    table.insert(1, 1);
    table.insert(1, 999);
    table.insert(101, 101);
    table.insert(201, 101);
    table.insert(301, 101);
    table.insert(401, 101);
    table.insert(25, 10);
    table.insert(77, 2);
    table.insert(57, 68);
}

void contains_test_table(kirthi::hashtable<int, int>& table) {
    cout << "Table contains 101 ?: " << table.contains(101) << endl;
    cout << "Table contains 201 ?: " << table.contains(201) << endl;
    cout << "Table contains 301 ?: " << table.contains(301) << endl;
    cout << "Table contains 401 ?: " << table.contains(401) << endl;
    cout << "Table contains 77 ?: " << table.contains(77) << endl;
    cout << "Table contains 999 ?: " << table.contains(999) << endl;
}

void get_test_table(kirthi::hashtable<int, int>& table) {
    try { // get throws an error is key doesn't exist
        cout << "get(401)" << table.get(401) << endl;
    } catch (...) {
        cout << "Key doesn't exist" << endl;
    }
    
}

void remove_test_table(kirthi::hashtable<int, int>& table) {
    table.remove(101);
    cout << "After removing 101" << endl;
    table.print();
}

int main() {
    
    kirthi::hashtable<int, int> table;
    insert_test_table(table);
    table.print();    
    //contains_test_table(table);
    //get_test_table(table);
    //remove_test_table(table);
    
    cout << "Number of collisions: " << table.getCollisions() << endl;
}