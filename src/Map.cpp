#include "Map.h"

Map::Map(std::string name) {
    m_name = name;
}

Map::~Map() {
    // TODO
}

std::string Map::getName() {
    return m_name;
}

void Map::addVertex(Vertex &vertex) {
    m_vertices.push_back(vertex);
}

void Map::addLinedef(Linedef &linedef) {
    m_linedefs.push_back(linedef);
}