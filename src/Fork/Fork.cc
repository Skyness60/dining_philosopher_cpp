#include "Fork.hh"

Fork::Fork(Fork &&) noexcept : mutex() {}

Fork &Fork::operator=(Fork &&) noexcept {
    return *this;
}

Fork::~Fork() {}

void Fork::pickUp() {
    mutex.lock();
}

void Fork::putDown() {
    mutex.unlock();
}
