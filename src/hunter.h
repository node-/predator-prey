/* Predator object, child of Creature and contains all
 * functionality and intelligence for decision making.
 *
 *
 * -- Jake Kosberg
 * -- CS 3A
 */

#ifndef _HUNTER_H_
#define _HUNTER_H_

#include "creature.h"

class Hunter: public Creature
{
private:
    int eaten;
    
private:
    static int const breedIterations;
    static int const starveIterations;
    Coordinate lastMove;
    //int moveUtility();

public:
    Hunter();
    Hunter(Hunter const &h);
    Hunter(bool const b);
    ~Hunter();
    
    Coordinate move(vector<vector<int> > surroundings);
    Coordinate breed(vector<vector<int> > surroundings);
    Creature* clone(void);
    bool readyToDie(void);
    
};

#endif // _HUNTER_H_