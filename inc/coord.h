#ifndef __COORD__
#define __COORD__

typedef struct _Coord
{
    int lin; /* vertical coordinate */
    int col; /* horizontal coordinate */
} Coord;

/**
 * @brief Return 1 if c1 and c2 are equal, 0 otherwise.
 *
 * @param c1 coordinates
 * @param c2 coordinates
 * @return int 1 or 0
 */
int coord_cmp(Coord c1, Coord c2);

/**
 * @brief Return the sum of c1 and c2.
 *
 * @param c1 coordinates
 * @param c2 coordinates
 * @return Coord c1 + c2
 */
Coord coord_add(Coord c1, Coord c2);

/**
 * @brief Return the difference between c1 and c2.
 *
 * @param c1 coordinates
 * @param c2 coordinates
 * @return Coord c1 - c2
 */
Coord coord_sub(Coord c1, Coord c2);

#endif