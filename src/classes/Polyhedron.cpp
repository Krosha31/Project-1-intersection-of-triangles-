#include "Polyhedron.h"

const int tetrahedron_size = 4;

Polyhedron::Polyhedron(const Polyhedron &poly) {
    points = poly.points;
    edges = poly.edges;
}

Polyhedron::Polyhedron(Polyhedron &&poly) noexcept {
points = std::move(poly.points);
edges = std::move(poly.edges);
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
    std::cout << "Enter tetrahedron's points:" << std::endl;
    std::vector<Point<3>> points(tetrahedron_size);
    std::vector<std::vector<unsigned int>> edges(tetrahedron_size, std::vector<unsigned int>(tetrahedron_size, 1));
    for (int i = 0; i < tetrahedron_size; i++) {
        in >> points[i];
    }
    poly = Polyhedron();
    return in;

    /*
    std::string s_poly;
    in >> s_poly;
    if (s_poly.empty()) {
        poly = Polyhedron();
    } else {
        std::vector<Point<3>> points{};
        std::vector<std::vector<unsigned int>> edges{};


        poly = Polyhedron(points, edges);
    }
     */

    // input for polyhedron
    /*
    size_t size_poly;
    std::cout << "Enter number of polyhedron's points" << std::endl;
    in >> size_poly;
    std::cout << "Enter polyhedron's points" << std::endl;
    std::vector<Point<3>> points(size_poly);
    std::vector<std::vector<unsigned int>> edges(size_poly, std::vector<unsigned int>(size_poly));

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
     */
}
