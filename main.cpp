#include <iostream>
#include "point.h"
#include "polygon.h"
#include "Draw.h"


int main() {
    std::cout << "Please enter the number of the first polygon's points\n";
    size_t size1;
    std::cin >> size1;
    std::cout << '\n';
    std::cout << "Please enter the points of first polygon:\n";
    std::vector <Point<2>> points1(size1);
    for (size_t i = 0; i < size1; i++) {
        std::cin >> points1[i];
    }
    Polygon<2> polygon1 {points1};
    std::cout << '\n';
    std::cout << "Please enter the number of the second polygon's points\n";
    size_t size2;
    std::cin >> size2;
    std::cout << "Please enter the points of second polygon:\n";
    std::vector <Point<2>> points2(size2);
    for (size_t i = 0; i < size2; i++) {
        std::cin >> points2[i];
    }
    Polygon<2> polygon2 {points2};
    std::cout << '\n';
    std::vector<Point<2>> intersection_points = polygon_intersection(polygon1, polygon2);
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


