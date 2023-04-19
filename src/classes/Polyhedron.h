#ifndef POLYHEDRON_H
#define POLYHEDRON_H

#include <vector>
#include <iostream>
#include "Point.h"

template<size_t T>
class Point {
public:
    int x = 0, y = 0, z = 0;;
};


class Polyhedron {
private:
    std::vector<Point<3>> points{};

    std::vector<std::vector<bool>> edges{}; //-> chmod idea

    explicit Polyhedron(const std::vector<Point<3>> &points, const std::vector<std::vector<bool>> &edges);

public:
    Polyhedron() = default;

    Polyhedron(const Polyhedron &poly);

    Polyhedron(Polyhedron &&poly) noexcept;

    Polyhedron &operator=(const Polyhedron &poly);

    Polyhedron &operator=(Polyhedron &&poly) noexcept;

    friend std::ostream &operator<<(std::ostream &out, const Polyhedron &poly);

    friend std::istream &operator>>(std::istream &in, Polyhedron &poly);

    ~Polyhedron() = default;
};

#endif
