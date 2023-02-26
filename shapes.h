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
    /* check if point in shape */
    virtual bool is_point_in_figure(const Point &point) const noexcept = 0;

    /* draw shape in the console */
    virtual void draw() const = 0;

    /* return shape coordinates */
    virtual std::vector<Point> shape_coordinates(Point shift = Point(0, 0)) const noexcept = 0;

    virtual ~Shape() = default;

    /* constant to make correct comparisons */
    static constexpr double eps = 0.00000001;
};


/* Circle shape */

class Circle : public Shape {
public:
    Circle() = default;

    Circle(double radius) noexcept;

    bool is_point_in_figure(const Point &point) const noexcept override;

    void draw() const override;

    std::vector<Point> shape_coordinates(Point shift = Point(0, 0)) const noexcept override;

private:
    double radius_{0}; // radius of circle
};


/* RegularPolygon shape */

class RegularPolygon : public Shape {
public:
    RegularPolygon() = default;

    RegularPolygon(size_t n, double size, double rotation = 0) noexcept;

    bool is_point_in_figure(const Point &point) const noexcept override;

    void draw() const override;

    std::vector<Point> shape_coordinates(Point shift = Point(0, 0)) const noexcept override;

private:
    size_t n_{0}; // number of sides
    double size_{0}; // size of side
    std::vector<Point> data_; // shape points
};

/* Square shape */

class Square : public RegularPolygon {
public:
    Square() = default;

    Square(double width) noexcept;

private:
    static constexpr size_t angle_num = 4;
};


/* Rectangle shape */

class Rectangle : public Shape {
public:
    Rectangle() = default;

    Rectangle(double width, double height) noexcept;

    bool is_point_in_figure(const Point &point) const noexcept override;

    void draw() const override;

    std::vector<Point> shape_coordinates(Point shift = Point(0, 0)) const noexcept override;

private:
    double width_{0}; // rectangle width
    double height_{0}; // rectangle height
};