#include <cstddef>
#include <stdexcept>
#include <iostream>

template <typename T, unsigned N>
class Array {
public:
    explicit Array(const T& value = T()) {
        fill(value);
    }

    Array(const Array& other) {
        for (size_t i = 0; i < N; ++i) {
            data[i] = other.data[i];
        }
    }

    Array& operator=(const Array& other) {
        if (this != &other) {
            for (size_t i = 0; i < N; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    ~Array() = default;

    size_t size() const {
        return N;
    }

    const T& operator[](size_t index) const {
        if (index >= N) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    T& operator[](size_t index) {
        if (index >= N) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    T& front() {
        return data[0];
    }

    const T& front() const {
        return data[0];
    }

    T& back() {
        return data[N - 1];
    }

    const T& back() const {
        return data[N - 1];
    }

    bool empty() const {
        return N == 0;
    }

    void fill(const T& value) {
        for (size_t i = 0; i < N; ++i) {
            data[i] = value;
        }
    }

private:
    T data[N];
};

template <int Base, int Exponent>
struct Power {
    static constexpr int value = (Exponent % 2 == 0) 
        ? Power<Base, Exponent / 2>::value * Power<Base, Exponent / 2>::value
        : Base * Power<Base, Exponent - 1>::value;
};

template <int Base>
struct Power<Base, 0> {
    static constexpr int value = 1;
};

template <int Base>
struct Power<Base, 1> {
    static constexpr int value = Base;
};

int main() {
    constexpr int result1 = Power<2, 10>::value;
    constexpr int result2 = Power<5, 3>::value;
    constexpr int result3 = Power<7, 0>::value;

    Array<int, 5> arr(3);
    arr.fill(10);
    int first = arr.front();
    int last = arr.back();

    std::cout << result1 << " " << result2 << " " << result3 << " ";
}