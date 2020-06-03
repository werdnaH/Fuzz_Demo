#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>

#include "tree.h"
#include "FuzzHelper.h"

using namespace std;


string generationalFuzz(int row, int col);
string generationalFuzz(int row, int col) {
    
}


extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
    vector<vector<Token>> res;
    //160 byte for board + 5 byte direction + 2 byte for their length
    if (Size < 165 + 2 * sizeof(uint8_t)) {
        return 0;
    }
    //uint8_t length_str = Data[0];
    uint8_t direct_len;
    memcpy(&direct_len, Data, sizeof(direct_len));
    direct_len %= 4; // make direct_len go between 1 and 5
    direct_len++;
    Data += sizeof(uint8_t);

    string direction(reinterpret_cast<const char*>(Data), direct_len);
    //printf("direction %s\n", direction.c_str());
    Data += direct_len;


    uint8_t board_len;
    memcpy(&board_len, Data, sizeof(board_len));
    board_len %= 160; // generate maximum around 9*9
    board_len++;
    Data += sizeof(uint8_t);

    string board(reinterpret_cast<const char*>(Data), board_len);
    Data += board_len;

    res = readInput(board);
    
    score(res, direction);
    //DoSomethingInterestingWithMyAPI(Data, Size);
    return 0;  // Non-zero return values are reserved for future use.
}
