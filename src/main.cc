#include "DiningPhilosophers.hh"
#include <iostream>

int main(int argc, char **argv)
{
    try
    {
        DiningPhilosophers app(argc, argv);
        std::cout << "Starting simulation..." << std::endl;
        app.startSimulation();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
