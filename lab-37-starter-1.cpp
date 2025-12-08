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
    else {
        while (getline(fin, line)) {
            //if the line is not empty, we will calculate the hash index and then add the string that we derived the hash index from to the hash table
            if(!line.empty()) {
                int hash_i = gen_hash_index(line);
                hash_table[hash_i].push_back(line);
            }
        }
    }

    //closes the data file
    fin.close();

    int choice;
    //while loop that continuously loops while the choice is not equal to 6
    while(true) {
        //calls the print menu function that displays the users options
        print_menu();
        //requests the user to input a menu action 
        cout << "Please enter your choice: ";
        cin >> choice;
        cin.ignore();

        //if the user input is not valid, then returns this message
        if (choice < 1 && choice > 6)
            cout << "Invalid input\n";
        //else a switch that uses the user input as an argument is called
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

//void function that displays the options that the users can perform
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

//void function that traverses the hash table in order to find a desired value
void search_for_key(const map<int, list<string>>& table) {
    string desired_code;
    cout << "Enter the 12 character code you wish to find: ";
    cin >> desired_code;
    cin.ignore();
    cout << endl;

    //if the desired code is not the correct length, then we will return to the main function with this error message
    if (desired_code.length() != 12) {
        cout << "Ivalid code. Must be 12 characters long.\n";
        return;
    }

    int hash_i = gen_hash_index(desired_code);
    auto it = table.find(hash_i);

    //this code block finds the desired code by traversing the key values
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

//void function that adds a new value to the hash table
void add_key(map<int, list<string>>& table) {
    string new_code;
    cout << "Enter the new 12-char code to add: ";
    cin >> new_code;
    cin.ignore();
    cout << endl;

    //if the code length is not the correct length, then return to the main function with this error message
    if (new_code.length() != 12) {
        cout << "Invalid code length. Must be 12 characters. Not added.\n";
        return;
    }
    
    //compares the desired value to add to the current values already present within the hash table, in order to determine if this value can be added to the table
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

//void function that removes the desired value from the hash table if it exists
void remove_key(map<int, list<string>>& table) {
    string target_code;
    cout << "Enter the 12-char code to remove: ";
    cin >> target_code;
    cin.ignore();
    cout << endl;


    int hash_i = gen_hash_index(target_code);
    auto map_it = table.find(hash_i);

    //this code block traverses the hash table and compares the values with our desired value, and if it is found within the hash table, removes it from the hash table
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

//void function that modifies a designated value of the hash table
void modify_key(map<int, list<string>>& table) {
    string old_code;
    string new_code;

    cout << "Enter the 12-char code to modify: ";
    cin >> old_code;
    cin.ignore();
    cout << endl;

    int hash_i_old = gen_hash_index(old_code);
    auto map_it = table.find(hash_i_old);

    //code block that searches for the desired code, that was specified above, removes it from the hash table, and calls the add_key() function in order to "modify" the desired value
    if (map_it != table.end()) {
        auto& code_list = map_it->second;
        bool found = false;
        for (auto list_it = code_list.begin(); list_it != code_list.end(); ++list_it) {
            if (*list_it == old_code) {
                found = true;
                cout << "Found " << old_code << endl;

                add_key(table);

                code_list.erase(list_it);
                if (code_list.empty()) {
                    table.erase(map_it);
                }
                
                return;
            }
        }
        if (!found) {
             cout << "Code not found in the list.\n";
        }
    } else {
        cout << "Code not found in the table.\n";
    }
}

/* 
These targets are present in the dataset and can be used for testing:
536B9DFC93AF
1DA9D64D02A0
666D109AA22E
E1D2665B21EA
*/
