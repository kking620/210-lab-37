#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <numeric>
#include <list>
#include <map>

using namespace std;

int gen_hash_index(string& str);

int main() {
    long long grand_total = 0;
    int result = 0;
    string line;
    
    map<int, list<string>> hash_table;

    ifstream fin("lab-37-data-3.txt");

    if(!fin) {
        cout << "Could not open the requested data file.\n";
    }

    while (getline(fin, line)) {
        if(!line.empty()) {
            int hash_i = gen_hash_index(line);
            hash_table[hash_i].push_back(line);
        }
    }

    fin.close();

    int entries_shown = 0;
    int max_entries = 100;
    int entry_count = 1;

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
