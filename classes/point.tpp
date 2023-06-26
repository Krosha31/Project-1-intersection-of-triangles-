#pragma once

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

template<size_t point_dim>
bool Point<point_dim>::operator==(const Point<point_dim> &other) const {
    for (size_t i = 0; i < point_dim; i++) {
        if (abs(coords[i] - other.coords[i]) > EPS) {
            return false;
        }
    }
    return true;
}

template<size_t point_dim>
bool Point<point_dim>::operator>(const Point<point_dim> &other) const {
    for (size_t i = 0; i < coords.size(); i++) {
        if (abs(coords[i] - other.coords[i]) > EPS) {
            return coords[i] > other.coords[i];
        }
    }
}

template<size_t point_dim>
bool Point<point_dim>::operator<(const Point<point_dim> &other) const {
    for (size_t i = 0; i < coords.size(); i++) {
        if (abs(coords[i] - other.coords[i]) > EPS) {
            return coords[i] < other.coords[i];
        }
    }
    return false;
}

template<size_t point_dim>
std::istream &operator>>(std::istream &in, Point<point_dim> &point) {
    for (size_t i = 0; i < point_dim; i++) {
        in >> point.coords[i];
    }
    point.exist = true;
    return in;
}


template<size_t point_dim>
std::ostream &operator<<(std::basic_ostream<char> &out, const Point<point_dim> &point) {
    if (!point.exist) {
        out << "()";
        return out;
    }

    out << '(';
    for (size_t i = 0; i < point.dim; ++i) {
        if (i < point_dim - 1) {
            out << point.coords[i] << ", ";
        } else {
            out << point.coords[i] << ')';
        }
    }
    return out;
}


template<size_t point_size>
Point<point_size>
lines_intersection(const Point<point_size> &p1_, const Point<point_size> &p2_, const Point<point_size> &p3_,
                   const Point<point_size> &p4_) {
    Point<point_size> p1 = p1_, p2 = p2_, p3 = p3_, p4 = p4_;
    if (p1.get_coord(0) > p2.get_coord(0)) {
        std::swap(p1, p2);
    }
    if (p3.get_coord(0) > p4.get_coord(0)) {
        std::swap(p3, p4);
    }
    if ((p1.get_coord(0) == p2.get_coord(0)) && (p3.get_coord(0) == p4.get_coord(0))) {
        //если они лежат на одном X
        if (p1.get_coord(0) == p3.get_coord(0)) {
            //проверим не пересекаются ли они, т.е. есть ли у них общий Y
            if (!((std::max(p1.get_coord(1), p2.get_coord(1)) < std::min(p3.get_coord(1), p4.get_coord(1))) ||
                  (std::min(p1.get_coord(1), p2.get_coord(1)) > std::max(p3.get_coord(1), p4.get_coord(1))))) {
                Point<point_size> intersection = {p1.get_coord(0), p3.get_coord(1)};
                return intersection;// додумать
            }
        }
        //std::cout << 1;
        return Point<point_size>();
    }

    double k1, k2;
    if (p1.get_coord(0) == p2.get_coord(0)) {
        double x = p1.get_coord(0);
        k2 = (p3.get_coord(1) - p4.get_coord(1)) / (p3.get_coord(0) - p4.get_coord(0));
        double b2 = p3.get_coord(1) - k2 * p3.get_coord(0);
        double y = k2 * x + b2;

        if (p3.get_coord(0) <= x && p4.get_coord(0) >= x &&
            std::min(p1.get_coord(1), p2.get_coord(1)) <= y && std::max(p1.get_coord(1), p2.get_coord(1)) >= y) {
            Point<point_size> intersection_point = {x, y};
            return intersection_point;
        }
        return Point<point_size>();
    } else {
        k1 = (p2.get_coord(1) - p1.get_coord(1)) / (p2.get_coord(0) - p1.get_coord(0));
    }

    if (p3.get_coord(0) == p4.get_coord(0)) {
        double x = p3.get_coord(0);
        k1 = (p1.get_coord(1) - p2.get_coord(1)) / (p1.get_coord(0) - p2.get_coord(0));
        double b1 = p1.get_coord(1) - k1 * p1.get_coord(0);
        double y = k1 * x + b1;

        if (p1.get_coord(0) <= x && p2.get_coord(0) >= x &&
            std::min(p3.get_coord(1), p4.get_coord(1)) <= y && std::max(p3.get_coord(1), p4.get_coord(1)) >= y) {
            Point<point_size> intersection_point = {x, y};
            return intersection_point;
        }
        return Point<point_size>();
    } else {
        k2 = (p4.get_coord(1) - p3.get_coord(1)) / (p4.get_coord(0) - p3.get_coord(0));
    }

    double b1 = p1.get_coord(1) - k1 * p1.get_coord(0);
    double b2 = p3.get_coord(1) - k2 * p3.get_coord(0);

    if (fabs(k1 - k2) < EPS) {

        return Point<point_size>();
    }


    double x = (b2 - b1) / (k1 - k2);
    double y = k1 * x + b1;

    if ((x < std::max(p1.get_coord(0), p3.get_coord(0))) || (x > std::min(p2.get_coord(0), p4.get_coord(0)))) {
        return Point<point_size>(); //точка X находится вне пересечения проекций отрезков на ось X
    }
    Point<point_size> intersection_point = {x, y};
    return intersection_point;
}
