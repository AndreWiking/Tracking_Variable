
#include "LogController.h"

std::string hex_to_string(unsigned long long val)
{
    char hexString[2 * sizeof(unsigned long long) + 1];
    sprintf(hexString, "%llX", val);
    return {hexString};
}