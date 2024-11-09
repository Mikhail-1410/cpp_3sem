#include <iostream>
#include <algorithm>
#include <cassert>
#include <string>

#define UNUSED(v) ((void)(v));

template<typename T, size_t ... Dims>
class Grid;

template<typename T, size_t N>
class Grid<T, N> {
private:
    T elements[N];
public:
    Grid(const T& value) {
        std::fill(elements, elements + N, value);
    }

    Grid() {
        std::fill(elements, elements + N, T());
    }

    Grid(Grid<T> const &) = delete;
    Grid(Grid<T>&&) = delete;
    Grid<T>& operator=(Grid<T>&) = delete;
    Grid<T>& operator=(Grid<T>&&) = delete;

    T operator[](size_t index) const { return elements[index]; }
    T& operator[](size_t index) { return elements[index]; }

    T operator()(size_t index) const { return elements[index]; }
    T& operator()(size_t index) { return elements[index]; }

    size_t size() const { return N; }
};

template <typename T, size_t N, size_t ... RemainingDims>
class Grid<T, N, RemainingDims...> {
private:
    Grid<T, RemainingDims...> nestedArray[N];
    size_t dimensions[sizeof...(RemainingDims) + 1];
public:
    Grid(const T& value) {
        std::fill(nestedArray, nestedArray + N, Grid<T, RemainingDims...>(value));

        dimensions[0] = N;
        size_t idx = 1;
        (..., (dimensions[idx++] = RemainingDims));
    }

    Grid() {
        std::fill(nestedArray, nestedArray + N, Grid<T, RemainingDims...>());

        dimensions[0] = N;
        size_t idx = 1;
        (..., (dimensions[idx++] = RemainingDims));
    }

    Grid<T, RemainingDims...> operator[](size_t index) const { return nestedArray[index]; }
    Grid<T, RemainingDims...>& operator[](size_t index) { return nestedArray[index]; }

    template<typename... Indices>
    auto operator()(size_t index, Indices... remainingIndices) const { return nestedArray[index](remainingIndices...); }
    template<typename... Indices>
    auto& operator()(size_t index, Indices... remainingIndices) { return nestedArray[index](remainingIndices...); }

    size_t dimensionSize(size_t index) const { return dimensions[index]; }
};

int main() {

    Grid<float, 3, 2> grid2D(0.0f);
    assert(3 == grid2D.dimensionSize(0));
    assert(2 == grid2D.dimensionSize(1));

    std::cout << "Basic indexing check: " << grid2D[1][1] << std::endl;
 
    for (size_t y = 0; y < grid2D.dimensionSize(0); ++y) {
        for (size_t x = 0; x < grid2D.dimensionSize(1); ++x) {
            assert(0.0f == grid2D[y][x]);
        }
    }

    for (size_t y = 0; y < grid2D.dimensionSize(0); ++y) {
        for (size_t x = 0; x < grid2D.dimensionSize(1); ++x) {
            grid2D[y][x] = 1.0f;
        }
    }

    for (size_t y = 0; y < grid2D.dimensionSize(0); ++y) {
        for (size_t x = 0; x < grid2D.dimensionSize(1); ++x) {
            assert(1.0f == grid2D(y, x));
        }
    }

    Grid<float, 2, 3, 4> grid3D(1.0f);
    assert(1.0f == grid3D(1, 1, 1));

    Grid<float, 3, 4> grid2D_2(2.0f);
    assert(2.0f == grid2D_2(1, 1));
    std::cout << 1 << std::endl;
    grid2D_2 = grid3D[1];
    assert(1.0f == grid2D_2(1, 1));

    Grid<float, 3, 4, 5> grid3D_full(2.0f);
}