#pragma once
#include "triangle.h"
#include <unordered_set>
#include <algorithm>

inline double det(double x1, double y1, double x2, double y2) {
    return x1 * y2 - y1 * x2;
}

template<size_t point_size>
bool for_sort(const Point<point_size>& a, const Point<point_size>& b) {
    for (size_t i = 0; i < point_size; i++) {
        if (abs(a.get_coord(i) - b.get_coord(i)) > EPS) {
            return a.get_coord(i) > b.get_coord(i);
        }
    }
    return true;
}


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
    vertexe_ = list;
    if (this->vertexe_.size() != 3) {
        throw std::logic_error("Incorrect number of points in a triangle");
    }
    std::sort(vertexe_.begin(), vertexe_.end());
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


template<size_t point_size>
std::ostream &operator<<(std::ostream &out, const Triangle<point_size> &triangle) {
    out << "Triangle(";
    for (int i = 0; i < 3; i++) {
        out << triangle.vertexe_[i];

        if (i != 2) {
            out << ", ";
        }
    }
    out << ")\n";
    return out;
}

template<size_t point_size>
bool is_triangle(const Triangle<point_size> &tr) {
    if (point_size != 2) {
        return false;
    }
    double square_triangle = tr.vertexe_[0].get_coord(0) * (tr.vertexe_[1].get_coord(1) - tr.vertexe_[2].get_coord(1)) + tr.vertexe_[1].get_coord(0) * (tr.vertexe_[2].get_coord(1) - tr.vertexe_[0].get_coord(1)) +
                             tr.vertexe_[2].get_coord(0) * (tr.vertexe_[0].get_coord(1) - tr.vertexe_[1].get_coord(1));
    return (square_triangle != 0.0);
}



template<size_t point_size>
bool point_in_triangle(const Triangle<point_size> &triangle, const Point<point_size>& point) {
    double xa = triangle.vertexe_[0].get_coord(0);
    double xb = triangle.vertexe_[1].get_coord(0);
    double xc = triangle.vertexe_[2].get_coord(0);
    double ya = triangle.vertexe_[0].get_coord(1);
    double yb = triangle.vertexe_[1].get_coord(1);
    double yc = triangle.vertexe_[2].get_coord(1);
    double x0 = point.get_coord(0);
    double y0 = point.get_coord(1);

    double res1 = det(xa - x0, ya - y0, xb - xa, yb - ya);
    double res2 = det(xb - x0, yb - y0, xc - xb, yc - yb);
    double res3 = det(xc - x0, yc - y0, xa - xc, ya - yc);
    if (res1 >= 0 && res2 >= 0 && res3 >= 0 || res1 <= 0 && res2 <= 0 && res3 <= 0) {
        return true;
    }
    return false;
}

template<size_t point_size>
std::vector<Point<point_size>> triangle_intersection(const Triangle<point_size> &triangle1, const Triangle<point_size> &triangle2) {
    Triangle<point_size> tr1 {triangle1};
    Triangle<point_size> tr2 {triangle2};
    Point<point_size> intersection_point;
    std::vector<Point<point_size>> all_points;
    if (!(is_triangle(tr1)) || !(is_triangle(tr2))) {
        std::cout << "This is not a triangle.";
        return all_points;
    }
    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++) {
            intersection_point = lines_intersection(tr1.vertexe_[i], tr1.vertexe_[(i + 1) % 3], tr2.vertexe_[j], tr2.vertexe_[(j + 1) % 3]);
            if (intersection_point.is_exist()) {
                all_points.push_back(intersection_point);
            }

        }
    }

    for (size_t i = 0; i < 3; i++) {
        if (point_in_triangle(tr1, tr2.vertexe_[i])) {
            all_points.push_back(tr2.vertexe_[i]);
        }
        if (point_in_triangle(tr2, tr1.vertexe_[i])) {
            all_points.push_back(tr1.vertexe_[i]);
        }
    }


    std::vector<Point<point_size>> out{};
    for (auto item: all_points) {
        if (std::find(out.begin(), out.end(), item) == out.end()) {
            out.push_back(item);
        }
    }
    std::sort(out.begin(), out.end());
    return out;
}