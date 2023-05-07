#include "triangle.h"

template<size_t point_size>
Triangle<point_size>::Triangle() {
    this->vertexe_.resize(3);
}

template<size_t point_size>
void Triangle<point_size>::set_point(size_t pos, const Point<point_size> &point) {
    if (pos >= 3) {
        throw std::logic_error("Point does not exist");
    }
    this->vertexe_[pos] = point;
}

template<size_t point_size>
Point<point_size> Triangle<point_size>::get_point(size_t pos) const {
    if (pos >= 3) {
        throw std::logic_error("Point does not exist");
    }
    return this->vertexe_[pos];
}

template<size_t point_size>
Triangle<point_size>::Triangle(const std::initializer_list<Point<point_size>> &list) {
    this->vertexe_ = list;
    if (this->vertexe_.size() != 3) {
        throw std::logic_error("Incorrect number of points in a triangle");
    }
}

template<size_t point_size>
Triangle<point_size> &Triangle<point_size>::operator=(Triangle<point_size> &&rhs) noexcept {
    if (this == &rhs) {
        return *this;
    }
    this->vertexe_ = std::move(rhs.vertexe_);
    return *this;
}

template<size_t point_size>
Triangle<point_size>::Triangle(Triangle<point_size> &&rhs) noexcept {
    this->vertexe_ = std::move(rhs.vertexe_);
}