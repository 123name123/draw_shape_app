//
// Created by Elisey Muxin on 24.02.2023.
//
#pragma once

#include <vector>
#include <iostream>


struct Point {
    double x_, y_;

    Point() = default;

    Point(double x, double y) noexcept;
};


/* Abstract class for shapes */

class Shape {
public:
    virtual bool is_point_in_figure(const Point &point) const noexcept = 0; // check if point in shape

    virtual void draw() const = 0; // draw shape in the console

    virtual ~Shape() = default;

    static constexpr double eps = 0.00000001; // constant to make correct comparisons
};


/* Circle shape */

class Circle : public Shape {
public:
    Circle() = default;

    Circle(double radius) noexcept;

    bool is_point_in_figure(const Point &point) const noexcept override;

    void draw() const override;

private:
    double radius_{0}; // radius of circle
};


/* RegularPolygon shape */

class RegularPolygon : public Shape {
public:
    RegularPolygon() = default;

    RegularPolygon(size_t n, double size) noexcept;

    bool is_point_in_figure(const Point &point) const noexcept override;

    void draw() const override;

private:
    size_t n_{0}; // number of sides
    double size_{0}; // size of side
    std::vector<Point> data_; // shape points
};


/* Rectangle shape */

class Rectangle : public Shape {
public:
    Rectangle() = default;

    Rectangle(double width, double height) noexcept;

    bool is_point_in_figure(const Point &point) const noexcept override;

    void draw() const override;

private:
    double width_{0}; // rectangle width
    double height_{0}; // rectangle height
};