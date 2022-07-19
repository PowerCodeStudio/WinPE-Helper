#include <iostream>
#include <cstdio>
#include <cstring>
#include <io.h>
#include <string>
#pragma once

inline bool fileRead(const char* name) {
    int acsResult = _access(name, 04);
    if (acsResult == 0) return true;
    else return false;
}

inline bool fileWrite(const char* name) {
    int acsResult = _access(name, 06);
    if (acsResult == 0) return true;
    else return false;
}
