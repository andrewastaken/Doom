#include "WADReader.h"
#include <iostream>

int main() {
    std::string WADFilePath = "../wad/DOOM.WAD";

    WADReader reader(WADFilePath);

    return 0;
}