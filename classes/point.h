#pragma once

#include "iostream"
#include "initializer_list"
#include "vector"
#include "cmath"

static const double EPS = 1e-9;




template<size_t point_dim>
class Point {
private:
    size_t dim = point_dim;
    std::vector<double> coords{};
    bool exist = false;

public:

    Point();

    Point(const std::initializer_list<double> &coords);

    Point(const Point<point_dim> &other) = default;

    Point(Point<point_dim> &&other) noexcept;

    Point<point_dim> &operator=(const Point<point_dim> &other) = default;

    Point<point_dim> &operator=(Point<point_dim> &&other) noexcept;

    bool operator==(const Point<point_dim> &other) const;

    bool operator>(const Point<point_dim> &other) const;

    bool operator<(const Point<point_dim> &other) const;

    template<size_t point_dim1>
    friend std::ostream &operator<<(std::ostream &out,const Point<point_dim1> &);

    template<size_t point_dim1>
    friend std::istream &operator>>(std::istream &in, Point<point_dim1> &);

    double get_coord(size_t coord) const;

    size_t get_dim() const;

    bool is_exist() const;

    void set_coord(size_t coord, double value);

    ~Point() = default;
};



#include "point.tpp"
