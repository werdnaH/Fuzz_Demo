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
    //cout << Size << endl;
    vector<vector<Token>> res = readInput(
        " _,Red_S, _,Blue_S, _;"
        " _,Blue_T, _,Red_S, _;"
        " _, _, _, _, _;"
        " _, _,Red_S,Blue_T,Red_T;"
        " _,Red_S,Blue_S, _, _;"
    );

    if (Size < 5 + sizeof(uint8_t)) { // 1 byte for length and 5 byte for string
        return 0;
    }
    //uint8_t length_str = Data[0];
    uint8_t length_str;
    memcpy(&length_str, Data, sizeof(length_str));

    length_str %= 4; // make length_str go between 1 and 5
    length_str++;

    Data += sizeof(uint8_t);

    string direction(reinterpret_cast<const char*>(Data), length_str);
    //printf("direction %s\n", direction.c_str());

    score(res, direction);
    //DoSomethingInterestingWithMyAPI(Data, Size);
    return 0;  // Non-zero return values are reserved for future use.
}
