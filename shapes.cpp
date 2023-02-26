//
// Created by Elisey Muxin on 24.02.2023.
//

#include "shapes.h"
#include <cmath>

/* Point */

Point::Point(double x, double y) noexcept: x_(x), y_(y) {
}


/* Circle */

Circle::Circle(double radius) noexcept: radius_(radius) {
}

bool Circle::is_point_in_figure(const Point &point) const noexcept {
    if (point.x_ * point.x_ + point.y_ * point.y_ - eps <= radius_ * radius_) {
        return true;
    }
    return false;
}

void Circle::draw() const {
    std::cout << "\nCircle with radius: " << radius_ << "\n";
    int side = static_cast<int>(radius_) + 1;
    for (int x = -side; x <= side; ++x) {
        for (int y = side; y >= -side; --y) {
            std::cout << (is_point_in_figure(Point(x, y)) ? "*" : " ");
        }
        std::cout << "\n";
    }
}

std::vector<Point> Circle::shape_coordinates(Point shift) const noexcept {
    return {shift};
}


/* RegularPolygon */

RegularPolygon::RegularPolygon(size_t n, double size, double rotation_angle) noexcept: n_(n), size_(size) {
    data_.resize(n_);
    double num = 0;
    double radius = size_ / (2 * sin(M_PI / static_cast<double>(n)));
    for (auto &[x, y]: data_) {
        auto angle = 2 * M_PI * num / static_cast<double>(n) + rotation_angle;
        x = radius * cos(angle);
        y = radius * sin(angle);
        ++num;
    }
}

bool RegularPolygon::is_point_in_figure(const Point &point) const noexcept {
    size_t count = 0;
    for (size_t i = 0; i < data_.size(); i++) {
        Point shape_a = data_[i];
        Point shape_b = data_[(i + 1) % data_.size()];
        if ((shape_a.y_ > point.y_ + eps) != (shape_b.y_ > point.y_ + eps)) {
            double x = (shape_b.x_ - shape_a.x_) * (point.y_ - shape_a.y_) /
                       (shape_b.y_ - shape_a.y_) + shape_a.x_;
            if (point.x_ + eps < x) {
                ++count;
            }
        }
    }
    return count % 2;
}

void RegularPolygon::draw() const {
    std::cout << "\nRegular Polygon with number of angles: " << n_ << " and size of side: " << size_ << "\n";
    int side = static_cast<int>(size_) + 1;
    for (int x = -side; x <= side; ++x) {
        for (int y = side; y >= -side; --y) {
            std::cout << (is_point_in_figure(Point(x, y)) ? "*" : " ");
        }
        std::cout << "\n";
    }
}

std::vector<Point> RegularPolygon::shape_coordinates(Point shift) const noexcept {
    std::vector<Point> result;
    result.reserve(data_.size());
    transform(data_.begin(), data_.end(), std::back_inserter(result),
              [shift](Point p) { return Point(p.x_ + shift.x_, p.y_ + shift.y_); });
    return result;
}


/* Square */

Square::Square(double width) noexcept: RegularPolygon(angle_num, width, M_PI / 4) {
}

/* Rectangle */

Rectangle::Rectangle(double width, double height) noexcept:
        width_(width),
        height_(height) {
}

bool Rectangle::is_point_in_figure(const Point &point) const noexcept {
    if (point.x_ + eps < -width_ / 2 || point.x_ > width_ / 2 + eps) {
        return false;
    }
    if (point.y_ + eps < -height_ / 2 || point.y_ > height_ / 2 + eps) {
        return false;
    }
    return true;
}

void Rectangle::draw() const {
    std::cout << "\nRectangle with sides: " << width_ << " " << height_ << "\n";
    int width = static_cast<int>(width_);
    int height = static_cast<int>(height_);
    for (int x = -width; x <= width; ++x) {
        for (int y = -height; y <= height; ++y) {
            std::cout << (is_point_in_figure(Point(x, y)) ? "*" : " ");
        }
        std::cout << "\n";
    }
}

std::vector<Point> Rectangle::shape_coordinates(Point shift) const noexcept {
    Point corner{width_ / 2, height_ / 2};
    return {Point(corner.x_ + shift.x_, corner.x_ + shift.y_),
            Point(corner.x_ + shift.x_, -corner.x_ + shift.y_),
            Point(-corner.x_ + shift.x_, -corner.x_ + shift.y_),
            Point(-corner.x_ + shift.x_, corner.x_ + shift.y_)};
}