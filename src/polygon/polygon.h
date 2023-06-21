#pragma once

#include<vector>
#include<iostream>
#include<initializer_list>
#include<cmath>
#include "point.h"

template<size_t point_size>
class Polygon {
private:
    std::vector<Point<point_size>> vertexe_{};
public:
    Polygon() = default;

    Polygon(const std::initializer_list<Point<point_size>> &list);

    Polygon(const std::vector<Point<2>>& points);

    Polygon(const Polygon<point_size> &rhs) = default;

    Polygon(Polygon<point_size>&& rhs) noexcept;

    Polygon<point_size> &operator=(const Polygon<point_size> &rhs) = default;

    Polygon<point_size> &operator=(Polygon<point_size> &&rhs) noexcept;

    size_t size() const;

    template<size_t point_size1>
    friend std::ostream &operator<<(std::ostream &out,const Polygon<point_size1> &polygon);

    void set_point(size_t pos, const Point<point_size>& point);

    Point<point_size> get_point(size_t pos) const;

    template<size_t point_size1>
    friend bool is_polygon(const Polygon<point_size1>& pl);

    template<size_t point_size1>
    friend bool is_convex_polygon(const Polygon<point_size1> &pol);

    template<size_t point_size1>
    friend bool point_in_polygon(const Polygon<point_size1> &polygon, const Point<point_size1>& point);

    template<size_t point_size1>
    friend std::vector <Point<point_size1>>  polygon_intersection(const Polygon<point_size1>&, const Polygon<point_size1>&);

    ~Polygon() = default;
};

#include "polygon.tpp"
