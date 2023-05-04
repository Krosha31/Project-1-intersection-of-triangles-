#pragma once

#include<vector>
#include<iostream>
#include<initializer_list>
#include<cmath>
#include<set>

constexpr double EPS = 1e-9;

template <size_t point_size>
class Point {
    const size_t size_ = point_size;
    std::vector<double> coords{};
    bool exist_ = false;
public:
    Point();
    Point(const std::initializer_list<double>& coords);
    Point(const Point<point_size>& other) = default;
    Point(Point<point_size> && other) noexcept;

    Point<point_size> &operator=(const Point<point_size> &other) = default;
    Point<point_size> &operator=(Point<point_size> &&other) noexept;

    double get_coord(size_t coord) const;


    template<size_t point_size2>
    friend std::ostream &operator<<(std::ostream& out, const Point<point_size2>& point);
    ~Point() = default;
};



template<size_t point_size>
class Triangle {
    std::vector <Point<point_size>> vertexe_{};
public:
    Triangle();
    Triangle(const Triangle<point_size>& other) = default;
    Triangle(Triangle<point_size> && rhs) noexcept;
    Triangle(const std::initializer_list<Point<point_size>> &list); 
    
    Triangle<point_size> &operator=(const Triangle<point_size>& other) = default;
    Triangle<point_size> &operator=(Triangle<point_size> &&other) noexcept;

    template<size_t point_size2>
    friend std::ostream& operator<<(std::ostream& out, const Triangle<point_size2>& triangle);
    ~Triangle() = default;
};

template<size_t point_size>
bool is_triangle(const Triangle<point_size>& tr);

template<size_t point_size>
Point<point_size> lines_intersection(Point<point_size> &p1, Point<point_size> &p2, Point<point_size> &p3, Point<point_size> &p4);

template<size_t point_size>
bool triangle_intersection(const Triangle<point_size>& tr1, const Triangle<point_size>& tr2);
