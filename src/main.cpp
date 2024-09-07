#include <iostream>
#include "WADLoader.h"

int main() {
    WADLoader loader("D://Projects//Doom//assets//wad//DOOM.WAD");
    loader.loadWADFile();
    loader.readDirectories();
    return 0;
}