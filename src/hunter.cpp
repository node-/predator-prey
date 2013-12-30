/* hunter.cpp
 *
 *
 * -- Jake Kosberg
 * -- CS 3A
 */

#include "hunter.h"

int const Hunter::breedIterations = 100;
int const Hunter::starveIterations = 20;

Hunter::Hunter()
{
    ident = 2;
    eaten = false;
}

Hunter::Hunter(bool const b)
{
    ident = 2;
    eaten = false;
}

Hunter::Hunter(Hunter const &h)
{
    ident = h.ident;
    moved = h.moved;
    steps = h.steps;
    eligable = h.eligable;
    eaten = h.eaten;
}

Hunter::~Hunter()
{
    
}

/* -- Reflex Agent -- */
Coordinate Hunter::move(vector<vector<int> > surroundings)
{
    // Default state
    // The Hunter is not moving
    bool eating = false;
    // The Hunter has now moved
    moved = true;
    // The Hunter is not eligable to breed
    eligable = false;
    // Steps keeps track of which step the world is on
    steps++;
    // Tracks when the Hunter can breed
    counter++;
    // Basically a death counter that gets extended when the Hunter eats
    eaten--;
    
    // Influence the decision by seeding the pseudo-random number generation.
    if (rand() % 3 == 1)
        srand((unsigned int) time(0));
    else if (rand() % 3 == 2)
        srand((unsigned int) steps);
    else
        srand((unsigned int) rand());
    
    vector<Coordinate> coords; // All adjacent empty blocks
    vector<Coordinate> ally; // All adjacent coordinates of fellow Hunters
    for (int i = 0; i < surroundings.size(); i++)
        for (int j = 0; j < surroundings[i].size(); j++)
        {
            if (surroundings[i][j] == 2) // If there is an adjacent Hunter
            {
                eligable = true; // Eligable for breeding
                ally.push_back(Coordinate(i-1, j-1));
            }
            if (!eating)
            {
                // Default, if there is no Prey adjacent, this block will keep
                // control until it finds prey.
                if (surroundings[i][j] == 1) // if there is PREY
                {
                    eating = true; // change control to PREY mode (search only for prey)
                    eaten = starveIterations;
                    coords.clear(); // clear all non-prey spaces
                    coords.push_back(Coordinate(i-1, j-1));
                    // This causes Hunters to always choose the first Prey they come
                    // across, and consequently, the Hunters aggregate together
                    // by forming packs.
                    lastMove = Coordinate(i-1, j-1); /* -- Disable Pack AI -- */
                }
                else if (surroundings[i][j] == 0) // if there is empty SPACE
                    coords.push_back(Coordinate(i-1, j-1));
            }
            else
            {
                if (surroundings[i][j] == 1) // If the Hunter is eating and there's Prey
                    coords.push_back(Coordinate(i-1, j-1));
            }
        }
    if (ally.size() && coords.size() && rand() % 6 == 0)
    {
        // This causes Hunters to prefer potential movements (when eating or otherwise)
        // when they bring them closer to other Hunters. The Hunters prefer to be in
        // packs.
        int index = 0;
        for (int i = 0; i < coords.size(); i++)
            for (int j = 0; j < ally.size(); j++)
                if (coords[i].x == ally[j].x || coords[i].y == ally[j].y)
                    index = i;
        lastMove = coords[index];
    }
    else if (coords.size())
    {
        // This causes Hunters to go in a straight line if that path seems like it
        // will benefit them.
        for (int i = 0; i < coords.size(); i++)
            if (coords[i] == lastMove) // If the move candidate is equal to the Last Move
                return coords[i]; // Do that move
        lastMove = coords[rand() % coords.size()]; // otherwise, pick a random movement
    }
    else
        // There is no movementd to make.
        lastMove = Coordinate(0, 0);
    
    return lastMove;
}

Coordinate Hunter::breed(vector<vector<int> > surroundings)
{
    if (!(counter == breedIterations))
        return Coordinate(0, 0);
    //return Coordinate(0, 0); // Disable Breeding
    
    vector<Coordinate> coords;
    counter -= breedIterations;
    for (int i = 0; i < surroundings.size(); i++)
        for (int j = 0; j < surroundings[i].size(); j++)
            if (surroundings[i][j] == 0 || surroundings[i][j] == 1)
                coords.push_back(Coordinate(i-1, j-1));
    if (coords.size())
        return coords[rand() % coords.size()];
    else
        return Coordinate(0, 0);
}

Creature* Hunter::clone(void)
{
    Hunter* h = new Hunter(*this);
    return h;
}

bool Hunter::readyToDie(void)
{
    //return false; // Disable dying
    return eaten <= 0;
}