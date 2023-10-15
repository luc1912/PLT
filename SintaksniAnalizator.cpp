#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

vector<string> input;
int rb = 0;
int space = 0;
string output;

void error();
void program(int offset);
void command_list(int offset);
void command(int offset);
void joining_command(int offset);
void for_loop(int offset);
void E(int offset);
void E_list(int offset);
void T(int offset);
void T_list(int offset);
void P(int offset);

string find_first_part() {
    size_t pos = input[rb].find(' ');
    string firstPart;
    firstPart = pos != string::npos ? input[rb].substr(0, pos) : input[rb];
    return firstPart;
}

void error() {
    if(input[rb] == "⏊") cout << "err kraj";
    else cout << "err " << input[rb];
    exit(0);
}

void program(int offset) {
    vector<string> primijeni = {"IDN", "KR_ZA", "⏊"};
    string firstPart = find_first_part();

    if(find(primijeni.begin(), primijeni.end(), firstPart) != primijeni.end()) {
        output = output + "<program>\n";
        output = output + string(offset+1, ' ') + "<lista_naredbi>\n";
        command_list(offset+1);
    }
    else error();
    cout << output;
}

void command_list(int offset) {
    vector<string> primijeni1 = {"IDN", "KR_ZA"};
    vector<string> primijeni2 = {"KR_AZ", "⏊"};
    string firstPart = find_first_part();

    if(find(primijeni1.begin(), primijeni1.end(), firstPart) != primijeni1.end()) {
        output = output + string(offset+1, ' ') + "<naredba>\n";
        command(offset+1);
        output = output + string(offset+1, ' ') + "<lista_naredbi>\n";
        command_list(offset+1);
    }

    else if(find(primijeni2.begin(), primijeni2.end(), firstPart) != primijeni2.end()) {
        output = output + string(offset+1, ' ') + "$\n";
    }

    else error();
}

void command(int offset) {
    size_t pos = input[rb].find(' ');
    string firstPart = find_first_part();

    if(firstPart == "IDN") {
        output = output + string(offset+1, ' ') + "<naredba_pridruzivanja>\n";
        joining_command(offset+1);
    }

    else if(firstPart == "KR_ZA") {
        output = output + string(offset+1, ' ') + "<za_petlja>\n";
        for_loop(offset+1);
    }

    else error();
}

void joining_command(int offset) {
    string firstPart = find_first_part();

    if(firstPart == "IDN") {
        output = output + string(offset+1, ' ') + input[rb++] + "\n";
        firstPart = find_first_part();
        if(firstPart == "OP_PRIDRUZI") {
            output = output + string(offset+1, ' ') + input[rb++] + "\n";
            output = output + string(offset+1, ' ') + "<E>\n";
            E(offset+1);
        }
        else error();
    }
    else error();
}

void for_loop(int offset) {
    string firstPart = find_first_part();

    if(firstPart == "KR_ZA") {
        output = output + string(offset+1, ' ') + input[rb++] + "\n";
        firstPart = find_first_part();
        if(firstPart == "IDN") {
            output = output + string(offset+1, ' ') + input[rb++] + "\n";
            firstPart = find_first_part();
            if(firstPart == "KR_OD") {
                output = output + string(offset+1, ' ') + input[rb++] + "\n";
                output = output + string(offset+1, ' ') + "<E>\n";
                E(offset+1);
                firstPart = find_first_part();
                if(firstPart == "KR_DO") {
                    output = output + string(offset+1, ' ') + input[rb++] + "\n";
                    output = output + string(offset+1, ' ') + "<E>\n";
                    E(offset+1);
                    output = output + string(offset+1, ' ') + "<lista_naredbi>\n";
                    command_list(offset+1);
                    firstPart = find_first_part();
                    if(firstPart == "KR_AZ") {
                        output = output + string(offset+1, ' ') + input[rb++] + "\n";
                    }
                    else error();
                }
                else error();
            }
            else error();
        }
        else error();
    }
    else error();
}

void E(int offset) {
    vector<string> primijeni = {"IDN", "BROJ", "OP_PLUS", "OP_MINUS", "L_ZAGRADA"};
    string firstPart = find_first_part();

    if(find(primijeni.begin(), primijeni.end(), firstPart) != primijeni.end()) {
        output = output + string(offset+1, ' ') + "<T>\n";
        T(offset+1);
        output = output + string(offset+1, ' ') + "<E_lista>\n";
        E_list(offset+1);
    }

    else error();
}

void E_list(int offset){
    vector<string> primijeni = {"IDN", "KR_ZA", "KR_DO", "KR_AZ", "D_ZAGRADA", "⏊"};
    string firstPart = find_first_part();

    if(firstPart == "OP_PLUS") {
        output = output + string(offset+1, ' ') + input[rb++] + "\n";
        output = output + string(offset+1, ' ') + "<E>\n";
        E(offset+1);
    }

    else if(firstPart == "OP_MINUS") {
        output = output + string(offset+1, ' ') + input[rb++] + "\n";
        output = output + string(offset+1, ' ') + "<E>\n";
        E(offset+1);
    }

    else if(find(primijeni.begin(), primijeni.end(), firstPart) != primijeni.end()) {
        output = output + string(offset+1, ' ') + "$\n";
    }

    else error();
}

void T(int offset) {
    vector<string> primijeni = {"IDN", "BROJ", "OP_PLUS", "OP_MINUS", "L_ZAGRADA"};
    string firstPart = find_first_part();

    if(find(primijeni.begin(), primijeni.end(), firstPart) != primijeni.end()) {
        output = output + string(offset+1, ' ') + "<P>\n";
        P(offset+1);
        output = output + string(offset+1, ' ') + "<T_lista>\n";
        T_list(offset+1);
    }

    else error();
}

void T_list(int offset) {
    vector<string> primijeni = {"IDN", "KR_ZA", "KR_DO", "KR_AZ", "D_ZAGRADA", "⏊", "OP_PLUS", "OP_MINUS"};
    string firstPart = find_first_part();

    if(firstPart == "OP_PUTA" || firstPart == "OP_DIJELI") {
        output = output + string(offset+1, ' ') + input[rb++] + "\n";
        output = output + string(offset+1, ' ') + "<T>\n";
        T(offset+1);
    }

    else if(find(primijeni.begin(), primijeni.end(), firstPart) != primijeni.end()) {
        output = output + string(offset+1, ' ') + "$\n";
    }

    else error();
}

void P(int offset) {
    string firstPart = find_first_part();

    if(firstPart == "OP_PLUS") {
        output = output + string(offset+1, ' ') + input[rb++] + "\n";
        output = output + string(offset+1, ' ') + "<P>\n";
        P(offset+1);
    }

    else if(firstPart == "OP_MINUS") {
        output = output + string(offset+1, ' ') + input[rb++] + "\n";
        output = output + string(offset+1, ' ') + "<P>\n";
        P(offset+1);
    }

    else if(firstPart == "L_ZAGRADA") {
        output = output + string(offset+1, ' ') + input[rb++] + "\n";
        output = output + string(offset+1, ' ') + "<E>\n";
        E(offset+1);
        firstPart = find_first_part();
        if(firstPart == "D_ZAGRADA") {
            output = output + string(offset+1, ' ') + input[rb++] + "\n";
        }
        else error();
    }

    else if(firstPart == "IDN") {
        output = output + string(offset+1, ' ') + input[rb++] + "\n";
    }

    else if(firstPart == "BROJ") {
        output = output + string(offset+1, ' ') + input[rb++] + "\n";
    }

    else error();
}

int main() {
    string line;
    while (getline(cin, line)) {
        input.push_back(line);
    }
    input.emplace_back("⏊");
    program(space);
}