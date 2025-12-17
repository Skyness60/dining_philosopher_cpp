#pragma once

#include "Fork.hh"
#include <optional>
#include <vector>

typedef enum PhilosopherState {
  THINKING,
  EATING,
  SLEEPING,
  DONE,
  ERROR
} PhilosopherState;

class Philosopher {
    private:
        unsigned int id;
        unsigned int thinkTime;
        unsigned int idLeft;
        unsigned int idRight;
        unsigned int eatTime;
        unsigned int sleepTime;
        std::optional<unsigned int> mealsPerPhilosopher;
        PhilosopherState state;
        std::vector<Fork>* forks;

    public:
        Philosopher(unsigned int philosopherId, unsigned int thinkTime, unsigned int idLeft, unsigned int idRight,
                    unsigned int eatTime, unsigned int sleepTime, std::vector<Fork>& forks);
        Philosopher(unsigned int philosopherId, unsigned int thinkTime, unsigned int idLeft, unsigned int idRight,
                    unsigned int eatTime, unsigned int sleepTime,
                    unsigned int mealsPerPhilosopher, std::vector<Fork>& forks);
        ~Philosopher();
        void think();
        void eat();
        void sleep();
        void pickUpForks();
        void putDownForks();
        void routine();
};
