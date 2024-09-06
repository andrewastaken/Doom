#include <cstdint>
#include <string>
#include <vector>

struct Vertex {
    int16_t x;
    int16_t y;
};

struct Linedef {
    uint16_t start;
    uint16_t end;
    uint16_t flags;
    uint16_t lineType;
    uint16_t sectorTag;
    uint16_t rightSidedef;
    uint16_t leftSidedef;
};

class Map {
    public:
        Map(std::string name);
        ~Map();

        std::string getName();
        void addVertex(Vertex &vertex);
        void addLinedef(Linedef &linedef);

    private:
        std::string m_name;
        std::vector<Vertex> m_vertices;
        std::vector<Linedef> m_linedefs;
};