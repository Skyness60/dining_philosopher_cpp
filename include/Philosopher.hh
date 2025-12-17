#pragma once

#include "Fork.hh"
#include <optional>
#include <vector>
#include <atomic>
#include <mutex>

typedef enum PhilosopherState {
  THINKING,
  EATING,
  SLEEPING,
  PICKING_UP_FORKS,
  PUTTING_DOWN_FORKS,
  DONE,
  ERROR
} PhilosopherState;

class Philosopher {
    private:
        unsigned int id;
        unsigned int doneTime;
        unsigned int thinkTime;
        unsigned int idLeft;
        unsigned int idRight;
        unsigned int eatTime;
        unsigned int sleepTime;
        std::optional<unsigned int> mealsPerPhilosopher;
        PhilosopherState state;
        std::vector<Fork>& forks;
        std::atomic<long long> lastMealMs;
        std::atomic<bool> done;
        std::atomic<bool>& stopFlag;
        std::mutex& printMutex;
        unsigned int timeToDie;

    public:
        Philosopher(unsigned int philosopherId, unsigned int doneTime, unsigned int thinkTime, unsigned int idLeft, unsigned int idRight,
                    unsigned int eatTime, unsigned int sleepTime, std::vector<Fork>& forks, std::atomic<bool>& stopFlag, std::mutex& printMutex);
        Philosopher(unsigned int philosopherId, unsigned int doneTime, unsigned int thinkTime, unsigned int idLeft, unsigned int idRight,
                    unsigned int eatTime, unsigned int sleepTime,
                    unsigned int mealsPerPhilosopher, std::vector<Fork>& forks, std::atomic<bool>& stopFlag, std::mutex& printMutex);
        Philosopher(const Philosopher&) = delete;
        Philosopher& operator=(const Philosopher&) = delete;
        Philosopher(Philosopher&& other) noexcept;
        Philosopher& operator=(Philosopher&& other) noexcept = delete;
        ~Philosopher();
        void think();
        void eat();
        void sleep();
        void pickUpForks();
        void putDownForks();
        void routine();
        long long getLastMealMs() const;
        bool isDone() const;
        unsigned int getId() const;
};
