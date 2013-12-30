/* prey.cpp
 *
 *
 * -- Jake Kosberg
 * -- CS 3A
 */

#include "prey.h"

int const Prey::breedIterations = 4;

Prey::Prey()
{
    ident = 1;
}

Prey::~Prey()
{

}

Coordinate Prey::move(vector<vector<int> > surroundings)
{
    moved = true;
    steps++;
    counter++;
    eligable = false;
    srand((unsigned int) time(0));
    vector<Coordinate> coords;
    for (int i = 0; i < surroundings.size(); i++)
        for (int j = 0; j < surroundings[i].size(); j++)
        {
            if (surroundings[i][j] == 0) // if there's no creature
                coords.push_back(Coordinate(int(i-(surroundings.size()/2)),
                                            int(j-(surroundings.size()/2))));
            else if (surroundings[i][j] == 1)
                eligable = true;
        }
    
    if (coords.size())
        return coords[rand() % coords.size()];
    else
        return Coordinate(0, 0);
}

Coordinate Prey::breed(vector<vector<int> > surroundings)
{
    if (!(counter == breedIterations))
        return Coordinate(0, 0);
    
    vector<Coordinate> coords;
    counter -= breedIterations;
    for (int i = 0; i < surroundings.size(); i++)
        for (int j = 0; j < surroundings[i].size(); j++)
            if (surroundings[i][j] == 0)
                coords.push_back(Coordinate(i-1, j-1));
    if (coords.size())
        return coords[rand() % coords.size()];
    else
        return Coordinate(0, 0);
}

Creature* Prey::clone(void)
{
    Prey* p = new Prey(*this);
    return p;
}

bool Prey::readyToDie(void)
{
    return false;
}