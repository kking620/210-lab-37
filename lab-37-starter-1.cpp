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
    
    ifstream fin("lab-37-data-3.txt");

    while (getline(fin, line)) {
        if(!line.empty()) {
            result = sum_ascii(line);
            grand_total += result;
        }
    }

    if(!fin) {
        cout << "Could not open the requested data file.\n";
    }

    cout << "The grand total of the ASCII values is: " << grand_total;

    fin.close();

    return 0;
}

int sum_ascii(string& str) {
    int sum = 0;
    for (char c : str) {
        sum += (int) c;
    }

    return sum;
}

/* 
These targets are present in the dataset and can be used for testing:
536B9DFC93AF
1DA9D64D02A0
666D109AA22E
E1D2665B21EA
*/
