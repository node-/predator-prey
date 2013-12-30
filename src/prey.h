/* Prey object, child of Creature and contains all
 * functionality and intelligence for decision making.
 *
 *
 * -- Jake Kosberg
 * -- CS 3A
 */

#ifndef _PREY_H_
#define _PREY_H_

#include "creature.h"

class Prey: public Creature
{
private:
    static int const breedIterations;

public:
    Prey();
    ~Prey();
    
    Coordinate move(vector<vector<int> > surroundings);
    Coordinate breed(vector<vector<int> > surroundings);
    Creature* clone(void);
    
    bool readyToDie(void);
};

#endif // _PREY_H_