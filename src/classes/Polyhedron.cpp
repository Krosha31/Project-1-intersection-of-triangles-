#include "Polyhedron.h"
#include <set>
#include <algorithm>

#include <unordered_map>

static const int tetrahedron_size = 4;
static const double eps = 0.001;

Polyhedron::Polyhedron(const Polyhedron &poly) {
    points_ = poly.points_;
    edges_ = poly.edges_;
}

Polyhedron::Polyhedron(Polyhedron &&poly) noexcept {
    points_ = std::move(poly.points_);
    edges_ = std::move(poly.edges_);
}

Polyhedron::Polyhedron(const std::vector<Point<3>> &points, const std::vector<std::vector<bool>> &edges) {
//    if (!is_correct(points, edges))
//        throw std::logic_error("Can't create polyhedron");
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

std::vector<std::vector<size_t>> remove_other(std::vector<std::vector<size_t>> &vec) {
    std::sort(vec.begin(), vec.end(), [](const std::vector<size_t> &a, const std::vector<size_t> &b) { return a.size() < b.size(); });
    for (auto &i: vec) {
        std::sort(i.begin(), i.end());
    }
    size_t cur = 0;
    while (cur < vec.size() - 1) {
        for (int i = cur + 1; i < vec.size(); ++i) {

        }
        ++cur;
    }
    return vec;
}


void dfs(size_t point_number, const std::vector<std::vector<bool>> &edges, std::vector<bool> &was) {
    was[point_number] = true;
    for (size_t i = 0; i < edges[point_number].size(); i++) {
        if (edges[point_number][i] && !was[i]) {
            dfs(i, edges, was);
        }
    }
}

//bool is_correct(const std::vector<Point<3>> &points, const std::vector<std::vector<bool>> &edges) {
//    if (points.empty() or edges.size() != points.size() or edges[0].size() != points.size() or !check_plane(points)) {
//        return false;
//    }
//
//    std::vector<bool> was(points.size(), false);
//    dfs(0, edges, was);
//    for (auto item: was) {
//        if (!item) {
//            return false;
//        }
//    }
//    for (size_t i = 0; i < points.size(); i++) {
//        for (size_t j = 0; j < points.size(); j++) {
//            for (size_t k = 0; k < points.size(); k++) {
//                for (size_t t = 0; t < points.size(); t++) {
//                    std::set<size_t> four_points{i, j, k, t};
//                    if (four_points.size() < 4) {
//                        continue;
//                    }
//                    std::vector<double> a(3);
//                    std::vector<double> b(3);
//                    std::vector<double> c(3);
//                    for (size_t s = 0; s < 3; s++) {
//                        a[s] = points[j].get_coord(s) - points[i].get_coord(s);
//                        b[s] = points[k].get_coord(s) - points[i].get_coord(s);
//                        c[s] = points[t].get_coord(s) - points[i].get_coord(s);
//                    }
//                    double determinant = 0;
//                    determinant += a[0] * (b[1] * c[2] - b[2] * c[1]);
//                    determinant -= a[1] * (b[0] * c[2] - b[2] * c[0]);
//                    determinant += a[2] * (b[0] * c[1] - b[1] * c[0]);
//                    if (abs(determinant) < eps) {
//                        return false;
//                    }
//                }
//            }
//        }
//    }
//
//    std::cout << 1;
//    for (size_t i = 0; i < edges.size(); i++) {
//        for (size_t j = i + 1; j < edges.size(); j++) {
//            if (!edges[i][j]) {
//                continue;
//            }
//            std::pair<unsigned int, unsigned int> third_points{-1, -1};
//            for (size_t k = 0; k < edges.size(); k++) {
//                if (k == i && k == j) {
//                    continue;
//                }
//                if (edges[i][k] && edges[j][k]) {
//                    Triangle<3> temp_triangle{points[i], points[j], points[k]};
//                    if (is_triangle(temp_triangle)) {
//                        if (third_points.first == -1) {
//                            third_points.first = k;
//                        } else if (third_points.second == -1) {
//                            third_points.second = k;
//                        } else {
//                            return false;
//                        }
//                    } else {
//                        return false;
//                    }
//                }
//            }
//            if (third_points.second == -1) {
//                return false;
//            }
//
//        }
//    }
//    return true;
//}