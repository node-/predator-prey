/* world.cpp
 *
 *
 * -- Jake Kosberg
 * -- CS 3A
 */

#include "world.h"

// Default constructor creates a 20x20 world.
World::World()
{
    populate(40,80);
    hasPlayer = false;
    steps = 0;
}

// Constructor for initial world dimensions.
World::World(int X, int Y)
{
    populate(X, Y);
    hasPlayer = false;
    steps = 0;
}

// Proper destructor for dynamically allocated Space objects.
World::~World()
{
    for (int i = 0; i < x; i++)
        delete [] grid[i];
    delete [] grid;
}

// Finds the number of instances an ID shows up in the world.
int World::idCount(int ident)
{
    int count = 0;
    for (int i = 0; i < x; i++)
        for (int j = 0; j < y; j++)
            if (grid[i][j].mob && grid[i][j].mob->ident == ident)
                count++;
    return count;
}

// Finds the number of hunters.
int World::hunterCount(void)
{
    return idCount(2);
}

// Finds the number of prey.
int World::preyCount(void)
{
    return idCount(1);
}

// Populates the Space **grid with X and Y dimensions.
void World::populate(int X, int Y)
{
    x = X;
    y = Y;
    srand((unsigned int) time(0));
    grid = new Space * [X];
    for (int i = 0; i < x; i++)
    {
        Space* tempgrid = new Space [Y];
        for (int j = 0; j < y; j++)
        {
            if (j % 8 == 0 && i > 20)
                tempgrid[j] = Space(true);
            else if (rand() % 10007 == 0)
                tempgrid[j] = Space(Hunter(true));
            else if (rand() % 2 == 0)
                tempgrid[j] = Space(Prey());
            else if (rand() % 8 == 0)
                tempgrid[j] = Space(Hunter());
            else
                tempgrid[j] = Space();
            grid[i] = tempgrid;
        }
    }
}

// Returns false iff all spaces have no creatures.
bool World::hasCreatures(void)
{
    for (int i = 0; i < x; i++)
        for (int j = 0; j < y; j++)
            if (grid[i][j].mob)
                return true;
    return false;
}

// Moves a creature from one coordinate to another coordinate.
void World::moveTo(Coordinate to, Coordinate from)
{
    if (x >= to.x && y >= to.y)
        // Read it like this: ontoThis.jump(jumpThisCreature)
        grid[to.x][to.y].jumpFrom(grid[from.x][from.y]);
}

void World::createOffspring(Coordinate to, Coordinate from)
{
    if (to == from)
        return;
    grid[to.x][to.y].copyFrom(grid[from.x][from.y]);
}

// Returns a 3x3 double vector of each ident of the creatures around point (X, Y).
vector< vector<int> > World::surroundings(int X, int Y, int fog)
{
    // Fill a 3x3 double vector with all -1s
    vector<vector<int> > surround;
    for (int i = 0; i < fog; i++)
    {
        vector<int> temp;
        for (int j = 0; j < fog; j++)
            temp.push_back(-1);
        surround.push_back(temp);
    }
    
    // Replace the -1s with the IDs of each creature
    for (int i = 0; i < x; i++)
        for (int j = 0; j < y; j++)
            if ((X >= i - fog/2 && X <= i + fog/2) &&
                (Y >= j - fog/2 && Y <= j + fog/2)) // if the block is adjacent
                surround[i-X+fog/2][j-Y+fog/2] = grid[i][j].mob? grid[i][j].mob->ident:
                                         grid[i][j].isWall()? -1: 0;
                // Surround[x][y] at corresponding point is equal to the mob's ID
                // unless there is no mob inside the space. In that case, set equal
                // to 0.
    
    // If there are still -1s in the vector, then those points are out of bounds
    return surround;
}

void World::moveCreatures(void)
{
    for (int k = 1; k < 3; k++)
        for (int i = 0; i < x; i++)
            for (int j = 0; j < y; j++)
                if (!grid[i][j].isWall() &&
                    grid[i][j].mob &&
                    grid[i][j].mob->ident == k &&
                    !grid[i][j].mob->hasMoved(steps))
                {
                    // Passes surroundings(i, j) to the creature at spot (i, j), then
                    // the creature decides where to move to. That new location is set
                    // to newLoc.
                    Coordinate newLoc = grid[i][j].mob->move(surroundings(i, j, 3));
                    newLoc.add(i, j);
                    moveTo(newLoc, Coordinate(i, j)); // Move creature from (i, j) to newLoc
                }
}

void World::breedCreatures(void)
{
    for (int k = 1; k < 3; k++)
        for (int i = 0; i < x; i++)
            for (int j = 0; j < y; j++)
                if (grid[i][j].mob &&
                    grid[i][j].mob->ident == k)
                {
                    // Breed works similarly to Move, but it calls createOffspring
                    // instead of moveTo, which copies the creature from the space.
                    // After breeding, the creatures die if their time is up.
                    if (grid[i][j].mob->eligable)
                    {
                        Coordinate newLoc = grid[i][j].mob->breed(surroundings(i, j, 3));
                        newLoc.add(i, j);
                        createOffspring(newLoc, Coordinate(i, j));
                    }
                    if (grid[i][j].mob->readyToDie())
                        grid[i][j].killCreature();
                }
}

// Moves the world one step forward.
void World::Step(void)
{
    steps++;
    moveCreatures();
    breedCreatures();
}

// Prints the world.
ostream& operator<<(ostream& out, const World& w)
{
    for (int i = 0; i < w.x; i++)
    {
        for (int j = 0; j < w.y; j++) {
            out << w.grid[i][j] << " ";
        }
        out << endl;
    }
    return out;
}