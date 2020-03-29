#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

int main() {
    // This code accepts the meaningful token - 'ruchika jain'
    string in;
    getline(cin, in);
    int state = 0;
    vector<char> table(0);
    map <char, int> m;
    bool accepted = true;
    string ac = "ruchika jain";
    int i = 0;
    for (;i < ac.size(); i++) {
        if (in[i] == ac[i]) {
            if (m.find(in[i]) == m.end() && in[i] >= 'a' && in[i] <= 'z') {
                table.push_back(in[i]);
                m[in[i]] = i;
            }
        } else {
            accepted = false;
            break;
        }
    }

    if (accepted) {
        cout << "The string is ACCEPTED!";
    } else {
        cout << "The string is NOT ACCEPTED. There is error at index : " << i << "!";
    }

    cout << endl << "SYMBOL TABLE" << endl;
    for (int i = 0; i < table.size(); i++) {
        cout << table[i] << "   |   " << "<id," << i << ">" << endl;
    }
    return 0;
}
