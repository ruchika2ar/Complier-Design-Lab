#include <iostream>
#include <vector>
#include <string>
#include <set>
using namespace std;

bool isLetter (char x) {
    if (x >= 'a' && x <= 'z') return true;
    else if (x >= 'A' && x <= 'Z') return true;
    else return false;
}

bool isDigit(char x) {
    if (x >= '0' && x <= '9') return true;
    else return false;
}

bool isDelimiter(char x) {
    if (x == ' ' || x == '\t' || x == '\n') return true;
    else return false;
}

void skipString (int& i, string in) {
    if (in[i] == '"') {
        i++;
        while (in[i] != '"') i++;
        i++;
    } else if (in[i] == '\'') i = i + 3;
    return;
}

void operators (vector<string> snippet) {
    for (int l = 0; l < snippet.size(); l++) {
        int i = 0;
        string in = snippet[l];
        int state = 0;
        while (i < in.size()) {
            char c = in[i];
            if (c == '"' || '\'') skipString(i, in);
            switch (state) {
            case 0:
                if (c == '<') state = 1;
                else if (c == '=') state = 5;
                else if (c == '>') state = 8;
                else if (c == '!') state = 12;
                else if (c == '+') state = 15;
                else state = 0;
                i++;
                break;

            case 1:
                if (c == '=') state = 2;
                else if (c == '<') state = 3;
                else {
                    state = 4;
                    i--;
                }
                i++;
                break;

            case 2:
                cout << "<=  -  Relational Operator" << endl;
                state = 0;
                break;

            case 3:
                cout << "<<  -  Bitwise Operator" << endl;
                state = 0;

                break;

            case 4:
                cout << "<  -  Relational Operator" << endl;
                state = 0;
                break;

            case 5:
                if (c == '=') state = 6;
                else {
                    state = 7;
                    i--;
                }
                i++;
                break;

            case 6:
                cout << "==  -  Relational Operator" << endl;
                state = 0;
                break;

            case 7:
                cout << "=  -  Assignment Operator" << endl;
                state = 0;
                break;

            case 8:
                if (c == '=') state = 9;
                else if (c == '>') state = 10;
                else {
                    state = 11;
                    i--;
                }
                i++;
                break;

            case 9:
                cout << ">=  -  Relational Operator" << endl;
                state = 0;
                break;

            case 10:
                cout << ">>  -  Bitwise Operator" << endl;
                state = 0;
                break;

            case 11:
                cout << ">  -  Relational Operator" << endl;
                state = 0;
                break;

            case 12:
                if (c == '=') state = 13;
                else {
                    state = 14;
                    i--;
                }
                i++;
                break;

            case 13:
                cout << "!=  -  Relational Operator" << endl;
                state = 0;
                break;

            case 14:
                cout << "!  -  Bitwise Operator" << endl;
                state = 0;
                break;

            case 15:
                if (c == '+') state = 16;
                else {
                    state = 17;
                    i--;
                }
                i++;
                break;

            case 16:
                cout << "++  -  Unary Operator" << endl;
                state = 0;
                break;

            case 17:
                cout << "+  -  Arithmetic Operator" << endl;
                state = 0;
                break;

            }
        }
    }
}


void identifiers (vector<string> snippet) {
    vector <string> k{"auto", "double", "int", "struct", "break", "else", "long", "switch", "case", "typedef", "char",
                      "return", "const", "float", "short", "unsigned", "continue", "for", "signed", "void", "do", "if", "while", "true",
                      "false", "bool", "new", "class", "delete", "using", "private", "public", "namespace", "this"};
    set <string> keywords(k.begin(), k.end());
    for (int l = 0; l < snippet.size(); l++) {
        int i = 0;
        string in = snippet[l];
        string cur;
        int state = 18;
        while (i < in.size()) {
            char c = in[i];
            if (c == '"' || '\'') skipString(i, in);
            switch (state) {
            case 18:
                if (isLetter(c)) {
                    state = 19;
                    cur.push_back(c);
                } else state = 18;
                i++;
                break;

            case 19:
                if (isLetter(c) || isDigit(c)) {
                    state = 19;
                    cur.push_back(c);
                }
                else {
                    state = 20;
                    i--;
                }
                i++;
                break;

            case 20:
                if (keywords.find(cur) != keywords.end()) cout << cur << "  -  Keyword" << endl;
                else cout << cur << "  -  Identifier" << endl;
                cur = "";
                state = 18;
                break;
            }
        }
    }
    return;
}

void numbers (vector<string> snippet) {
    for (int l = 0; l < snippet.size(); l++) {
        int i = 0;
        string in = snippet[l];
        string cur;
        int state = 21;
        while (i < in.size()) {
            char c = in[i];
            if (c == '"' || '\'') skipString(i, in);
            switch (state) {
            case 21:
                if (isDigit(c)) {
                    state = 22;
                    cur.push_back(c);
                } else {
                    state = 21;
                    cur = "";
                }
                i++;
                break;

            case 22:
                if (isDigit(c)) {
                    state = 22;
                    cur.push_back(c);
                } else if (c == 'e') {
                    state = 25;
                    cur.push_back(c);
                } else if (c == '.') {
                    state = 23;
                    cur.push_back(c);
                } else {
                    state = 28;
                    i--;
                }
                i++;
                break;

            case 23:
                if (isDigit(c)) {
                    state = 24;
                    cur.push_back(c);
                } else {
                    state = 21;
                    cur = "";
                }
                i++;
                break;

            case 24:
                if (isDigit(c)) {
                    state = 24;
                    cur.push_back(c);
                } else if (c == 'e') {
                    state = 25;
                    cur.push_back(c);
                } else {
                    state = 30;
                    i--;
                }
                i++;
                break;
            case 25:
                if (c == '+' || c == '-') {
                    state = 26;
                    cur.push_back(c);
                } else if (isDigit(c)) {
                    state = 27;
                    cur.push_back(c);
                } else {
                    state = 21;
                    cur = "";
                }
                i++;
                break;
            case 26:
                if (isDigit(c)) {
                    state = 27;
                    cur.push_back(c);
                } else {
                    state = 21;
                    cur = "";
                }
                i++;
                break;
            case 27:
                if (isDigit(c)) {
                    state = 27;
                    cur.push_back(c);
                } else {
                    state = 28;
                    i--;
                }
                i++;
                break;
            case 28:
                cout << cur << "  -  Number" << endl;
                cur = "";
                state = 21;
                break;
            case 29:
                cout << cur << "  -  Number" << endl;
                cur = "";
                state = 21;
                break;
            case 30:
                cout << cur << "  -  Number" << endl;
                cur = "";
                state = 21;
                break;
            }
        }
    }
}

void delimiters (vector<string>& snippet) {
    for (int l = 0; l < snippet.size(); l++) {
        int i = 0;
        string in = snippet[l];
        string cur;
        int state = 31;
        while (i < in.size()) {
            char c = in[i];
            if (c == '"' || '\'') skipString(i, in);
            switch (state) {
            case 31:
                if (isDelimiter(c)) state = 32;
                else state = 31;
                i++;
                break;

            case 32:
                if (isDelimiter(c)) state = 32;
                else {
                    state = 33;
                    i--;
                }
                i++;
                break;

            case 33:
                state = 31;
                break;

            }
        }
    }
}

void sequential(vector<string> snippet) {
    operators(snippet);
    identifiers(snippet);
    numbers(snippet);
    delimiters(snippet);
    return;
}

int main() {
    vector<string> snippet(0);
    while (true) {
        string in;
        getline(cin, in);
        if (in == "EXIT") break;
        cout << in << endl;
        snippet.push_back(in);
    }
    cout << endl;

    sequential(snippet);

    cout << endl;
    return 0;


}
