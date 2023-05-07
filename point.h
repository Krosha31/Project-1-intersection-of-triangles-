#ifndef POINT_H
#define POINT_H

#include "iostream"
#include "initializer_list"
#include "vector"
#include "cmath"

const double EPS = 1e-9;

template<size_t point_dim>
class Point;

template<size_t point_dim>
std::basic_ostream<char> &operator<<(std::basic_ostream<char> &out, const Point<point_dim> &point) {
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

    friend std::basic_ostream<char> &operator<<<point_dim>(std::basic_ostream<char> &out,const Point &);

    double get_coord(size_t coord) const;

    size_t get_dim() const;

    bool is_exist() const;

    void set_coord(size_t coord, double value);

    ~Point() = default;
};


//чекните, что нигде не напутал x и y в точках
//мб сделать функцию для n-мерной точки)
template<size_t point_size>
Point<point_size> lines_intersection(const Point<point_size> &p1_, const Point<point_size> &p2_, const Point<point_size> &p3_, const Point<point_size> &p4_) {
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
        std::cout << 1;
        return Point<point_size>();
    }

    double k1, k2;
    if (p1.get_coord(0) == p2.get_coord(0)) {
        double x = p1.get_coord(0);
        k2 = (p3.get_coord(1) - p4.get_coord(1)) / (p3.get_coord(0) - p4.get_coord(0));
        double b2 = p3.get_coord(1) - k2 * p3.get_coord(0);
        double y = k2 * x + b2;

        if (p3.get_coord(0) <= x && p4.get_coord(0) >= x &&
                std::min(p1.get_coord(1),p2.get_coord(1)) <= y && std::max(p1.get_coord(1), p2.get_coord(1)) >= y) {
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
                std::min(p3.get_coord(1),p4.get_coord(1)) <= y && std::max(p3.get_coord(1), p4.get_coord(1)) >= y) {
            Point<point_size> intersection_point = {x, y};
            return intersection_point;
        }
        return Point<point_size>();
    } else {
        k2 = (p4.get_coord(1) - p3.get_coord(1)) / (p4.get_coord(0) - p3.get_coord(0));
    }

    if (fabs(k1 - k2) < EPS) {
        std::cout << k1 << " " << k2 << std::endl;

        return Point<point_size>();
    }

    double b1 = p1.get_coord(1) - k1 * p1.get_coord(0);
    double b2 = p3.get_coord(1) - k2 * p3.get_coord(0);
    double x = (b2 - b1) / (k1 - k2);
    double y = k1 * x + b1;

    if ((x < std::max(p1.get_coord(0), p3.get_coord(0))) || (x > std::min(p2.get_coord(0), p4.get_coord(0)))) {
        std::cout << x;
        return Point<point_size>(); //точка X находится вне пересечения проекций отрезков на ось X
    }
    Point<point_size> intersection_point = {x, y};
    return intersection_point;
}

#endif
