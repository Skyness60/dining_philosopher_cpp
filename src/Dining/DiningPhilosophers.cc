#include "DiningPhilosophers.hh"
#include <iostream>
#include <stdexcept>
#include <thread>

DiningPhilosophers::DiningPhilosophers(int argc, char **argv)
{
    if (argc < 5 or argc > 6)
        throw std::invalid_argument("Not enough arguments");
    numPhilosophers = std::stoul(argv[1]);
    thinkTime = std::stoul(argv[2]);
    eatTime = std::stoul(argv[3]);
    sleepTime = std::stoul(argv[4]);
    if (numPhilosophers == 0 or thinkTime == 0 or eatTime == 0 or sleepTime == 0)
        throw std::invalid_argument("Invalid arguments");
    if (argc == 6)
    {
        unsigned int parsedMeals = std::stoul(argv[5]);
        if (parsedMeals == 0)
            throw std::invalid_argument("Invalid arguments");
        mealsPerPhilosopher = parsedMeals;
    }
    else
        mealsPerPhilosopher = std::nullopt;
}

DiningPhilosophers::~DiningPhilosophers()
{
}

void DiningPhilosophers::startSimulation()
{
    forks.reserve(numPhilosophers);
    for (unsigned int i = 0; i < numPhilosophers; i++)
        forks.emplace_back();

    for (unsigned int id = 0; id < numPhilosophers; id++)
    {
        unsigned int idLeft = id;
        unsigned int idRight = (id + 1) % numPhilosophers;
        if (mealsPerPhilosopher.has_value())
            philosophers.emplace_back(id, thinkTime, idLeft, idRight, eatTime,
                                      sleepTime, mealsPerPhilosopher.value(), forks);
        else
            philosophers.emplace_back(id, thinkTime, idLeft, idRight, eatTime,
                                      sleepTime, forks);
    }
}
