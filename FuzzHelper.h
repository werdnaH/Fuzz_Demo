#include <string>
using namespace std;

void GetStr(string* destination, const uint8_t** source, size_t* size, size_t len) {
    if (*size < len) {
        string direction(reinterpret_cast<const char*>(*source), *size);
        direction.append(string(len - *size, ' '));
        *destination = direction;
        *source += *size;
        *size = 0;
        return;
    }
    string direction(reinterpret_cast<const char*>(*source), len);
    *destination = direction;
    *source += len;
    *size -= len;
}