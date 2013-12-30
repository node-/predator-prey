/* This object holds the world object and runs all functions
 * for changing the world.
 *
 *
 * -- Jake Kosberg
 * -- CS 3A
 */

#ifndef _APP_H_
#define _APP_H_

#include "world.h"

#include <iostream>

class App
{
private:
    World world;
    
public:
    App();
    App(int argc, char **argv);
    ~App();
    int run();
};

#endif // _APP_H_
