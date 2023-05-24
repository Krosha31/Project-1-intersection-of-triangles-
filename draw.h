#pragma once

#include<iostream>
#include<initializer_list>
#include <SFML/Graphics.hpp>
#include "triangle.h"

class Draw {
private:

	sf::VertexArray points1_;
	sf::VertexArray points2_;
	sf::VertexArray points3_;

	size_t windowsize_ = 800;

	sf::ConvexShape shape_constructing(const sf::Vector2f center, \
		const sf::VertexArray points, bool is_intersection);

	sf::VertexArray axes_constructing();

public:

	Draw() = default;

	Draw(const Draw &rhs) = default;

	Draw(Draw&& rhs) noexcept;

	template<size_t point_size>
	Draw(const Triangle<point_size>& first, const Triangle<point_size>& second);

	template<size_t point_size>
	Draw(const std::initializer_list<Point<point_size>> &list);	
	
	void set_window(const size_t size);

	void dimension_check(size_t point_size);

	template<size_t point_size>
	sf::Vector2f point2vector2f(const Point<point_size>& p);

	template<size_t point_size>
	sf::VertexArray vector2vertex(const std::vector<Point<point_size>> &v_points);

	template<size_t point_size>
	void intersection(const Triangle<point_size>& triangle1, \
		const Triangle<point_size>& triangle2);

	void scale_coordinates();

	void draw_all();

	~Draw() = default;
};

#include "draw.tpp"