#ifndef POLYGON_H
#define POLYGON_H

#include <vector>

using namespace std;

enum gamer{X, O, XO, null};
class polygon
{
    gamer s;
    size_t siz;
    vector<vector<gamer>> p;

    bool setCellValue(size_t i, size_t j, gamer v);

public:
    polygon();
    polygon(size_t size);

    void polygonResize(size_t size);
    bool step(size_t i, size_t j);
    gamer getPlayer();
    gamer getCellValue(size_t i, size_t j);

    bool draw();
    bool checkIsWin(gamer symbol);
    gamer statusGame();

    void clear();
    size_t size();
};

#endif // POLYGON_H
