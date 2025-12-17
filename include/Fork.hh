#pragma once

#include <mutex>

class Fork
{
    private:
        std::mutex mutex;

    public:
        Fork() = default;
        Fork(const Fork &) = delete;
        Fork &operator=(const Fork &) = delete;
        Fork(Fork &&) noexcept;
        Fork &operator=(Fork &&) noexcept;
        ~Fork();
        void pickUp();
        void putDown();
};
