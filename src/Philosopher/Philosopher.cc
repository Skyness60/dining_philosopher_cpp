#include "Philosopher.hh"
#include <thread>
#include <iostream>

namespace {
constexpr const char* kReset = "\033[0m";
constexpr const char* kFork = "\033[33m";
constexpr const char* kThink = "\033[36m";
constexpr const char* kEat = "\033[32m";
constexpr const char* kSleep = "\033[35m";

long long nowMs() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
               std::chrono::steady_clock::now().time_since_epoch())
        .count();
}

void sleepWithStop(unsigned int durationMs, std::atomic<bool>& stopFlag) {
    unsigned int slept = 0;
    const unsigned int step = 1;
    while (slept < durationMs && !stopFlag.load()) {
        unsigned int chunk = std::min(step, durationMs - slept);
        std::this_thread::sleep_for(std::chrono::milliseconds(chunk));
        slept += chunk;
    }
}
}

Philosopher::Philosopher(unsigned int philosopherId, unsigned int doneTime, unsigned int thinkTime,
                         unsigned int idLeft, unsigned int idRight,
                         unsigned int eatTime, unsigned int sleepTime, std::vector<Fork> &forks,
                         std::atomic<bool>& stopFlag, std::mutex& printMutex)
    : id(philosopherId), doneTime(doneTime), thinkTime(thinkTime), idLeft(idLeft), idRight(idRight),
      eatTime(eatTime), sleepTime(sleepTime),
      mealsPerPhilosopher(std::nullopt), state(THINKING), forks(forks),
      lastMealMs(nowMs()), done(false), stopFlag(stopFlag), printMutex(printMutex), timeToDie(doneTime)
{
    std::cout << "Philosopher " << id << " created" << std::endl;
}

Philosopher::Philosopher(unsigned int philosopherId, unsigned int doneTime, unsigned int thinkTime,
                         unsigned int idLeft, unsigned int idRight,
                         unsigned int eatTime, unsigned int sleepTime, unsigned int mealsPerPhilosopher,
                         std::vector<Fork> &forks, std::atomic<bool>& stopFlag, std::mutex& printMutex)
    : id(philosopherId), doneTime(doneTime), thinkTime(thinkTime), idLeft(idLeft), idRight(idRight),
      eatTime(eatTime), sleepTime(sleepTime),
      mealsPerPhilosopher(mealsPerPhilosopher), state(THINKING), forks(forks),
      lastMealMs(nowMs()), done(false), stopFlag(stopFlag), printMutex(printMutex), timeToDie(doneTime)
{}

Philosopher::Philosopher(Philosopher&& other) noexcept
    : id(other.id), doneTime(other.doneTime), thinkTime(other.thinkTime), idLeft(other.idLeft), idRight(other.idRight),
      eatTime(other.eatTime), sleepTime(other.sleepTime), mealsPerPhilosopher(other.mealsPerPhilosopher),
      state(other.state), forks(other.forks),
      lastMealMs(other.lastMealMs.load()), done(other.done.load()),
      stopFlag(other.stopFlag), printMutex(other.printMutex), timeToDie(other.timeToDie)
{}
Philosopher::~Philosopher() {}

void Philosopher::think()
{
    state = THINKING;
    {
        std::lock_guard<std::mutex> lock(printMutex);
        std::cout << kThink << nowMs() << " " << id << " is thinking" << kReset << '\n';
    }
    sleepWithStop(thinkTime, stopFlag);
}

void Philosopher::eat()
{
    state = EATING;
    {
        std::lock_guard<std::mutex> lock(printMutex);
        std::cout << kEat << nowMs() << " " << id << " is eating" << kReset << '\n';
    }
    sleepWithStop(eatTime, stopFlag);
}

void Philosopher::sleep()
{
    state = SLEEPING;
    {
        std::lock_guard<std::mutex> lock(printMutex);
        std::cout << kSleep << nowMs() << " " << id << " is sleeping" << kReset << '\n';
    }
    sleepWithStop(sleepTime, stopFlag);
}

void Philosopher::pickUpForks()
{
    state = PICKING_UP_FORKS;
    {
        std::lock_guard<std::mutex> lock(printMutex);
        std::cout << kFork << nowMs() << " " << id << " has taken a fork" << kReset << '\n';
    }
    if (stopFlag.load())
        return;
    unsigned int first = std::min(idLeft, idRight);
    unsigned int second = std::max(idLeft, idRight);
    forks[first].pickUp();
    if (stopFlag.load()) {
        forks[first].putDown();
        return;
    }
    forks[second].pickUp();
}

void Philosopher::putDownForks()
{
    state = PUTTING_DOWN_FORKS;
    {
        std::lock_guard<std::mutex> lock(printMutex);
        std::cout << kFork << nowMs() << " " << id << " put down forks" << kReset << '\n';
    }
    forks[idLeft].putDown();
    forks[idRight].putDown();
}

void Philosopher::routine() {
    lastMealMs.store(nowMs());
    unsigned int mealsRemaining = mealsPerPhilosopher.has_value() ? mealsPerPhilosopher.value() : 0;
    while (!stopFlag.load()) {
        think();
        if (stopFlag.load())
            break;
        pickUpForks();
        if (stopFlag.load()) {
            putDownForks();
            break;
        }
        eat();
        lastMealMs.store(nowMs());
        if (stopFlag.load()) {
            putDownForks();
            break;
        }
        if (mealsRemaining > 0) {
            --mealsRemaining;
        }
        putDownForks();
        if (mealsRemaining == 0 && mealsPerPhilosopher.has_value()) {
            break;
        }
        sleep();
    }
    done.store(true);
}

long long Philosopher::getLastMealMs() const {
    return lastMealMs.load();
}

bool Philosopher::isDone() const {
    return done.load();
}

unsigned int Philosopher::getId() const {
    return id;
}
