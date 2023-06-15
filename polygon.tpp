#pragma once
#include "polygon.h"
#include <algorithm>

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
    if (point_size != 2) {
        return false;
    }
    size_t size = pl.vertexe_.size();
    double square_polygon = 0;
    //вычисляем по формуле Гаусса площадь многоугольника
    for(int i=0; i < size - 1; ++i){
        square_polygon += pl.vertexe_[i].get_coord(0) * pl.vertexe_[i + 1].get_coord(1);
        square_polygon -= pl.vertexe_[i + 1].get_coord(0) * pl.vertexe_[i].get_coord(1);
    }
    square_polygon += pl.vertexe_[size - 1].get_coord(0) * pl.vertexe_[0].get_coord(1);
    square_polygon -= pl.vertexe_[0].get_coord(0) * pl.vertexe_[size - 1].get_coord(1);
    return (square_polygon != 0.0);
}

