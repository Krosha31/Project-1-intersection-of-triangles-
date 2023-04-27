#include "Polyhedron.h"

const int tetrahedron_size = 4;

Polyhedron::Polyhedron(const Polyhedron &poly) {
    points_ = poly.points_;
    edges_ = poly.edges_;
}

Polyhedron::Polyhedron(Polyhedron &&poly) noexcept {
    points_ = std::move(poly.points_);
    edges_ = std::move(poly.edges_);
}

bool is_correct(const std::vector<Point<3>> &points, const std::vector<std::vector<unsigned int>> &edges) {
    if (points.size() == tetrahedron_size) {
        for (size_t i = 0; i < tetrahedron_size; i++)
            for (size_t j = i + 1; j < tetrahedron_size; j++)
                for (size_t k = j + 1; k < tetrahedron_size; k++)
                    if (!is_triangle(points[i], points[j], points[k]))
                        return false;
        return true;
    }
    return false; // needed changes for point's number > 4
}

Polyhedron::Polyhedron(const std::vector<Point<3>> &points, const std::vector<std::vector<unsigned int>> &edges) {
    if (!is_correct(points, edges))
        throw std::logic_error("Can't create polyhedron");
    this->points_ = points;
    this->edges_ = edges;
}

Polyhedron &Polyhedron::operator=(Polyhedron &&poly) noexcept {
    if (this == &poly)
        return *this;
    points_ = std::move(poly.points_);
    edges_ = std::move(poly.edges_);
    return *this;
}

std::ostream &operator<<(std::ostream &out, const Polyhedron &poly) {
    if (poly.points_.empty()) {
        out << "Empty\n";
    } else {
        for (const Point<3> &p: poly.points_) {
            out << p << '\n';
        }
        out << '\n';
        for (size_t i = 0; i < poly.points_.size(); ++i) {
            size_t k = 0;
            for (size_t j = 0; j < poly.points_.size(); ++j) {
                if (k < poly.edges_[i].size() and poly.edges_[i][k] == j) {
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
    size_t size_poly;
    std::cout << "Enter number of polyhedron's points" << std::endl;
    in >> size_poly;
    std::vector<Point<3>> points(size_poly);
    std::vector<std::vector<unsigned int>> edges(size_poly, std::vector<unsigned int>(size_poly));

    std::cout << "Enter polyhedron's points" << std::endl;
    for (size_t i = 0; i < size_poly; i++) {
        in >> points[i];
    }

    std::cout << "Enter the adjacency matrix for points";
    for (size_t i = 0; i < size_poly; i++) {
        for (size_t j = 0; j < size_poly; j++) {
            in >> edges[i][j];
        }
    }
    poly = Polyhedron(points, edges);
    return in;
}
