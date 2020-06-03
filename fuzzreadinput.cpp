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

    FuzzReader fr(&Data, Size);

    vector<vector<Token>> res;

    //uint8_t length_str = Data[0];
    uint8_t length_str;
    memcpy(&length_str, Data, sizeof(length_str));
    // fr.NextBlock(&length_str, sizeof(length_str));
    length_str = setRange(length_str, 1, 5);

    string direction;
    fr.NextStr(&direction, length_str);

    uint8_t board_len;
    fr.NextBlock(&board_len, sizeof(uint8_t));

    string board;
    fr.NextStr(&board, board_len);

    res = readInput(board);
    
    score(res, direction);
    //DoSomethingInterestingWithMyAPI(Data, Size);
    return 0;  // Non-zero return values are reserved for future use.
}
