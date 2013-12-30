/* This object creates and maintains the World. The world is stored
 * in a dynamically allocated double pointer Space variable. Each
 * Space object can hold a public creature object, but have other
 * variables stored with them as well (temperature, terrain, etc).
 *
 *
 * -- Jake Kosberg
 * -- CS 3A
 */

#ifndef _WORLD_H_
#define _WORLD_H_

#include "creature.h"
#include "prey.h"
#include "hunter.h"
#include "coordinate.h"
#include "space.h"

#include <vector>
#include <stdlib.h>

class World
{
private:
    // Environment variables
    int x, y, steps;
    Space **grid;
    bool hasPlayer; // experiment
    
    // Self-called functions
    int idCount(int ident);
    
    void populate(int X, int Y);
    void moveCreatures(void);
    void breedCreatures(void);

public:
    // Constructors
    World();
    World(int X, int Y);
    ~World();
    
    // Accessors
    bool hasCreatures(void);
    int hunterCount(void);
    int preyCount(void);
    vector< vector<int> > surroundings(int x, int y, int fog);
    
    // Mutators
    void moveTo(Coordinate to, Coordinate from);
    void createOffspring(Coordinate to, Coordinate from);
    void Step(void);
    
    // Operators
    friend ostream& operator<<(ostream& out, const World& w);
};

#endif // _WORLD_H_