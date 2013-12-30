/* app.cpp
 *
 *
 * -- Jake Kosberg
 * -- CS 3A
 */

#include "app.h"

#include <unistd.h>

using namespace std;

App::App()
{

}

App::App(int argc, char **argv)
{
    
}

App::~App()
{

}

int App::run()
{
    cout << "Hunter Count: " << world.hunterCount() << endl;
    cout << "Prey Count: " << world.preyCount() << endl;
    cin.ignore();
    int gen = 0;
    
    while (world.hasCreatures())
    {
        
        cout << "generation: " << gen << endl;
        cout << world << endl;
        gen++;
        world.Step();
        //cin.ignore();
        usleep(15000);
    }
    return 0;
}