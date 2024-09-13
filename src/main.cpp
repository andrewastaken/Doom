#include <iostream>
#include "WADReader.h"

int main() {
    WADReader reader;
    reader.setWADFilePath("../assets/wad/DOOM.WAD");
    reader.loadWADFile();

    reader.readHeader();
    //reader.readDirectories();

    return 0;
}