/* Terrain and Environment variables
 *
 *
 * -- Jake Kosberg
 * -- CS 3A
 */

#ifndef _TERRAIN_H_
#define _TERRAIN_H_

#include <iostream>

class Terrain
{
private:
    int level; // 1 to 100
    
public:
    bool blocked;
    
    Terrain();
    Terrain(bool blocker);
    Terrain(Terrain const &T);
    
    void Block(bool b);
};

#endif // _TERRAIN_H_
