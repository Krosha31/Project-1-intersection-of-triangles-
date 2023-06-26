#include "Polyhedron.h"
#include <set>
#include <algorithm>

static const double eps = 0.001;

bool is_correct(const std::vector<Point<3>> &points, const std::vector<std::vector<bool>> &edges);

Polyhedron::Polyhedron(const Polyhedron &poly) {
    points_ = poly.points_;
    edges_ = poly.edges_;
}

Polyhedron::Polyhedron(Polyhedron &&poly) noexcept {
    points_ = std::move(poly.points_);
    edges_ = std::move(poly.edges_);
}

Polyhedron::Polyhedron(const std::vector<Point<3>> &points, const std::vector<std::vector<bool>> &edges) {
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
        for (size_t i = 0; i < poly.edges_.size(); ++i) {
            for (size_t j = 0; j < poly.edges_[0].size(); ++j) {
                std::cout << poly.edges_[i][j] << ' ';
            }
            out << '\n';
        }
    }
    return out;
}

std::istream &operator>>(std::istream &in, Polyhedron &poly) {
    size_t size_poly;
    std::cout << "Enter the number of polyhedron's points" << std::endl;
    in >> size_poly;
    std::vector<Point<3>> points(size_poly);
    std::vector<std::vector<bool>> edges(size_poly, std::vector<bool>(size_poly));

    std::cout << "Enter the polyhedron's points" << std::endl;
    for (size_t i = 0; i < size_poly; i++) {
        in >> points[i];
    }

    std::cout << "Enter the adjacency matrix for the points" << std::endl;
    for (size_t i = 0; i < size_poly; i++) {
        for (size_t j = 0; j < size_poly; j++) {
            int temp;
            in >> temp;
            edges[i][j] = (temp != 0);
        }
    }
    poly = Polyhedron(points, edges);
    return in;
}

bool m_det(const std::vector<double> &m) {
    return std::abs(m[0] * m[4] * m[8] + m[2] * m[3] * m[7] + m[1] * m[5] * m[6] - m[2] * m[4] * m[6] - m[0] * m[5] * m[7] - m[1] * m[3] * m[8]) < eps;
}

bool check_plane(const std::vector<Point<3>> &points) {
    for (int i = 3; i < points.size(); ++i) {
        if (!m_det({points[i].get_coord(0) - points[0].get_coord(0), points[i].get_coord(1) - points[0].get_coord(1), points[i].get_coord(2) - points[0].get_coord(2),
                    points[1].get_coord(0) - points[0].get_coord(0), points[1].get_coord(1) - points[0].get_coord(1), points[1].get_coord(2) - points[0].get_coord(2),
                    points[2].get_coord(0) - points[0].get_coord(0), points[2].get_coord(1) - points[0].get_coord(1), points[2].get_coord(2) - points[0].get_coord(2)}))
            return false;
    }
    return true;
}

bool remove_other(std::vector<std::vector<size_t>> &vec, const std::vector<Point<3>> &points) {
    std::sort(vec.begin(), vec.end(), [](const std::vector<size_t> &a, const std::vector<size_t> &b) { return a.size() < b.size(); });
    for (auto &i: vec) {
        std::sort(i.begin(), i.end());
    }
    size_t cur = 0;
    while (cur < vec.size() - 1) {
        for (size_t i = cur + 1; i < vec.size(); ++i) {
            bool flag = true;
            for (size_t j = 0; j < vec[cur].size(); ++j) {
                if (std::find(vec[i].begin(), vec[i].end(), vec[cur][j]) == vec[i].end()) {
                    flag = false;
                }
            }
            if (flag) {
                std::erase(vec, vec[i]);
            }
        }
        ++cur;
    }
    for (const auto &i: vec) {
        std::vector<Point<3>> tmp;
        tmp.resize(i.size());
        for (auto j: i) {
            tmp.push_back(points[j]);
        }
        if (!(i.size() > 3 and check_plane(tmp))) {
            return false;
        }
        tmp.clear();
    }
    return true;
}


bool is_correct(const std::vector<Point<3>> &points, const std::vector<std::vector<bool>> &edges) {
    if (points.empty() or points.size() < 4 or edges.size() != points.size() or edges[0].size() != points.size() or check_plane(points)) {
        return false;
    }
    return true;
}