/* creature.cpp
 *
 *
 * -- Jake Kosberg
 * -- CS 3A
 */

#include "creature.h"

Creature::Creature()
{
    ident = 0;
    moved = false;
    steps = 0;
    counter = 0;
    eligable = false;
}

Creature::~Creature()
{
    
}

bool Creature::hasMoved(int pos)
{
    if (moved == true && steps == pos)
        return true;
    return false;
}

Creature& Creature::operator=(Creature const &copy)
{
    if (&copy == this)
        return *this;
    steps = copy.steps;
    ident = copy.ident;
    moved = copy.moved;
    return *this;
}

ostream& operator<<(ostream& out, Creature *c)
{
    out << c->ident;
    return out;
}