#include "triangle.h"

template<size_t point_size>
Point<point_size>& Point<point_size>::operator=(const Point<point_size>& other){
    if (this == &other){
        return *this;
    }
    exist_ = other.exist_;
    x_ = other.x_;
    y_ = other.y_;
    z_ = other.z_;
    return *this;
}

template<size_t point_size>
std::ostream& operator<<(std::ostream& out, const Point<point_size>& point)
{
    //out << "Coordinates of the point: ";
    if (point.size_ == 3) {
        out << "(" << point.x_ << ", "<< point.y_ << ", " << point.z_<<  ")\n";
    }
    else{
        out << "(" << point.x_ << ", "<< point.y_ <<  ")\n";
    }
    return out;
}

template<size_t point_size>
std::ostream& operator<<(std::ostream& out, const Triangle<point_size>& triangle)
{
    //out << "Coordinates of the triangle: \n";
    out << "Triangle(";
    for (int i = 0; i < triangle.size_; i++){
        //out << i + 1 << " point: ";
        if (point_size == 3) {
            out << "(" << triangle.vertexe_[i].x_ << ", "<< triangle.vertexe_[i].y_ << ", " << triangle.vertexe_[i].z_ <<  ")";
        }
        else {
            out << "(" << triangle.vertexe_[i].x_ << ", " << triangle.vertexe_[i].y_ <<  ")";
        }
        if (i != triangle.size_ - 1){
            out << ", ";
        }
    }
    out << ")\n";
    return out;
}
template<size_t point_size>
bool is_triangle(const Triangle<point_size>& tr) {
    double square_triangle = fabs(((tr.vertexe_[1].x_ - tr.vertexe_[0].x_)*(tr.vertexe_[2].y_ - tr.vertexe_[0].y_) - (tr.vertexe_[2].x_ - tr.vertexe_[0].x_)*(tr.vertexe_[1].y_ - tr.vertexe_[0].y_)) / 2);
    return  (square_triangle != 0.0);
}

template<size_t point_size>
Point<point_size> lines_intersection(Point<point_size> p1, Point<point_size> p2, Point<point_size> p3, Point<point_size> p4) {
    if (p1.x_ >= p2.x_){
        std::swap(p1, p2);
    }
    if (p3.x_ >= p4.x_){
        std::swap(p3, p4);
    }
    if((p1.x_ == p2.x_) && (p3.x_ == p4.x_)) {
        //если они лежат на одном X
        if(p1.x_ == p3.x_) {
            //проверим не пересекаются ли они, т.е. есть ли у них общий Y
            if (!((std::max(p1.y_, p2.y_) < std::min(p3.y_, p4.y_)) || (std::min(p1.y_, p2.y_) > std::max(p3.y_, p4.y_)))) {
                return Point<point_size>(p1.x_, p3.y_);// додумать
            }
        }
        //std::cout << 1;
        return Point<point_size>();
    }

    double k1, k2;
    if (p1.x_ == p2.x_){
        k1 = 0;
    }
    else{
        k1 = (p2.y_ - p1.y_) / (p2.x_ - p1.x_);
    }

    if (p3.x_ == p4.x_){
        k2 = 0;
    }
    else{
        k2 = (p4.y_ - p3.y_) / (p4.x_ - p3.x_);
    }

    if (fabs(k1 - k2) < EPS) {
        //std::cout << k1 << " " << k2 << std::endl;
        std::cout << 2;

        return Point<point_size>();
    }

    double b1 = p1.y_ - k1 * p1.x_;
    double b2 = p3.y_ - k2 * p3.x_;
    double x = (b2 - b1) / (k1 - k2);
    double y = k1 * x + b1;

    if ((x < std::max(p1.x_, p3.x_)) || (x > std::min(p2.x_, p4.x_))) {
        //std::cout << 3;
        return Point<point_size>(); //точка X находится вне пересечения проекций отрезков на ось X
    }
    Point<point_size> intersection_point(x, y);
    return intersection_point;
}

template<size_t point_size>
bool triangle_intersection(const Triangle<point_size>& tr1, const Triangle<point_size>& tr2){
    Point<point_size> intersection_point;
    std::vector<Point<point_size>> all_points;
    if (!(is_triangle(tr1)) || !(is_triangle(tr2)))
    {
        std::cout << "This is not a triangle.";
        return false;
    }
    for (int i = 0; i < tr1.size_; i++){
        for (int j = 0; j < tr2.size_; j++)
        {
            intersection_point = lines_intersection(tr1.vertexe_[i], tr1.vertexe_[(i + 1) % 3], tr2.vertexe_[j], tr2.vertexe_[(j + 1) % 3]);
            if (intersection_point.exist_)
            {
                all_points.push_back(intersection_point);
            }

        }
    }
    if (all_points.empty())
        return false;
    for (int i = 0; i < all_points.size(); i++) {
        std::cout << all_points[i];
    }
    return true;
}
