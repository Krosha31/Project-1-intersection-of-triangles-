#ifndef POLYHEDRON_H
#define POLYHEDRON_H

#include <vector>
#include <iostream>
#include "../../classes/point.h"
#include "../../classes/triangle.h"

class Polyhedron {
//private:
public:
    std::vector<Point<3>> points_{};

    std::vector<std::vector<bool>> edges_{};

    [[nodiscard]] std::vector<std::pair<Triangle<3>, std::vector<size_t>>> gen_plates() const;
//
//public:
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

Point<3> base_intersect(const Triangle<3> &tri, const Point<3> &left, const Point<3> &right);

#endif
