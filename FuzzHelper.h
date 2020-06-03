#include <string>
using namespace std;

template<typename T>
void nextRange(T* destination, const uint8_t **ptr, size_t* size, size_t len) {
    if (len > *size) {
        memset(destination, 0, len);
        memcpy(destination, *ptr, *size);
        *size = 0;
        *ptr += *size;
        return;
    }
    memcpy(destination, *ptr, len);
    *size -= len;            
    *ptr += len;

} // */

uint8_t setRange(uint8_t length_str, int min, int max) {
    length_str %= max - min; // make length_str go between 1 and 5
    length_str += min; 
    return length_str;
}

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

struct FuzzReader {
    const uint8_t** pData;
    size_t size;
    FuzzReader() = default;
    FuzzReader(const uint8_t** d, size_t s) {
        pData = d;
        size = s;
    }
    template<typename T>
    void nextBlock(T* destination, size_t len) {
        if (len > *size) {
            memset(destination, 0, len);
            memcpy(destination, *pData, *size);
            *size = 0;
            *pData += *size;
            return;
        }
        memcpy(destination, *pData, len);
        *size -= len;            
        *pData += len;
    }

    void nextStr(string* destination, size_t len) {
        if (size < len) {
            string direction(reinterpret_cast<const char*>(*pData), size);
            direction.append(string(len - size, ' '));
            *destination = direction;
            *pData += size;
            size = 0;
            return;
        }
    }

};