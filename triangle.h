#ifndef TRIANGLE_H
#define TRIANGLE_H

#include<vector>
#include<iostream>
#include<initializer_list>
#include<cmath>
#include "point.h"

template<size_t point_size>
class Triangle;

template<size_t point_size>
std::basic_ostream<char> &operator<<(std::basic_ostream<char> &out, const Triangle<point_size> &triangle) {
    //out << "Coordinates of the triangle: \n";
    out << "Triangle(";
    for (int i = 0; i < 3; i++) {
        //out << i + 1 << " point: ";
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
    double square_triangle = tr.vertexe_[0].get_coord(0) * (tr.vertexe_[1].get_coord(1) - tr.vertexe_[2].get_coord(1)) + tr.vertexe_[1].get_coord(0) * (tr.vertexe_[2].get_coord(1) - tr.vertexe_[0].get_coord(1)) +
            tr.vertexe_[2].get_coord(0) * (tr.vertexe_[0].get_coord(1) - tr.vertexe_[1].get_coord(1));
    return (square_triangle != 0.0);
}

template<size_t point_size>
bool triangle_intersection(const Triangle<point_size> &tr1, const Triangle<point_size> &tr2) {
    Point<point_size> intersection_point;
    std::vector<Point<point_size>> all_points;
    if (!(is_triangle(tr1)) || !(is_triangle(tr2))) {
        std::cout << "This is not a triangle.";
        return false;
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            intersection_point = lines_intersection(tr1.vertexe_[i], tr1.vertexe_[(i + 1) % 3], tr2.vertexe_[j], tr2.vertexe_[(j + 1) % 3]);
            if (intersection_point.is_exist()) {
                all_points.push_back(intersection_point);
            }

        }
    }
    if (all_points.empty())
        return false;
    for (int i = 0; i < all_points.size(); i++) {
        std::cout << all_points[i];
    }
    return true;
}

//сделал в треугольнике 3 точки
template<size_t point_size>
class Triangle {
private:
    std::vector<Point<point_size>> vertexe_{};
public:
    friend bool is_triangle<point_size>(const Triangle &tr);

    friend bool triangle_intersection<point_size>(const Triangle &tr1, const Triangle &tr2);

    Triangle();

    Triangle(const Triangle<point_size> &rhs) = default;

    Triangle(Triangle<point_size> &&rhs) noexcept;

    Triangle(const std::initializer_list<Point<point_size>> &list);// здесь нужно в идеале сделать сортировку, чтобы все точки располагались по часовому круг

    Triangle<point_size> &operator=(const Triangle<point_size> &rhs) = default;

    Triangle<point_size> &operator=(Triangle<point_size> &&rhs) noexcept;

    friend std::basic_ostream<char> &operator<<<point_size>(std::basic_ostream<char> &out,const Triangle &triangle);

    Point<point_size> get_point(size_t pos) const;

    void set_point(size_t pos, const Point<point_size> &point);

    ~Triangle() = default;
};

#endif