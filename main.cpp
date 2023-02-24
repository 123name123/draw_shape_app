#include <memory>
#include "shapes.h"


int main() {
    std::vector<std::unique_ptr<Shape>> shapes;
    const std::string main_question = "Enter type of shape you want to add or see your shapes\nCircle: 1\n"
                                      "Regular Polygon: 2\nRectangle: 3\nDraw shapes: 4\nExit: 5";
    const std::string circle_question = "Enter radius of circle:\n";
    const std::string polygon_question = "Enter number of angles and size of side:\n";
    const std::string rectangle_question = "Enter the sides of the rectangle:\n";
    bool is_running = true;
    while (is_running) {
        std::cout << main_question;
        size_t type;
        std::cin >> type;
        if (type > 4 || type < 1) {
            throw std::runtime_error("Wrong type");
        }
        if (type == 1) {
            std::cout << circle_question;
            double radius;
            std::cin >> radius;
            shapes.push_back(std::make_unique<Circle>(radius));
        } else if (type == 2) {
            std::cout << polygon_question;
            size_t n;
            double size;
            std::cin >> n >> size;
            shapes.push_back(std::make_unique<RegularPolygon>(n, size));
        } else if (type == 3) {
            std::cout << rectangle_question;
            double width, height;
            std::cin >> width >> height;
            shapes.push_back(std::make_unique<Rectangle>(width, height));
        } else if (type == 4) {
            for (const auto &shape: shapes) {
                shape->draw();
            }
            shapes.clear();
        } else {
            is_running = false;
        }
    }
    std::cout << "Good bye!!";
}
