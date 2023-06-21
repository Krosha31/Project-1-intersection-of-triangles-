#include <gtest/gtest.h>

#include <iostream>
#include <vector>
#include "point.h"
#include "triangle.h"
//#include "Draw.h"
//#include <SFML/Graphics.hpp>







TEST(Point, Constructors)
{
    Point<3> a {1, 2, 3};
    ASSERT_TRUE(a.get_dim() == 3);
    ASSERT_TRUE(a.get_coord(1) == 2);
    ASSERT_THROW(a.get_coord(4), std::logic_error);
    Point<3> b;{};
    ASSERT_TRUE(b.is_exist() == false);
    b = a;
    b.set_coord(0, 5);
    ASSERT_TRUE(a.get_coord(0) != b.get_coord(0));
}


TEST(Point, Lines) {
    //Parallel lines
    Point<2> a {1, 1};
    Point<2> b {5, 5};
    Point<2> c {3, 1};
    Point<2> d {7, 1};
    ASSERT_TRUE(lines_intersection(a, b, c, d) == Point<2>());
    c = {0, 4};
    d = {4, 0};
    Point<2> result{2, 2};
    ASSERT_TRUE(lines_intersection(a, b, c, d) == result);

    c = {7, 7};
    d = {9, 9};
    ASSERT_TRUE(lines_intersection(a, b, c, d) == Point<2>());

    c = {0, 4};
    d = {-4, 8};
    ASSERT_TRUE(lines_intersection(a, b, c, d) == Point<2>());
}


TEST(Triangle, Conctructors) {
    Point<2> a{0, 4};
    Point<2> b{1, 1};
    Point<2> c{5, 5};
    Triangle<2> tr{a, b, c};
    ASSERT_TRUE(is_triangle(tr));
    ASSERT_TRUE(tr.get_point(1) == b);
    tr.set_point(0, {2, 2});
    ASSERT_TRUE(!is_triangle(tr));
}

TEST(Triangle, Intersections) {
    Point<2> a, b, c, d, e, f;
    a = {0, 4};
    b = {1, 1};
    c = {4, 4};
    d = {1.6, 3.7};
    e = {1, 2.8};
    f = {2, 2.8};
    Triangle<2> tr1{a, b, c};
    Triangle<2> tr2{d, e, f};
    std::vector<Point<2>> answer {d, e, f};
    std::sort(answer.begin(), answer.end());
    // triangle in triangle
    ASSERT_TRUE(triangle_intersection(tr1, tr2) == answer);

    d = {2, 4};
    tr2 = {d, e, f};
    answer = {d, e ,f};
    std::sort(answer.begin(), answer.end());
    //triangle in triangle, but there is one common vertex
    ASSERT_TRUE(triangle_intersection(tr1, tr2) == answer);

    d = {2.1, 5.4};
    f = {3, 3};
    tr2 = {d, e, f};
    answer = {{2.625, 4}, {static_cast<double>(98) / 65, 4}, e, f};
    std::sort(answer.begin(), answer.end());
    // tro points of intersection and two points in the triangle
    ASSERT_TRUE(triangle_intersection(tr1, tr2) == answer);

    tr2 = {d, a, c};
    answer = {a, c};
    // two common vertex
    ASSERT_TRUE(triangle_intersection(tr1, tr2) == answer);

    e = {6, 6};
    tr2 = {e, a, d};
    answer = {a};
    //one common vertex
    ASSERT_TRUE(triangle_intersection(tr1, tr2) == answer);

    d = {100, 100};
    e = {200, 200};
    f = {200, 100};
    tr2 = {d, e, f};
    answer = {};
    // no points
    ASSERT_TRUE(triangle_intersection(tr1, tr2) == answer);
}



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}



