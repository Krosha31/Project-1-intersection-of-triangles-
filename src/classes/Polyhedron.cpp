#include "Polyhedron.h"

Polyhedron::Polyhedron(const Polyhedron &poly) {
    points = poly.points;
    edges = poly.edges;
}

Polyhedron::Polyhedron(Polyhedron &&poly) noexcept {
    points = std::move(poly.points);
    edges = std::move(poly.edges);
}

bool is_correct(const std::vector<Point<3>> &points, const std::vector<std::vector<unsigned int>> &edges) {
    /*
    Create polyhedron ticket
    */
};

Polyhedron::Polyhedron(const std::vector<Point<3>> &points, const std::vector<std::vector<unsigned int>> &edges) {
    if (!is_correct(points, edges))
        throw std::logic_error("Can't create polyhedron");
    this->points = points;
    this->edges = edges;
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
        for (const Point<3> &p: poly.points) {
            out << p << '\n';
        }
        out << '\n';
        for (size_t i = 0; i < poly.points.size(); ++i) {
            size_t k = 0;
            for (size_t j = 0; j < poly.points.size(); ++j) {
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
        std::vector<std::vector<unsigned int>> edges{};
        /*
        Create polyhedron ticket
        */
        poly = Polyhedron(points, edges);
    }
    return in;
}
