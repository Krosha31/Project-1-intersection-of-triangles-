#include <iostream>
#include "src/point/point.h"
#include "src/triangle/triangle.h"
#include "Draw.h"


int main() {
    std::cout << "Please enter the points of first triangle:\n";
    Point<2> p1, p2, p3;
    std::cin >> p1 >> p2 >> p3;
    Triangle<2> tr1 {p1, p2, p3};
    std::cout << '\n';
    std::cout << "Please enter the points of second triangle:\n";
    std::cin >> p1 >> p2 >> p3;
    Triangle<2> tr2 {p1, p2, p3};
    std::vector<Point<2>> intersection_points = triangle_intersection(tr1, tr2);
    if (intersection_points.empty()) {
        std::cout << "The triangles don't intersect";
    }
    else {
        std::cout << "Intersection points:\n";
        for (auto item: intersection_points) {
            std::cout << item << " ";
        }
    }
    Draw draw {tr1, tr2};
    draw.draw_all();
    return 0;
}


