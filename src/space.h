/* This object holds the creatures in the world, and also contains
 * other information dependant on Terrain or other features.
 *
 *
 * -- Jake Kosberg
 * -- CS 3A
 */

#ifndef _SPACE_H_
#define _SPACE_H_

#include "creature.h"
#include "hunter.h"
#include "prey.h"
#include "terrain.h"

#include <iostream>

class Space
{
private:
    Terrain env; // environment type
    static int ident;
    int uid;
    
public:
    Creature *mob;
    
    // Constructors
    Space();
    Space(bool blocked);
    Space(Space const &s);
    Space(Hunter const &h);
    Space(Prey const &p);
    ~Space();
    
    // Accessors
    bool isEmpty(void) const;
    bool isWall(void) const;
    
    // Mutators
    void buildWall(void);
    void killCreature(void);
    void jumpFrom(Space &s);
    void copyFrom(Space &s);
    
    // Operators
    friend ostream& operator<<(ostream& out, Space const &s);
    
    
};

#endif // _SPACE_H_
