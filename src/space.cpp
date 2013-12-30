/* space.cpp
 *
 *
 * -- Jake Kosberg
 * -- CS 3A
 */

#include "space.h"

int Space::ident = 0;

Space::Space():
mob(NULL),
uid(ident++),
env()
{}

Space::Space(bool blocked):
uid(ident++),
env(blocked),
mob(NULL)
{}

Space::Space(Space const &s):
uid(ident++),
env(s.env),
mob(s.mob)
{}

Space::Space(Hunter const &h):
uid(ident++),
mob(new Hunter(h)),
env()
{}

Space::Space(Prey const &p):
uid(ident++),
mob(new Prey(p)),
env()
{}

Space::~Space()
{
    //if (mob)
        //delete mob;
}

bool Space::isWall(void) const
{
    return env.blocked;
}

bool Space::isEmpty(void) const
{
    return mob;
}

void Space::buildWall(void)
{
    env.Block(true);
}

void Space::killCreature(void)
{
    mob = NULL;
}

void Space::jumpFrom(Space &s)
{
    if (&s == this)
        return;
    if (mob)
        delete mob;
    mob = s.mob;
    s.killCreature();
}

void Space::copyFrom(Space &s)
{
    if (&s == this || !s.mob)
        return;
    mob = s.mob->clone();
}

ostream& operator<<(ostream& out, Space const &s)
{
    if (s.mob)
    {
        if (s.mob->ident == 1)
            out << "~";
        else if (s.mob->ident == 2)
            out << "H";
        else
            out << "*";
    }
    else if (s.isWall())
        out << "*";
    else
        out << " ";
    
    return out;
}