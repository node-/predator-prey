/* Abstract Creature template for Hunter and Prey.
 *
 *
 * -- Jake Kosberg
 * -- CS 3A
 */

#ifndef _CREATURE_H_
#define _CREATURE_H_

#include "coordinate.h"

#include <iostream>
#include <vector>

using namespace std;

class Creature
{
public:
    bool moved, eligable;
    int counter, steps, ident;
    
    Creature();
    virtual ~Creature();
    bool hasMoved(int pos);
    
    virtual bool readyToDie(void) = 0;
    virtual Creature* clone(void) = 0;
    virtual Coordinate move(vector<vector<int> > surroundings) = 0;
    virtual Coordinate breed(vector<vector<int> > surroundings) = 0;
    
    friend ostream& operator<<(ostream& out, Creature c);
    Creature& operator=(Creature const &copy);
};


#endif // _CREATURE_H_
