#pragma once

#include <optional>
#include <vector>
#include "Philosopher.hh"

class DiningPhilosophers
{
    private:
        std::vector<Philosopher> philosophers;
        std::vector<Fork> forks;
        unsigned int numPhilosophers;
        unsigned int thinkTime;
        unsigned int eatTime;
        unsigned int sleepTime;
        std::optional<unsigned int> mealsPerPhilosopher;

    public:
        DiningPhilosophers(int argc, char **argv);
        ~DiningPhilosophers();

        void startSimulation();
};
