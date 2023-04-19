#include "Polyhedron.h"

Polyhedron::Polyhedron(const Polyhedron &poly) {
    points = poly.points;
    edges = poly.edges;
}

Polyhedron::Polyhedron(Polyhedron &&poly) noexcept {
    points = std::move(poly.points);
    edges = std::move(poly.edges);
}

Polyhedron::Polyhedron(const std::vector<Point<3>> &points, const std::vector<std::vector<bool>> &edges) {
    this->points = points;
    this->edges = edges;
}
