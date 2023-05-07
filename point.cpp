#include "point.h"

template<size_t point_dim>
bool Point<point_dim>::is_exist() const {
    return this->exist;
}

template<size_t point_dim>
Point<point_dim>::Point() {
    if (point_dim != 0) {
        this->coords.resize(point_dim);
        this->exist = false;
    }
}

template<size_t point_dim>
size_t Point<point_dim>::get_dim() const {
    return this->dim;
}

template<size_t point_dim>
void Point<point_dim>::set_coord(size_t coord, const double value) {
    if (coord >= this->coords.size()) {
        throw std::logic_error("Coordinate does not exist");
    }
    this->coords[coord] = value;
}

template<size_t point_dim>
double Point<point_dim>::get_coord(size_t coord) const {
    if (coord >= this->coords.size()) {
        throw std::logic_error("Coordinate does not exist");
    }
    return this->coords[coord];
}

template<size_t point_dim>
Point<point_dim>::Point(const std::initializer_list<double> &coords) {
    if (coords.size() != point_dim) {
        throw std::length_error("Incorrect number of coordinates");
    }
    if (point_dim == 0) {
        exist = false;
        return;
    }

    this->exist = true;

    for (const auto &i: coords) {
        this->coords.push_back(i);
    }
}

template<size_t point_dim>
Point<point_dim>::Point(Point<point_dim> &&other) noexcept {
    this->coords = std::move(other.coords);
    this->exist = other.exist;
    this->dim = other.dim;
}

template<size_t point_dim>
Point<point_dim> &Point<point_dim>::operator=(Point<point_dim> &&other) noexcept {
    if (this == &other) {
        return *this;
    }
    this->coords = std::move(other.coords);
    this->exist = other.exist;
    this->dim = other.dim;
    return *this;
}