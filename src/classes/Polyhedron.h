#ifndef POLYHEDRON_H
#define POLYHEDRON_H

#include <vector>
#include <iostream>
#include "../../classes/point.h"
#include "../polygon/polygon.h"

class Polyhedron {
private:
    std::vector<Point<3>> points_{};

    std::vector<std::vector<bool>> edges_{};

public:
    Polyhedron() = default;

    explicit Polyhedron(const std::vector<Point<3>> &points, const std::vector<std::vector<bool>> &edges);

    Polyhedron(const Polyhedron &poly);

    Polyhedron(Polyhedron &&poly) noexcept;

    Polyhedron &operator=(const Polyhedron &poly) = default;

    Polyhedron &operator=(Polyhedron &&poly) noexcept;

    friend std::ostream &operator<<(std::ostream &out, const Polyhedron &poly);

    friend std::istream &operator>>(std::istream &in, Polyhedron &poly);

    friend bool is_correct(const std::vector<Point<3>> &points, const std::vector<std::vector<bool>> &edges);

    ~Polyhedron() = default;
};

bool remove_other(std::vector<std::vector<size_t>> &vec);

#endif
