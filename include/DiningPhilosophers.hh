#pragma once

#include <optional>
#include <vector>
#include <thread>
#include <atomic>
#include <mutex>
#include "Philosopher.hh"

class DiningPhilosophers
{
    private:
        std::vector<Philosopher> philosophers;
        std::vector<std::thread> threads;
        std::vector<Fork> forks;
        unsigned int numPhilosophers;
        unsigned int timeToDie;
        unsigned int thinkTime;
        unsigned int eatTime;
        unsigned int sleepTime;
        std::optional<unsigned int> mealsPerPhilosopher;
        std::atomic<bool> stopFlag;
        std::mutex printMutex;

    public:
        DiningPhilosophers(int argc, char **argv);
        ~DiningPhilosophers();

        void startSimulation();
};
