#include "Philosopher.hh"
#include <thread>
#include <iostream>

Philosopher::Philosopher(unsigned int philosopherId, unsigned int thinkTime,
                         unsigned int idLeft, unsigned int idRight,
                         unsigned int eatTime, unsigned int sleepTime,
                         std::vector<Fork> &forks)
    : id(philosopherId), thinkTime(thinkTime), idLeft(idLeft), idRight(idRight),
      eatTime(eatTime), sleepTime(sleepTime),
      mealsPerPhilosopher(std::nullopt), state(THINKING), forks(&forks)
{
    std::cout << "Philosopher " << id << " created" << std::endl;
    std::thread t(&Philosopher::routine, this);
    t.detach();
}

Philosopher::Philosopher(unsigned int philosopherId, unsigned int thinkTime,
                         unsigned int idLeft, unsigned int idRight,
                         unsigned int eatTime, unsigned int sleepTime,
                         unsigned int mealsPerPhilosopher, std::vector<Fork> &forks)
    : id(philosopherId), thinkTime(thinkTime), idLeft(idLeft), idRight(idRight),
      eatTime(eatTime), sleepTime(sleepTime),
      mealsPerPhilosopher(mealsPerPhilosopher), state(THINKING), forks(&forks)
{
  std::thread t(&Philosopher::routine, this);
  t.detach();
}
Philosopher::~Philosopher() {}

void Philosopher::think() {}

void Philosopher::eat() {}

void Philosopher::sleep() {}

void Philosopher::pickUpForks() {}

void Philosopher::putDownForks() {}

void Philosopher::routine() {
  if (!mealsPerPhilosopher.has_value()) {
    while (true) {
      think();
      pickUpForks();
      eat();
      putDownForks();
      sleep();
    }
    state = DONE;
    return;
  }
  unsigned int mealsRemaining = mealsPerPhilosopher.value();
  while (mealsRemaining > 0) {
    think();
    pickUpForks();
    eat();
    putDownForks();
    sleep();
    mealsRemaining--;
  }
  state = DONE;
}
