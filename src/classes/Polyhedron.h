#ifndef POLYHEDRON_H
#define POLYHEDRON_H

#include <vector>
#include <iostream>
#include "Point.h"


class Polyhedron {
private:
    std::vector<Point<3>> points{};

    std::vector<std::vector<unsigned int>> edges{}; //-> chmod idea for < 64 vertices

public:
    Polyhedron() = default;

    explicit Polyhedron(const std::vector<Point<3>> &points, const std::vector<std::vector<unsigned int>> &edges);

    Polyhedron(const Polyhedron &poly);

    Polyhedron(Polyhedron &&poly) noexcept;

    Polyhedron &operator=(const Polyhedron &poly) = default;

    Polyhedron &operator=(Polyhedron &&poly) noexcept;

    friend std::ostream &operator<<(std::ostream &out, const Polyhedron &poly);

    friend std::istream &operator>>(std::istream &in, Polyhedron &poly);

    ~Polyhedron() = default;
};

#endif
