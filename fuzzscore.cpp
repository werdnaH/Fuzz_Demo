#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>

#include "tree.h"
#include "FuzzHelper.h"

using namespace std;


extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }
    
    vector<vector<Token>> res;

    const uint8_t** Data_ptr = &Data;
    int row;
    nextRange(&row, Data_ptr, &Size, sizeof(row));
    row %= 20;

    int col;
    nextRange(&col, Data_ptr, &Size, sizeof(col));
    col %= 20;

    // create valid vector input
    for (int i = 0; i < row; i++) {
        vector<Token> tmp;
        for (int j = 0; j < col; j++) {
            Token t;
            // both player and height is represent in a single char
            GetStr(&(t.player), Data_ptr, &Size, 1); 
            GetStr(&(t.height), Data_ptr, &Size, 1);
            tmp.push_back(t);    
        }
        res.push_back(tmp);
    }
    
    uint8_t length_str;
    nextRange(&length_str, Data_ptr, &Size, sizeof(length_str));
    length_str = setRange(length_str, 1, 5);

    string direction;
    GetStr(&direction, Data_ptr, &Size, length_str);

    score(res, direction);
    return 0;  // Non-zero return values are reserved for future use. */
}
