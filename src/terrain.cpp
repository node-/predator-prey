/* terrain.cpp
 *
 *
 * -- Jake Kosberg
 * -- CS 3A
 */

#include "terrain.h"

Terrain::Terrain():
blocked(false),
level(0)
{}

Terrain::Terrain(bool blocker):
level(100),
blocked(blocker)
{}

Terrain::Terrain(Terrain const &T):
level(T.level),
blocked(false)
{}

void Terrain::Block(bool b)
{
    blocked = b;
}