#pragma once
#include "draw.h"

// private

sf::ConvexShape Draw::shape_constructing(const sf::Vector2f center, \
    const sf::VertexArray points, bool is_intersection) {
    sf::ConvexShape shape;  // объявление

    shape.setPosition(center);    // позиция середины фигуры

    // число вершин
    size_t n = points.getVertexCount();
    shape.setPointCount(n);

    for (size_t i = 0; i < n; i++) {
        shape.setPoint(i, points[i].position);
    }

    if (is_intersection) {
        shape.setFillColor(sf::Color::Green); // цвет заполнения
    }

    // задаём контур (толщину, цвет) 
    shape.setOutlineThickness(1);
    shape.setOutlineColor(sf::Color::Black);

    return shape;
}

sf::VertexArray Draw::axes_constructing() {
    // оси координат
    sf::VertexArray axes(sf::Lines, 12);
    size_t shift = 10;
    // X
    axes[0].position = sf::Vector2f(0, windowsize_ / 2);
    axes[1].position = sf::Vector2f(windowsize_, windowsize_ / 2);
    // Y
    axes[2].position = sf::Vector2f(windowsize_ / 2, windowsize_);
    axes[3].position = sf::Vector2f(windowsize_ / 2, 0);
    // стрелочки X
    axes[4].position = sf::Vector2f(windowsize_ - shift, windowsize_ / 2 - shift);
    axes[5].position = sf::Vector2f(windowsize_, windowsize_ / 2);
    axes[6].position = sf::Vector2f(windowsize_, windowsize_ / 2);
    axes[7].position = sf::Vector2f(windowsize_ - shift, windowsize_ / 2 + shift);
    // стрелочки Y
    axes[8].position = sf::Vector2f(windowsize_ / 2 - shift, shift);
    axes[9].position = sf::Vector2f(windowsize_ / 2, 0);
    axes[10].position = sf::Vector2f(windowsize_ / 2, 0);
    axes[11].position = sf::Vector2f(windowsize_ / 2 + shift, shift);
    // цвет осей
    for (size_t i = 0; i < 12; i++) {
        axes[i].color = sf::Color::Black;
    }

    return axes;
}


// public
 
Draw::Draw(Draw&& rhs) noexcept {
    this->points1_ = std::move(rhs.points1_);
    this->points2_ = std::move(rhs.points2_);
    this->points3_ = std::move(rhs.points3_);
    this->windowsize_ = rhs.windowsize_;

}

template<size_t point_size>
Draw::Draw(const Triangle<point_size>& first, const Triangle<point_size>& second) {
    // проверка размерности
    dimension_check(point_size);
    
    // проверка треугольников
    if ((!is_triangle(first)) || (!is_triangle(second))) {
        throw std::logic_error("Incorrect triangles");
    }

    // заполняем points1_ и points2_
    points1_.setPrimitiveType(sf::Points);
    points2_.setPrimitiveType(sf::Points);
    for (size_t i = 0; i < 3; i++) {
        points1_.append(point2vector2f(first.get_point(i)));
        points2_.append(point2vector2f(second.get_point(i)));
    }

    // ищем область пересечения (заполняем points3_)
    intersection(first, second);

}

template<size_t point_size>
Draw::Draw(const std::initializer_list<Point<point_size>>& list) {
    // проверка размерности
    dimension_check(point_size);

    std::vector<Point<point_size>> tmp = list;
    if (tmp.size() != 6) {
        throw std::logic_error("Incorrect number of points in two triangles");
    }
    
    // делим вектор tmp на две части
    std::vector<Point<point_size>> first(tmp.begin(), \
        tmp.begin() + tmp.size() / 2);
    std::vector<Point<point_size>> second(tmp.begin() + tmp.size() / 2, \
        tmp.begin() + tmp.size());
    tmp.clear();

    // заполняем points1_ и points2_
    points1_ = vector2vertex(first);
    points2_ = vector2vertex(second);

    // заполняем points3_
    Triangle triangle1{ first };
    Triangle triangle2{ second };
    intersection(triangle1, triangle2);
}

void Draw::set_window(const size_t size) {
    windowsize_ = size;
}

void Draw::dimension_check(size_t point_size) {
    if (point_size != 2) {
        throw std::logic_error("Incorrect dimension. Must be 2!");
    }
}

template<size_t point_size>
sf::Vector2f Draw::point2vector2f(const Point<point_size>& p) {
    // проверка размерности
    dimension_check(point_size);

    return sf::Vector2f(p.get_coord(0), p.get_coord(1));
}

template<size_t point_size>
sf::VertexArray Draw::vector2vertex(const std::vector<Point<point_size>>& v_points) {
    sf::VertexArray points(sf::Points, v_points.size());
    for (size_t i = 0; i < v_points.size(); i++) {
        points[i].position = point2vector2f(v_points[i]);
    }
    return points;
}

template<size_t point_size>
void Draw::intersection(const Triangle<point_size>& triangle1, \
    const Triangle<point_size>& triangle2) {
    // проверка треугольников
    if ((!is_triangle(triangle1)) || (!is_triangle(triangle2))) {
        throw std::logic_error("Incorrect triangles");
    }

    // ищем область пересечения (заполняем points3_)
    std::vector<Point<point_size>> inter_points = triangle_intersection(triangle1, triangle2);
    points3_ = vector2vertex(inter_points);
}

void Draw::scale_coordinates() {
    //Находим максимальные значения по X и Y
    float maxX = std::max({
        points1_[0].position.x, points1_[1].position.x, points1_[2].position.x,
        points2_[0].position.x, points2_[1].position.x, points2_[2].position.x
        });

    float maxY = std::max({
        points1_[0].position.y, points1_[1].position.y, points1_[2].position.y,
        points2_[0].position.y, points2_[1].position.y, points2_[2].position.y
        });

    float minX = std::min({
        points1_[0].position.x, points1_[1].position.x, points1_[2].position.x,
        points2_[0].position.x, points2_[1].position.x, points2_[2].position.x
        });

    float minY = std::min({
        points1_[0].position.y, points1_[1].position.y, points1_[2].position.y,
        points2_[0].position.y, points2_[1].position.y, points2_[2].position.y
        });
    //Масштабируем, если это требуется
    float maxAbs = std::max({ std::abs(maxX), std::abs(maxY), std::abs(minX), std::abs(minY) });
    float minAbs = std::min({ std::abs(maxX), std::abs(maxY), std::abs(minX), std::abs(minY) });

    if (maxAbs > windowsize_ / 2) {
        // Находим максимальную разницу по X и Y
        float maxDiff = std::max(maxX - minX, maxY - minY);
        // Вычисляем коэффициент масштабирования
        float scaleFactor = maxDiff / (windowsize_ / 2);

        // Масштабируем координаты всех точек
        if (scaleFactor > 1.0f) {
            scaleFactor = 1.0f / scaleFactor;
        }
        for (size_t i = 0; i < points1_.getVertexCount(); ++i) {
            points1_[i].position *= scaleFactor;
        }
        for (size_t i = 0; i < points2_.getVertexCount(); ++i) {
            points2_[i].position *= scaleFactor;
        }
        for (size_t i = 0; i < points3_.getVertexCount(); ++i) {
            points3_[i].position *= scaleFactor;
        }
    } else if(minAbs < windowsize_ / 15) {  //Треугольник слишком маленький
         // Находим минимальную разницу по X и Y
         float minDiff = std::min(maxX - minX, maxY - minY);
         // Вычисляем коэффициент масштабирования
         float scaleFactor = (windowsize_ / 10) / minDiff;

         // Масштабируем координаты всех точек
         if (scaleFactor > 1.0f) {
             scaleFactor = 1.0f / scaleFactor;
         }
         for (size_t i = 0; i < points1_.getVertexCount(); ++i) {
             points1_[i].position /= scaleFactor;
         }
         for (size_t i = 0; i < points2_.getVertexCount(); ++i) {
             points2_[i].position /= scaleFactor;
         }
         for (size_t i = 0; i < points3_.getVertexCount(); ++i) {
             points3_[i].position /= scaleFactor;
         }
    }
}

void Draw::draw_all() {
    sf::Vector2f window_center(this->windowsize_ / 2, this->windowsize_ / 2);
    
    // оси координат
    sf::VertexArray coordinate_axes = axes_constructing();

    // масштабирование
    scale_coordinates();

    sf::ConvexShape triangle1 = shape_constructing(window_center, points1_, false); // треугольник 1
    sf::ConvexShape triangle2 = shape_constructing(window_center, points2_, false); // треугольник 2
    sf::ConvexShape intersection = shape_constructing(window_center, points3_, true); // область пересечения

    // Инвертирование оси y для каждого треугольника
    triangle1.setScale(1.f, -1.f);
    triangle2.setScale(1.f, -1.f);
    intersection.setScale(1.f, -1.f);

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(windowsize_, windowsize_), \
        "Two triangles and their intersection", sf::Style::Default, settings);
    
    window.setVerticalSyncEnabled(true); // This can avoid some visual artifacts, \
                                            and limit the framerate to a good value.

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::White);
        window.draw(triangle1);
        window.draw(triangle2);
        window.draw(intersection);
        window.draw(coordinate_axes);
        window.display();
    }
}
