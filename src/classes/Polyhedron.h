#ifndef POLYHEDRON_H
#define POLYHEDRON_H

#include <vector>
#include "Point.h"

template<size_t T>
class Point{

};


class Polyhedron {
private:
    std::vector<Point<3>> points{};
    std::vector<std::vector<bool>> edges{}; //-> chmod
public:
    Polyhedron() = default;

    explicit Polyhedron(const std::vector<Point<3>> &points, const std::vector<std::vector<bool>> &edges);

    Polyhedron(const Polyhedron &poly);

    Polyhedron(Polyhedron &&poly) noexcept;

};

#endif
