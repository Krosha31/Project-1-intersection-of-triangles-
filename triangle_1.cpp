#include "triangle.h"


template<size_t point_size>
Point<point_size>::Point() {
    if (point_size != 0) {
        this->coords.resize(point_size);
        this->exist = true;
    }
}

template<size_t point_size>
Point<point_size>::Point(const std::initializer_list<double> &coords) {
    if (coords.size() != point_size) {
        throw std::length_error("Incorrect number of coordinates");
    }
    if (point_size == 0) {
        exist = false;
        return;
    }

    this->exist = true;

    for (const auto& i : coords) {
        this->coords.push_back(i);
    }
}

template<size_t point_size>
Point<point_size>::Point(Point<point_size> &&other) noexcept {
    this->coords = std::move(other.coords);
    this->exist_ = other.exist_;
    this->size_ = other.size_;
}



template<size_t point_size>
Point<point_size> &Point<point_size>::operator=(Point<point_size> &&other) noexcept{
    if (this == &other) {
        return *this;
    }
    this->exist_ = other.exist_;
    this->coords = std::move(other.coords);
    this->size_ = other.size_;
    return *this;
}

template<size_t point_size2>
std::ostream& operator<<(std::ostream& out, const Point<point_size2>& point) {
    if (!point.exist) {
        out << "()";
        return out;
    }

    out << '(';
    for (size_t i = 0; i < point.size_; ++i) {
        if (i < point_size - 1) {
            out << point.coords[i] << ", ";
        }
        else {
            out << point.coords[i] << ')';
        }
    }
    return out;
}

template<size_t point_size>
double Point<point_size>::get_coord(size_t coord) const {
    if (coord >= this->coords.size()) {
        throw std::logic_error("Coordinate does not exist");
    }
    return this->coords[coord];
}






template<size_t point_size>
Triangle<point_size>::Triangle() {
    this->vertexe_.resize(3);
}

template<size_t point_size>
Triangle<point_size>::Triangle(const std::initializer_list<Point<point_size>>& list) {
    this->vertexe_ = list;
    if (this->vertexe_.size() != 3) {
        throw std::logic_error("Incorrect number of points in a triangle");
    }
}

template<size_t point_size>
Triangle<point_size>::Triangle(Triangle<point_size> &&other) noexcept {
    this->vertexe_ = std::move(other.vertexe_);
}

template<size_t point_size>
std::ostream& operator<<(std::ostream& out, const Triangle<point_size>& triangle)
{
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
bool is_triangle(const Triangle<point_size>& tr) {
    double square_triangle = fabs(((tr.vertexe_[1].get_coord(0) - tr.vertexe_[0].get_coord(0)) * (tr.vertexe_[2].get_coord(1) - tr.vertexe_[0].get_coord(1)) - (tr.vertexe_[2].get_coord(0) - tr.vertexe_[0].get_coord(0)) * (tr.vertexe_[1].get_coord(1) - tr.vertexe_[0].get_coord(1))) / 2);
    return  (square_triangle != 0.0);
}

template<size_t point_size>
Point<point_size> lines_intersection(Point<point_size> &p1, Point<point_size> &p2, Point<point_size> &p3, Point<point_size> &p4) {
    if (p1.get_coord(0) >= p2.get_coord(0)) {
        std::swap(p1, p2);
    }
    if (p3.get_coord(0) >= p4.xget_coord(0)) {
        std::swap(p3, p4);
    }
    if ((p1.get_coord(0) == p2.get_coord(0)) && (p3.get_coord(0) == p4.get_coord(0))) {
        //если они лежат на одном X
        if (p1.get_coord(0) == p3.get_coord(0)) {
            //проверим не пересекаются ли они, т.е. есть ли у них общий Y
            if (!((std::max(p1.get_coord(1), p2.get_coord(1)) < std::min(p3.get_coord(1), p4.get_coord(1))) || (std::min(p1.get_coord(1), p2.get_coord(1)) > std::max(p3.get_coord(1), p4.get_coord(1))))) {
                return Point<point_size>(p1.get_coord(1), p3.get_coord(1));// додумать
            }
        }
       
        return Point<point_size>();
    }

    double k1, k2;
    if (p1.get_coord(0) == p2.get_coord(0)) {
        k1 = 0;
    }
    else {
        k1 = (p2.get_coord(1) - p1.get_coord(1)) / (p2.get_coord(0) - p1.get_coord(0));
    }

    if (p3.get_coord(0) == p4.get_coord(0)) {
        k2 = 0;
    }
    else {
        k2 = (p4.get_coord(1) - p3.get_coord(1)) / (p4.get_coord(0) - p3.get_coord(0));
    }

    if (fabs(k1 - k2) < EPS) {
        return Point<point_size>();
    }

    double b1 = p1.get_coord(1) - k1 * p1.get_coord(0);
    double b2 = p3.get_coord(1)_ - k2 * p3.get_coord(0);
    double x = (b2 - b1) / (k1 - k2);
    double y = k1 * x + b1;

    if ((x < std::max(p1.get_coord(0), p3.get_coord(0))) || (x > std::min(p2.get_coord(0), p4.get_coord(0)))) {
        return Point<point_size>(); //точка X находится вне пересечения проекций отрезков на ось X
    }
    Point<point_size> intersection_point(x, y);
    return intersection_point;
}

template<size_t point_size>
bool triangle_intersection(const Triangle<point_size>& tr1, const Triangle<point_size>& tr2) {
    Point<point_size> intersection_point;
    std::vector<Point<point_size>> all_points;
    if (!(is_triangle(tr1)) || !(is_triangle(tr2)))
    {
        std::cout << "This is not a triangle.";
        return false;
    }
    for (int i = 0; i < tr1.size_; i++) {
        for (int j = 0; j < tr2.size_; j++)
        {
            intersection_point = lines_intersection(tr1.vertexe_[i], tr1.vertexe_[(i + 1) % 3], tr2.vertexe_[j], tr2.vertexe_[(j + 1) % 3]);
            if (intersection_point.exist_)
            {
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