#include "DiningPhilosophers.hh"
#include <iostream>
#include <stdexcept>
#include <thread>
#include <chrono>

DiningPhilosophers::DiningPhilosophers(int argc, char **argv)
{
    if (argc < 5 or argc > 6)
        throw std::invalid_argument("Not enough arguments");
    numPhilosophers = std::stoul(argv[1]);
    timeToDie = std::stoul(argv[2]);
    eatTime = std::stoul(argv[3]);
    sleepTime = std::stoul(argv[4]);
    thinkTime = 0;
    if (numPhilosophers == 0 or timeToDie == 0 or eatTime == 0 or sleepTime == 0)
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
    stopFlag = false;
}

DiningPhilosophers::~DiningPhilosophers()
{
}

void DiningPhilosophers::startSimulation()
{
    forks.reserve(numPhilosophers);
    philosophers.reserve(numPhilosophers);
    threads.reserve(numPhilosophers);
    for (unsigned int i = 0; i < numPhilosophers; i++)
        forks.emplace_back();

    for (unsigned int id = 0; id < numPhilosophers; id++)
    {
        unsigned int idLeft = id;
        unsigned int idRight = (id + 1) % numPhilosophers;
        if (mealsPerPhilosopher.has_value())
            philosophers.emplace_back(id, timeToDie, thinkTime, idLeft, idRight, eatTime,
                                      sleepTime, mealsPerPhilosopher.value(), forks, stopFlag, printMutex);
        else
            philosophers.emplace_back(id, timeToDie, thinkTime, idLeft, idRight, eatTime,
                                      sleepTime, forks, stopFlag, printMutex);
    }

    for (unsigned int i = 0; i < philosophers.size(); ++i)
        threads.emplace_back(&Philosopher::routine, &philosophers[i]);

    std::thread monitor([this]() {
        while (!stopFlag.load()) {
            auto nowMs = std::chrono::duration_cast<std::chrono::milliseconds>(
                             std::chrono::steady_clock::now().time_since_epoch())
                             .count();
            bool allDone = true;
            for (auto &p : philosophers) {
                long long delta = nowMs - p.getLastMealMs();
                if (delta >= static_cast<long long>(timeToDie)) {
                    std::lock_guard<std::mutex> lock(printMutex);
                    std::cout << "\033[31m" << nowMs << " " << p.getId() << " died\033[0m" << '\n';
                    stopFlag = true;
                    return;
                }
                if (!p.isDone())
                    allDone = false;
            }
            if (mealsPerPhilosopher.has_value() && allDone) {
                stopFlag = true;
                return;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    });

    for (auto &t : threads)
        if (t.joinable())
            t.join();
    if (monitor.joinable())
        monitor.join();
}
