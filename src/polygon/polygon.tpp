#pragma once
#include "polygon.h"
#include <algorithm>
#include <set>

template<size_t point_size>
Polygon<point_size>::Polygon(const std::initializer_list<Point<point_size>> &list) {
    vertexe_ = list;
    if (this->vertexe_.size() <= 2) {
        throw std::logic_error("Incorrect number of points in a polygon");
    }

}

template<size_t point_size>
Polygon<point_size>::Polygon(Polygon<point_size> &&rhs) noexcept {
    this->vertexe_ = std::move(rhs.vertexe_);
}

template<size_t point_size>
Polygon<point_size> &Polygon<point_size>::operator=(Polygon<point_size> &&rhs) noexcept {
    if (this == &rhs) {
        return *this;
    }
    this->vertexe_ = std::move(rhs.vertexe_);
    return *this;
}

template<size_t point_size>
std::ostream &operator<<(std::ostream &out, const Polygon<point_size> &polygon) {
    out << "Polygon(";
    for (int i = 0; i < polygon.vertexe_.size(); i++) {
        out << polygon.vertexe_[i];

        if (i != polygon.vertexe_.size() - 1) {
            out << ", ";
        }
    }
    out << ")\n";
    return out;
}

template <size_t point_size>
size_t Polygon<point_size>::size() const {
    return vertexe_.size();
}

template<size_t point_size>
void Polygon<point_size>::set_point(size_t pos, const Point<point_size> &point) {
    if (pos >= this->vertexe_.size()) {
        throw std::logic_error("Point does not exist");
    }
    this->vertexe_[pos] = point;
}

template<size_t point_size>
Point<point_size> Polygon<point_size>::get_point(size_t pos) const {
    if (pos >= this->vertexe_.size()) {
        throw std::logic_error("Point does not exist");
    }
    return this->vertexe_[pos];
}

template<size_t point_size>
bool is_convex_polygon(const Polygon<point_size> &pl) {
    if (point_size != 2) {
        return false;
    }
    Point<point_size> ab;
    Point<point_size> bc;
    size_t size = pl.vertexe_.size();
    // при его обходе в каждой тройке последовательных вершин происходит поворот всегда в одну и ту же сторону
    // При обходе многоугольника по часовой стрелке поворот будет всегда направо
    for (int i = 0; i < pl.vertexe_.size(); i++){
        // считаем координаты двух векторов
        if (i != 0 and i != size - 1){
            ab = {pl.vertexe_[i].get_coord(0) - pl.vertexe_[i - 1].get_coord(0), pl.vertexe_[i].get_coord(1) - pl.vertexe_[i - 1].get_coord(1)};
            bc = {pl.vertexe_[i + 1].get_coord(0) - pl.vertexe_[i].get_coord(0), pl.vertexe_[i + 1].get_coord(1) - pl.vertexe_[i].get_coord(1)};
        }
        else if (i == 0){
            ab = {pl.vertexe_[i].get_coord(0) - pl.vertexe_[size - 1].get_coord(0), pl.vertexe_[i].get_coord(1) - pl.vertexe_[size - 1].get_coord(1)};
            bc = {pl.vertexe_[i + 1].get_coord(0) - pl.vertexe_[i].get_coord(0), pl.vertexe_[i + 1].get_coord(1) - pl.vertexe_[i].get_coord(1)};
        }
        else if (i == pl.vertexe_.size() - 1){
            ab = {pl.vertexe_[i].get_coord(0) - pl.vertexe_[i - 1].get_coord(0), pl.vertexe_[i].get_coord(1) - pl.vertexe_[i - 1].get_coord(1)};
            bc = {pl.vertexe_[0].get_coord(0) - pl.vertexe_[i].get_coord(0), pl.vertexe_[0].get_coord(1) - pl.vertexe_[i].get_coord(1)};
        }
        // направление поворота в этой паре последовательных ребер будет задаваться знаком выражения:
        // в нашем случае отрицательное значение означает выпуклость фигуры
        if (ab.get_coord(0) * bc.get_coord(1) - ab.get_coord(1) * bc.get_coord(0) > 0)
            return false;
    }
    return true;
}

template<size_t point_size>
bool is_polygon(const Polygon<point_size> &pl) {
    size_t size = pl.vertexe_.size();
    double square_polygon = 0;
    //вычисляем по формуле Гаусса площадь многоугольника
    for(int i=0; i < size - 1; ++i){
        square_polygon += pl.vertexe_[i].get_coord(0) * pl.vertexe_[i + 1].get_coord(1);
        square_polygon -= pl.vertexe_[i + 1].get_coord(0) * pl.vertexe_[i].get_coord(1);
    }
    square_polygon += pl.vertexe_[size - 1].get_coord(0) * pl.vertexe_[0].get_coord(1);
    square_polygon -= pl.vertexe_[0].get_coord(0) * pl.vertexe_[size - 1].get_coord(1);
    if (fabs(square_polygon) > EPS && is_convex_polygon(pl)) {
        return true;
    }
    return false;
}


template<size_t point_size>
bool point_in_polygon(const Polygon<point_size> &polygon, const Point<point_size>& point) {
    if (!is_polygon(polygon)) {
        std::cout << "it isn't a polygon.\n";
        return false;
    }
    if (!point.is_exist()) {
        std::cout << "This point doesn't exist\n";
        return false;
    }
    Point<point_size> max_point = polygon.vertexe_[0];
    for (size_t i = 0; i < polygon.size(); i++) {
        max_point.set_coord(0, std::max(max_point.get_coord(0), polygon.get_point(i).get_coord(0)));
        max_point.set_coord(1, std::max(max_point.get_coord(1), polygon.get_point(i).get_coord(1)));
    }

    max_point.set_coord(0, max_point.get_coord(0) + 100);
    max_point.set_coord(1, max_point.get_coord(1) + 100);
    std::set<Point<2>> points_of_intersection;
    for (size_t i = 0; i < polygon.size(); i++) {
        Point<2> intersection_point = lines_intersection(polygon.vertexe_[i], polygon.vertexe_[(i + 1) % polygon.size()],point, max_point);
        if (intersection_point.is_exist()) {
            points_of_intersection.insert(intersection_point);
        }
    }
    if (points_of_intersection.size() % 2 == 1) {
        return true;
    }
    return false;
}


template <size_t point_size>
std::vector<Point<point_size>> polygon_intersection(const Polygon<point_size>& polygon1, const Polygon<point_size>& polygon2) {
    if (!is_polygon(polygon1)) {
        std::cout << "The first argument isn't a polygon.\n";
        return {};
    }
    if (!is_polygon(polygon2)) {
        std::cout << "The second argument isn't a polygon.\n";
        return {};
    }
    Point<point_size> intersection_point;
    std::vector<Point<point_size>> all_points;
    for (size_t i = 0; i < polygon1.size(); i++) {
        for (size_t j = 0; j < polygon2.size(); j++) {

            intersection_point = lines_intersection(polygon1.vertexe_[i], polygon1.vertexe_[(i + 1) % polygon1.size()],
                                                    polygon2.vertexe_[j], polygon2.vertexe_[(j + 1) % polygon2.size()]);
            if (intersection_point.is_exist()) {
                all_points.push_back(intersection_point);
            }

        }
    }

    for (size_t i = 0; i < polygon2.size(); i++) {
        if (point_in_polygon(polygon1, polygon2.get_point(i))) {
            all_points.push_back(polygon2.get_point(i));
        }
    }

    for (size_t i = 0; i < polygon1.size(); i++) {
        if (point_in_polygon(polygon2, polygon1.get_point(i))) {
            all_points.push_back(polygon1.get_point(i));
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

