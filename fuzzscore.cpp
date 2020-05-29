#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>

#include "tree.h"

using namespace std;


string generationalFuzz(int row, int col);
string generationalFuzz(int row, int col) {
    
}


extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
    vector<vector<Token>> res;


    int row = rand() % 20;
    int col = rand() % 20;
     //  space of Token + space of direction
    if (Size < row * col * sizeof(Token) + 5 + sizeof(uint8_t)) {
        return 0;
    }
    // create valid vector input
    for (int i = 0; i < row; i++) {
        vector<Token> tmp;
        for (int j = 0; j< col; j++) {
            Token t;
            memcpy(&t, Data, sizeof(Token));
            tmp.push_back(t);
            Data += sizeof(Token);
        }
    }

    //uint8_t length_str = Data[0];
    uint8_t length_str;
    memcpy(&length_str, Data, sizeof(length_str));
    length_str %= 4; // make length_str go between 1 and 5
    length_str++;
    Data += sizeof(uint8_t);

    string direction(reinterpret_cast<const char*>(Data), length_str);
    //printf("direction %s\n", direction.c_str());
    Data += length_str;
    
    score(res, direction);
    //DoSomethingInterestingWithMyAPI(Data, Size);
    return 0;  // Non-zero return values are reserved for future use.
}
