#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <numeric>
#include <list>
#include <map>

using namespace std;

//prototype function that will calculate our hash index for the given string value
int gen_hash_index(string& str);
void print_menu();
void print_first_100_entries(const map<int, list<string>>& table);
void search_for_key(const map<int, list<string>>& table);
void add_key(map<int, list<string>>& table);
void remove_key(map<int, list<string>>& table);
void modify_key(map<int, list<string>>& table);

int main() {
    //declaring the line string variable that will store the lines from our data file
    string line;
    
    //declaring our map which will store keys as integers and the values are lists of strings
    map<int, list<string>> hash_table;

    //opens the external data file with the given name
    ifstream fin("lab-37-data-3.txt");

    //if we cannot open the data file, return this message
    if(!fin) {
        cout << "Could not open the requested data file.\n";
    }

    //while loop that will continuously run until it has traversed the entirety of the data file
    while (getline(fin, line)) {
        //if the line is not empty, we will calculate the hash index and then add the string that we derived the hash index from to the hash table
        if(!line.empty()) {
            int hash_i = gen_hash_index(line);
            hash_table[hash_i].push_back(line);
        }
    }

    //closes the data file
    fin.close();

    int choice;
    while(true) {
        print_menu();
        cout << "Please enter your choice: ";
        cin >> choice;

        if (choice < 1 && choice > 6)
            cout << "Invalid input\n";
        else {
            switch(choice) {
                case 1:
                    print_first_100_entries(hash_table);
                    break;
                case 2:
                    search_for_key(hash_table);
                    break;
                case 3:
                    add_key(hash_table);
                    break;
                case 4:
                    remove_key(hash_table);
                    break;
                case 5:
                    modify_key(hash_table);
                    break;
                case 6:
                    "Exiting program\n";
                    break;
            }
        }

        if (choice == 6)
            break;
    }

    return 0;
}

//int function that calculates the hash index for our string argument and returns it to the main program
int gen_hash_index(string& str) {
    int hash_index  = 0;
    for (char c : str) {
        hash_index  += (int) c;
    }

    return hash_index ;
}

void print_menu() {
    cout << "Menu:\n";
    cout << "1. Print first 100 entries\n";
    cout << "2. Search for a key\n";
    cout << "3. Add a new code\n";
    cout << "4. Remove a code\n";
    cout << "5. Modify a code\n";
    cout << "6. Exit\n";
}

void print_first_100_entries(const map<int, list<string>>& table){
    //declares and initializes the variables that will be used to traverse the hash table to a predetermined amount
    int entries_shown = 0;
    int max_entries = 100;
    int entry_count = 1;

    //for loop that will traverse the hash table and output the first 100 values on our table
    for (const auto& pair : table) {
        if (entries_shown >= max_entries)
            break;

        const string& first_code = pair.second.front();

        cout << "Entry #" << entry_count << ": " << first_code << endl;
        entries_shown++;
        entry_count++;
    }
}

void search_for_key(const map<int, list<string>>& table) {
    string desired_code;
    cout << "Enter the 12 character code you wish to find: ";
    getline(cin, desired_code);
    cout << endl;

    if (desired_code.length() != 12) {
        cout << "Ivalid code. Must be 12 characters long.\n";
        return;
    }

    int hash_i = gen_hash_index(desired_code);
    auto it = table.find(hash_i);

    if (it != table.end()) {
        for (const string& data_code : it->second) {
            if (data_code == desired_code) {
            cout << "Found code " << desired_code << "at hash index " << hash_i << endl;
            return;
            }
        }
        cout << "The desired code was not found in the hash table\n";
    }
}

void add_key(map<int, list<string>>& table) {
    string new_code;
    cout << "Enter the new 12-char code to add: ";
    getline(cin, new_code);

    if (new_code.length() != 12) {
        cout << "Invalid code length. Must be 12 characters. Not added.\n";
        return;
    }
    
    int hash_i = gen_hash_index(new_code);
    auto it = table.find(hash_i);
    bool exists = false;
    if (it != table.end()) {
        for (const string& data_code : it->second) {
            if (data_code == new_code) {
                exists = true;
                break;
            }
        }
    }

    if (exists) {
        cout << "Error: This code already exists in the table.\n";
    } else {
        table[hash_i].push_back(new_code);
        cout << "Successfully added code: " << new_code << " at index " << hash_i << ".\n";
    }
}

void remove_key(map<int, list<string>>& table) {
    string target_code;
    cout << "Enter the 12-char code to remove: ";
    getline(cin, target_code);

    int hash_i = gen_hash_index(target_code);
    auto map_it = table.find(hash_i);

    if (map_it != table.end()) {
        auto& code_list = map_it->second;
        for (auto list_it = code_list.begin(); list_it != code_list.end(); ++list_it) {
            if (*list_it == target_code) {
                code_list.erase(list_it);
                cout << "Removed code: " << target_code << " from index " << hash_i << ".\n";
                
                if (code_list.empty()) {
                    table.erase(map_it);
                    cout << "Index " << hash_i << " is now empty and removed from the map.\n";
                }
                return;
            }
        }
    }
    cout << "Code not found in the table. Nothing removed.\n";
}

/* 
These targets are present in the dataset and can be used for testing:
536B9DFC93AF
1DA9D64D02A0
666D109AA22E
E1D2665B21EA
*/
