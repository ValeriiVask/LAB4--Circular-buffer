#pragma once
#include <array>

template <typename T, size_t maxSize>
class CircularBuffer {
private:
    std::array<T, maxSize> buffer;
    size_t firstToRead = 0;
    size_t firstFree = 0;
    size_t count = 0;

public:
    CircularBuffer() noexcept = default;

    size_t size() const noexcept {
        return count;
    }

    bool push(const T& value) noexcept {
        if (count < maxSize) {
            buffer[firstFree] = value;
            firstFree = (firstFree + 1) % maxSize;
            count++;
            return true;
        }
        return false;
    }

    bool pop(T& value) noexcept {
        if (count > 0) {
            value = buffer[firstToRead];
            firstToRead = (firstToRead + 1) % maxSize;
            count--;
            return true;
        }
        return false;
    }

    bool isEmpty() const noexcept {
        return count == 0;
    }

    bool isFull() const noexcept {
        return count == maxSize;
    }
};
