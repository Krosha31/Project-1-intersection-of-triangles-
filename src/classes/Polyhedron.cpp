#include "Polyhedron.h"

Polyhedron::Polyhedron(const Polyhedron &poly) {
    points = poly.points;
    edges = poly.edges;
}

Polyhedron::Polyhedron(Polyhedron &&poly) noexcept {
    points = std::move(poly.points);
    edges = std::move(poly.edges);
}

Polyhedron::Polyhedron(const std::vector<Point<3>> &points, const std::vector<std::vector<int>> &edges) {
    this->points = points;
    this->edges = edges;
}

Polyhedron &Polyhedron::operator=(const Polyhedron &poly) {
    points = poly.points;
    edges = poly.edges;
    return *this;
}

Polyhedron &Polyhedron::operator=(Polyhedron &&poly) noexcept {
    if (this == &poly)
        return *this;
    points = std::move(poly.points);
    edges = std::move(poly.edges);
    return *this;
}

std::ostream &operator<<(std::ostream &out, const Polyhedron &poly) {
    if (poly.points.empty()) {
        out << "Empty\n";
    } else {
        for (Point<3> p: poly.points) {
            out << p.x << ' ' << p.y << ' ' << p.z << '\n';
        }
        out << '\n';
        for (int i = 0; i < poly.points.size(); ++i) {
            size_t k = 0;
            for (int j = 0; j < poly.points.size(); ++j) {
                if (k < poly.edges[i].size() and poly.edges[i][k] == j) {
                    out << '1';
                    ++k;
                } else {
                    out << '0';
                }

            }
            out << '\n';
        }
    }
    return out;
}

std::istream &operator>>(std::istream &in, Polyhedron &poly) {
    std::string s_poly;
    in >> s_poly;
    if (s_poly.empty()) {
        poly = Polyhedron();
    } else {
        std::vector<Point<3>> points{};
        std::vector<std::vector<int>> edges{};
        /*
        Create polyhedron ticket
        */
        poly = Polyhedron(points, edges);
    }
    return in;
}
