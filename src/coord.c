#include "../inc/coord.h"

int coord_cmp(Coord c1, Coord c2)
{
    return (c1.lin == c2.lin) && (c1.col == c2.col);
}

Coord coord_add(Coord c1, Coord c2)
{
    Coord res;
    res.lin = c1.lin + c2.lin;
    res.col = c1.col + c2.col;
    return res;
}

Coord coord_sub(Coord c1, Coord c2)
{
    Coord res;
    res.lin = c1.lin - c2.lin;
    res.col = c1.col - c2.col;
    return res;
}