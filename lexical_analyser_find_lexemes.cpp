#include <iostream>
#include <vector>
#include <set>
using namespace std;

set<string> lexemes;

// remove comments
vector<string> remove_comments (vector<string>& snippet) {
    vector<string> n(0);
    bool search = false;
    bool prev = false;
    for (int l = 0; l < snippet.size(); l++) {
        string in = snippet[l];
        string x;
        for (int i = 0; i < in.size(); i++) {
            if (!search) {
                if (i + 1 < in.size() && in[i] == '/' && in[i + 1] == '/') break;
                else if (i + 1 < in.size() && in[i] == '/' && in[i + 1] == '*') {
                    search = true;
                    i++;
                } else x.push_back(in[i]);
            } else {
                if (i + 1 < in.size() && search && in[i] == '*' && in[i + 1] == '/') {
                    search = false;
                    i++;
                    if (i == in.size() - 1) prev = false;

                }
            }
        }
        if (x.size() > 0) {
            if (prev) {
                n[n.size() - 1] = n[n.size() - 1] + x;
                prev = false;
            } else {
                n.push_back(x);
            }
        }
        if (search && x.size() > 0) prev = true;
    }
    return n;
}

// identify operators
vector<string> operators (vector<string> snippet) {
    vector<string> op;
    for (int l = 0; l < snippet.size(); l++) {
        string in = snippet[l];
        for (int i = 0; i < in.size(); i++) {
            string x;
            if (in[i] == '<') {
                x.push_back(in[i]);
                if (i + 1 < in.size() && (in[i + 1] == '<' || in[i + 1] == '=')) {
                    i++;
                    x.push_back(in[i]);
                }
            } else if (in[i] == '>') {
                x.push_back(in[i]);
                if (i + 1 < in.size() || (in[i] == '>' || in[i] == '=') ) {
                    i++;
                    x.push_back(in[i]);
                }
            } else if (in[i] == '=') {
                x.push_back(in[i]);
                if (i + 1 < in.size() && in[i + 1] == '=') {
                    i++;
                    x.push_back(in[i]);
                }
            } else if (in[i] == '+') {
                x.push_back(in[i]);
                if (i + 1 < in.size() && (in[i + 1] == '=' || in[i + 1] == '+')) {
                    i++;
                    x.push_back(in[i]);
                }
            } else if (in[i] == '-') {
                x.push_back(in[i]);
                if (i + 1 < in.size() && (in[i + 1] == '=' || in[i + 1] == '-')) {
                    i++;
                    x.push_back(in[i]);
                }
            } else if (in[i] == '!') {
                x.push_back(in[i]);
                if (i + 1 < in.size() && in[i + 1] == '=') {
                    i++;
                    x.push_back(in[i]);
                }
            } else if (in[i] == '&') {
                x.push_back(in[i]);
                if (i + 1 < in.size() && in[i + 1] == '&') {
                    i++;
                    x.push_back(in[i]);
                }
            } else if (in[i] == '|') {
                x.push_back(in[i]);
                if (i + 1 < in.size() && in[i + 1] == '|') {
                    i++;
                    x.push_back(in[i]);
                }
            } else if (in[i] == '*') {
                x.push_back(in[i]);
                if (i + 1 < in.size() && in[i + 1] == '=') {
                    i++;
                    x.push_back(in[i]);
                }
            } else if (in[i] == '/') {
                x.push_back(in[i]);
                if (i + 1 < in.size() && in[i + 1] == '=') {
                    i++;
                    x.push_back(in[i]);
                }
            } else if (in[i] == '%') {
                x.push_back(in[i]);
                if (i + 1 < in.size() && in[i + 1] == '=') {
                    i++;
                    x.push_back(in[i]);
                }
            }  else if (i + 1 < in.size() && in[i] == '?' && in[i + 1] == '=') {
                x.push_back(in[i]);
                i++;
                x.push_back(in[i]);
            }
            if (x.size() > 0 && lexemes.find(x) == lexemes.end()) {
                op.push_back(x);
                lexemes.insert(x);
            }
        }
    }
    return op;
}

// identifying punctuations
vector<char> punctuations (vector<string> snippet) {
    vector<char> punct;
    set <char> p;
    for (int l = 0; l < snippet.size(); l++) {
        string in = snippet[l];
        for (int i = 0; i < in.size(); i++) {
            if (in[i] == ',' || in[i] == ';') {
                if (p.find(in[i]) == p.end()) {
                    punct.push_back(in[i]);
                    p.insert(in[i]);
                }
            }
        }
    }
    return punct;
}

// identifying parenthesis
vector<char> parenthesis (vector<string> snippet) {
    vector<char> par;
    set <char> p;
    for (int l = 0; l < snippet.size(); l++) {
        string in = snippet[l];
        for (int i = 0; i < in.size(); i++) {
            if (in[i] == '{' || in[i] == '}' || in[i] == '(' || in[i] == ')' || in[i] == '[' || in[i] == ']') {
                if (p.find(in[i]) == p.end()) {
                    par.push_back(in[i]);
                    p.insert(in[i]);
                }
            }
        }
    }
    return par;
}

// identifying keywords and identifiers
pair<vector<string>, vector<string>> keywords (vector<string> snippet) {
    vector<string> key;
    vector<string> iden;
    vector <string> k{"auto", "double", "int", "struct", "break", "else", "long", "switch", "case", "typedef", "char",
                      "return", "const", "float", "short", "unsigned", "continue", "for", "signed", "void", "do", "if", "while", "true",
                      "false", "bool", "new", "class", "delete", "using", "private", "public", "namespace", "this"};
    set <string> keyword(k.begin(), k.end());
    for (int l = 0; l < snippet.size(); l++) {
        string in = snippet[l];
        int i = 0;
        while (i < in.size()) {
            string x;
            if (in[i] == '"') {
                i++;
                while (in[i] != '"') i++;
                i++;
            } else if (in[i] == '\'') i = i + 3;
            else if ((in[i] >= 'a' && in[i] <= 'z') || (in[i] >= 'A' && in[i] <= 'Z')) {
                while ((in[i] >= 'a' && in[i] <= 'z') || (in[i] >= 'A' && in[i] <= 'Z') || (in[i] >= '0' && in[i] <= '9')) {
                    x.push_back(in[i]);
                    i++;
                    if (i >= in.size()) break;
                }
            } else i++;
            if (x.size() > 0 && lexemes .find(x) == lexemes.end()) {
                if (keyword.find(x) != keyword.end()) key.push_back(x);
                else iden.push_back(x);
                lexemes.insert(x);
            }
        }
    }
    return make_pair(iden, key);
}

// identifying numbers
vector<string> numbers (vector<string> snippet) {
    vector<string> num;
    for (int l = 0; l < snippet.size(); l++) {
        string in = snippet[l];
        int i = 0;
        while (i < in.size()) {
            string x;
            while (in[i] >= '0' && in[i] <= '9') {
                x.push_back(in[i]);
                i++;
                if (i >= in.size()) break;
            }
            if (x.size() > 0 && lexemes.find(x) == lexemes.end()) {
                num.push_back(x);
                lexemes.insert(x);
            }
            i++;
        }
    }
    return num;
}

// identifying literals
vector<string> literal (vector<string> snippet) {
    vector<string> lit;
    for (int l = 0; l < snippet.size(); l++) {
        string in = snippet[l];
        int i = 0;
        while (i < in.size()) {
            string x;
            if (in[i] == '"') {
                i++;
                while (i < in.size()) {
                    x.push_back(in[i]);
                    i++;
                    if (in[i] == '"') {
                        i++;
                        break;
                    }
                }
                if (x.size() > 0) lit.push_back(x);
            } else if (in[i] == '\'') {
                string x;
                i++;
                x.push_back(in[i]);
                i = i + 2;
                lit.push_back(x);
            }
            else i++;
        }
    }
    return lit;
}

int main () {
    vector<string> snippet(0);
    while (true) {
        string in;
        getline(cin, in);
        if (in == "EXIT") break;
        cout << in << endl;
        snippet.push_back(in);
    }

    cout << endl;

    snippet = remove_comments(snippet);
    vector<string> op = operators(snippet);
    vector<string> lit = literal(snippet);
    pair<vector<string>, vector<string>> p = keywords(snippet);
    vector<string> iden = p.first;
    vector<string> key = p.second;
    vector<string> num = numbers(snippet);
    vector<char> par = parenthesis(snippet);
    vector<char> punct = punctuations(snippet);
    cout << "Operators: ";
    for (int i = 0; i < op.size(); i++) {
        cout << op[i] ;
        if (i + 1 != op.size())cout << " ,  ";
    }
    cout << endl;
    cout << "Literals: ";
    for (int i = 0; i < lit.size(); i++) {
        cout << "\"" << lit[i] << "\"";
        if (i + 1 != lit.size()) cout << " ,  ";

    }
    cout << endl;
    cout << "Keywords: ";
    for (int i = 0; i < key.size(); i++) {
        cout  << key[i];
        if (i + 1 != key.size()) cout << " ,  ";
    }
    cout << endl;

    cout << "Numbers: ";
    for (int i = 0; i < num.size(); i++) {
        cout << num[i];
        if (i + 1 != num.size()) cout << " ,  ";

    }
    cout << endl;
    cout << "Identifiers: ";
    for (int i = 0; i < iden.size(); i++) {
        cout << iden[i];
        if (i + 1 != iden.size()) cout << " ,  ";
    }
    cout << endl;
    cout << "Punctuations: ";
    for (int i = 0; i < punct.size(); i++) {
        cout << punct[i];
        if (i + 1 != punct.size()) cout << " ,  ";

    }
    cout << endl;
    cout << "Parenthesis: ";
    for (int i = 0; i < par.size(); i++) {
        cout << par[i];
        if (i + 1 != par.size()) cout << " ,  ";

    }
    cout << endl;
    cout << endl << endl;
    cout << "SYMBOL TABLE" << endl;
    for (int i = 0; i < iden.size(); i++) {
        cout << iden[i] << "  |  <" << "id," << i + 1 << ">" << endl;
    } 
    return 0;
}
