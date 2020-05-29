#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <signal.h>
#include <string.h>
using namespace std;

struct Token {
    string player;
    string height;
    Token() = default;
    Token(string p, string h) {
        player = p;
        height = h;
    }
};


vector<vector<Token>> readInput(string input);


map<string, int> score(vector<vector<Token>> board, string direct);


bool isBlocked(vector<vector<Token>> board, int i, int j, int dx, int dy, map<string, int>);






vector<vector<Token>> readInput(string input) {
    vector<vector<Token>> ret;
    stringstream ss(input);
    string tokens;
    while (getline(ss, tokens, ';')) {
        vector<Token> row;
        stringstream ss_inner(tokens);
        string token;
        //cout << tokens << endl;
        while (getline(ss_inner, token, ',')) {
            row.push_back(Token(
                token.substr(0, token.find('_')), 
                token.substr(token.find('_') + 1))
            );
            //cout << token << row.back().height << endl;
        }
        ret.push_back(row);
    }
    return ret;
}

map<string, int> score(vector<vector<Token>> board, string direct) {
    map<string, int> record;
    map<string, int> order;
    order["S"] = 1;
    order["T"] = 2;
    order["V"] = 3;
    int dx = 0;
    int dy = 0;
    if (direct == "N") {
        dx = 1;
    } else if (strcmp(direct.c_str(), "S") == 0) {
        dx = -1;
    } else if (strcmp(direct.c_str(), "E") == 0) {
        dy = 1;
    } else if (strcmp(direct.c_str(), "BAD") == 0) { 
        raise(SIGSEGV); // this is a pretend bug
    } else {
         dy = -1;
    }
    
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[0].size(); j++) {
            string name = board[i][j].player;
            //cout << i << j << name << board[i][j].height << "============" << endl;
            if (name != " " && !isBlocked(board, i, j ,dx, dy, order))  {
                //cout << "score" << i << j << endl;
                if (!record.count(name)) {
                    record[name] = 0;
                }
                if (board[i][j].height == "S") {
                    record[name]++;
                } else if (board[i][j].height == "T") {
                    record[name] += 2;
                } else {
                    record[name] += 3;
                }
            }
        }
    }
    return record;
}


bool isBlocked(vector<vector<Token>> board, int i, int j, int dx, int dy, map<string, int> order) {
    int oriOrder = order[board[i][j].height];
    for (int h = 1; h <= 3; h++) {
        i += dx;
        j += dy;
        //cout << i << j << "|" << board[i][j].height << "|" << h << endl;
        if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size()) {
            return false;
        }
        int curOrder = order[board[i][j].height];
        if (h == 1 && curOrder >= oriOrder) {
            return true;
        } else if (h == 2 && curOrder >= oriOrder && curOrder >= 2) {
            return true;
        } else if (h == 3 && curOrder >= oriOrder && curOrder >= 3) {
            return true;
        }
    }
    return false;
}