#include<iostream>
#include<map>
#include<string>
#include<vector>

using namespace std;
bool comment = false;
int counter = 0;

void splitLine(const string& line, vector<string>& split) {
    string word;
    for (char i : line) {
        if (i == ' ' || i == '\t') { // Include '\t' as a delimiter
            if (!word.empty()) {
                split.push_back(word);
                word = "";
            }
        } else {
            word += i;
        }
    }
    if (!word.empty()) {
        split.push_back(word);
    }
}

bool checkKR(const string& element, int row) {
    if(element == "za") {
        cout << "KR_ZA" << " " << row << " " << element << endl;
        return true;
    }
    if(element == "od") {
        cout << "KR_OD" << " " << row << " " << element << endl;
        return true;
    }
    if(element == "do") {
        cout << "KR_DO" << " " << row << " " << element << endl;
        return true;
    }
    if(element == "az") {
        cout << "KR_AZ" << " " << row << " " << element << endl;
        return true;
    }
    return false;
}

void check(string& element, int row) {
    bool kr = checkKR(element, row);
    if (kr) return;

    string sb;
    for (size_t i = 0; i < element.length(); i++) {
        char c = element[i];
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            sb += c;
        } else if (c >= '0' && c <= '9') {
            sb += c;
        } else {
            if (!sb.empty()) {
                if (sb[0] >= '0' && sb[0] <= '9') {
                    bool brojIRijec = false;
                    string number;
                    string word;
                    for (size_t j = 1; j < sb.length(); j++) {
                        char cj = sb[j];
                        if ((cj >= 'a' && cj <= 'z') || (cj >= 'A' && cj <= 'Z')) {
                            number = sb.substr(0, j);
                            word = sb.substr(j);
                            brojIRijec = true;
                            break;
                        }
                    }
                    if (brojIRijec) {
                        cout << "BROJ" << " " << row << " " << number << endl;
                        kr = checkKR(word, row);
                        if (!kr) {
                            cout << "IDN" << " " << row << " " << word << endl;
                        }
                        kr = false;
                    } else {
                        cout << "BROJ" << " " << row << " " << sb << endl;
                    }
                } else {
                    cout << "IDN" << " " << row << " " << sb << endl;
                }
                sb.clear();
            }

            if (c == '=') {
                cout << "OP_PRIDRUZI" << " " << row << " " << c << endl;
            } else if (c == '+') {
                cout << "OP_PLUS" << " " << row << " " << c << endl;
            } else if (c == '-') {
                cout << "OP_MINUS" << " " << row << " " << c << endl;
            } else if (c == '*') {
                cout << "OP_PUTA" << " " << row << " " << c << endl;
            } else if (c == '/') {
                if (i < element.length() - 1) {
                    if (element[i + 1] == '/') {
                        comment = true; // Assuming 'komentar' is a variable declared outside this function
                        return;
                    }
                }
                cout << "OP_DIJELI" << " " << row << " " << c << endl;
            } else if (c == '(') {
                cout << "L_ZAGRADA" << " " << row << " " << c << endl;
            } else if (c == ')') {
                cout << "D_ZAGRADA" << " " << row << " " << c << endl;
            }
        }
    }

    if (!sb.empty()) {
        if (sb[0] >= '0' && sb[0] <= '9') {
            bool brojIRijec = false;
            string number;
            string word;
            for (size_t j = 1; j < sb.length(); j++) {
                char cj = sb[j];
                if ((cj >= 'a' && cj <= 'z') || (cj >= 'A' && cj <= 'Z')) {
                    number = sb.substr(0, j);
                    word = sb.substr(j);
                    brojIRijec = true;
                    break;
                }
            }
            if (brojIRijec) {
                cout << "BROJ" << " " << row << " " << number << endl;
                kr = checkKR(word, row);
                if (!kr) {
                    cout << "IDN" << " " << row << " " << word << endl;
                }
                kr = false;
            } else {
                cout << "BROJ" << " " << row << " " << sb << endl;
            }
        } else {
            cout << "IDN" << " " << row << " " << sb << endl;
        }
        sb.clear();
    }

}


int main() {
    map<int, string> map;
    int mapKey = 0;
    vector<string> split;
    string line;
    getline(cin, line);

    while(!line.empty() || counter != 2) {
        counter = (line.empty()) ? counter + 1 : 0;
        map[mapKey++] = line;
        getline(cin, line);
    }

    for(int i = 0; i < map.size(); i++) {
        if(map[i].empty()) continue;
        splitLine(map[i], split);
        for(auto & j : split) {
            if(!comment) {
                check(j, i+1);
            }
            else {
                comment = false;
                break;
            }
        }
        split.clear();
    }

    return 0;
}