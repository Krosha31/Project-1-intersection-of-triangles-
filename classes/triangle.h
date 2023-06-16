#ifndef TRIANGLE_H
#define TRIANGLE_H

#include<vector>
#include<iostream>
#include<initializer_list>
#include<cmath>
#include "point.h"




template<size_t point_size>
class Triangle {
private:
    std::vector<Point<point_size>> vertexe_{};
public:

    template<size_t point_size1>
    friend bool is_triangle(const Triangle<point_size1> &tr);

    template<size_t point_size1>
    friend std::vector<Point<point_size1>> triangle_intersection(const Triangle<point_size1> &tr1, const Triangle<point_size1> &tr2);

    template<size_t point_size1>
    friend bool point_in_triangle(const Triangle<point_size1> &triangle, const Point<point_size1>& point);

    Triangle();

    Triangle(const Triangle<point_size> &rhs) = default;

    Triangle(Triangle<point_size> &&rhs) noexcept;

    Triangle(const std::initializer_list<Point<point_size>> &list);// здесь нужно в идеале сделать сортировку, чтобы все точки располагались по часовому круг

    Triangle<point_size> &operator=(const Triangle<point_size> &rhs) = default;

    Triangle<point_size> &operator=(Triangle<point_size> &&rhs) noexcept;

    template<size_t point_size1>
    friend std::ostream &operator<<(std::ostream &out,const Triangle<point_size1> &triangle);

    Point<point_size> get_point(size_t pos) const;

    void set_point(size_t pos, const Point<point_size> &point);

    ~Triangle() = default;
};

#include "triangle.tpp"

#endif