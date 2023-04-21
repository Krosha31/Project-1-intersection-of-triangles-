#pragma once

#include<vector>
#include<iostream>
#include<initializer_list>
#include<cmath>
#include<set>

const double EPS = 1e-9;

template <size_t point_size>
class Point {
    const size_t size_ = point_size;
public:
    double x_;
    double y_;
    double z_;
    bool exist_;
    Point() : x_(0), y_(0), z_(0), exist_(0) {}
    Point(double x, double y, double z=0, bool exist=1) : x_(x), y_(y), z_(z), exist_(exist) {}
    Point<point_size>& operator=(const Point<point_size>& other);
    template<size_t point_size2>
    friend std::ostream& operator<<(std::ostream& out, const Point<point_size2>& point);
};



template<size_t point_size>
class Triangle {
public:
    size_t size_ = 0;
    std::vector <Point<point_size>> vertexe_;
    Triangle() = default;
    Triangle(const std::initializer_list<Point<point_size>> list) {// здесь нужно в идеале сделать сортировку, чтобы все точки располагались по часовому кругу
        for (auto element: list) {
            vertexe_.push_back(element);
            size_++;
        }
    }
    template<size_t point_size2>
    friend std::ostream& operator<<(std::ostream& out, const Triangle<point_size2>& triangle);
};

template<size_t point_size>
bool is_triangle(const Triangle<point_size>& tr);

template<size_t point_size>
Point<point_size> lines_intersection(Point<point_size> p1, Point<point_size> p2, Point<point_size> p3, Point<point_size> p4);

template<size_t point_size>
bool triangle_intersection(const Triangle<point_size>& tr1, const Triangle<point_size>& tr2);