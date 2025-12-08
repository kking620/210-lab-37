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

    //declares and initializes the variables that will be used to traverse the hash table to a predetermined amount
    int entries_shown = 0;
    int max_entries = 100;
    int entry_count = 1;

    //for loop that will traverse the hash table and output the first 100 values on our table
    for (const auto& pair : hash_table) {
        if (entries_shown >= max_entries)
            break;

        const string& first_code = pair.second.front();

        cout << "Entry #" << entry_count << ": " << first_code << endl;
        entries_shown++;
        entry_count++;
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

/* 
These targets are present in the dataset and can be used for testing:
536B9DFC93AF
1DA9D64D02A0
666D109AA22E
E1D2665B21EA
*/
