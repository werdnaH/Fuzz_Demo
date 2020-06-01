#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>

#include "tree.h"

using namespace std;


extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
    vector<vector<Token>> res;
    const uint8_t* min = Data;
    const uint8_t* max = Data + Size * sizeof(uint8_t);

    const uint8_t** Data_ptr = &Data;

    int row = *Data % 20;
    nextRange(Data_ptr, min, max, sizeof(uint8_t));

    int col = *Data % 20;
    nextRange(Data_ptr, min, max, sizeof(uint8_t));


    // create valid vector input
    for (int i = 0; i < row; i++) {
        vector<Token> tmp;
        for (int j = 0; j< col; j++) {
            Token t;
            memcpy(&t, Data, sizeof(Token));
            tmp.push_back(t);
            nextRange(Data_ptr, min, max, sizeof(Token));
        }
    }

    uint8_t length_str = getLength(Data, 1, 5);
    nextRange(Data_ptr, min, max, sizeof(uint8_t));

    string direction(reinterpret_cast<const char*>(Data), length_str);
    nextRange(Data_ptr, min, max, sizeof(direction));
    
    score(res, direction);
    return 0;  // Non-zero return values are reserved for future use.
}
