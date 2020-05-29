#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>

#include "tree.h"

using namespace std;

int main() {
    vector<vector<Token>> res = readInput(
        " _,Red_S, _,Blue_S, _;"
        " _,Blue_T, _,Red_S, _;"
        " _, _, _, _, _;"
        " _, _,Red_S,Blue_T,Red_T;"
        " _,Red_S,Blue_S, _, _;"
    );
    cout << res.size() << endl;
    for (int i = 0; i < res.size(); i++) {
        for (int j = 0; j < res[i].size(); j++) {
            cout << res[i][j].player << res[i][j].height << i << j << endl;
        } 
    }
    map<string, int> result = score(res, "W");
    for (auto e : result) {
        cout << e.first << e.second << endl;
    }

    printf("=======\n");
}