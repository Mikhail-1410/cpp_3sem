template<typename T>
class Grid final {
public: 
    using value_type = T;
    using size_type = unsigned;
private:
    T * const data;
    size_type const rows, cols;

    Grid(T *data, size_type rows, size_type cols)
        : data(data), rows(rows), cols(cols) { }

    Grid(Grid<T> const &) = delete;
    Grid(Grid<T>&&) = delete;
    Grid<T>& operator=(Grid<T>&) = delete;
    Grid<T>& operator=(Grid<T>&&) = delete;

    T operator()(size_type rowIndex, size_type colIndex) const {
        return data[rowIndex * cols + colIndex];
    }

    T& operator()(size_type rowIndex, size_type colIndex) {
        return data[rowIndex * cols + colIndex];
    }

    Grid<T>& operator=(T const &value) {
        for (auto it = data, end = data + cols * rows; it != end; ++it) {
            *it = value;
        }
        return *this;
    }
    
    size_type rowSize() const { return rows; }
    size_type colSize() const { return cols; }
};