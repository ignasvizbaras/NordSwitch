#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>

using namespace std;


void invalidBrackets(string filePath) {
    map<char, int> symbolsCount;
    vector<string> closingBracketsErrors;
    vector<string> openingBracketsErrors;
    char symbol;
    int line = 1;
    int column = 0;

    ifstream file(filePath);

    if (!file.is_open()) {
        cerr << "Can't open a file" << endl;
        exit(1);
    }

    while (file >> symbol) {
        column++;

        if (symbol == '\n') {
            line++;
            column = 0;
            continue;
        }

        symbolsCount[symbol]++;

        if (symbolsCount[']'] > symbolsCount['['] || symbolsCount['}'] > symbolsCount['{'] || symbolsCount[')'] > symbolsCount['(']) {
            closingBracketsErrors.push_back("Invalid bracket " + string(1, symbol) + " found at " + filePath + ":" + to_string(line) + ":" + to_string(column));
            symbolsCount[symbol]--;
            continue;
        }

        if (symbol == '[' || symbol == '{' || symbol == '(') {
            openingBracketsErrors.push_back("Invalid bracket " + string(1, symbol) + " found at " + filePath + ":" + to_string(line) + ":" + to_string(column));
        }
        if (symbol == ']' || symbol == '}' || symbol == ')') {
            openingBracketsErrors.pop_back();
            symbolsCount[symbol]--;
            if (symbol == ']') {
                symbolsCount['[']--;
                continue;
            }
            if (symbol == '}') {
                symbolsCount['{']--;
                continue;
            }
            if (symbol == ')') {
                symbolsCount['(']--;
                continue;
            }
        }
    }

    for (const auto& error : closingBracketsErrors) {
        cout << error << endl;
    }

    for (const auto& error : openingBracketsErrors) {
        cout << error << endl;
    }

    file.close();
}

int main() {
    string filePath;

    cout << "Enter path to your file: ";
    cin >> filePath;

    invalidBrackets(filePath);

    return 0;
}
