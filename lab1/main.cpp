#include "iostream"
#include "Shape.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Diamond.h"

void testShape(const std::shared_ptr<iakov::Shape>& shape);

int main(){

    std::shared_ptr<iakov::Rectangle> rectangle(new iakov::Rectangle(-1,-2,3,2));

    testShape(rectangle);

    std::cout << "\n";

    std::shared_ptr<iakov::Triangle> triangle(new iakov::Triangle(1,0,4,1,3,5));

    testShape(triangle);

    std::cout << "\n";

    std::shared_ptr<iakov::Diamond> diamond(new iakov::Diamond(1,1,2,2,2,1));

    testShape(diamond);
    return 0;
}

void testShape(const std::shared_ptr<iakov::Shape>& shape){
    shape->print();
    std::cout << "Area: " << shape->getArea() << "\n";
    std::cout << "Frame area: center{ x = " << shape->getFrameRect().center.x_ << ", y = " <<  shape->getFrameRect().center.y_ << " }, height = " << shape->getFrameRect().height_ << ", wight = " << shape->getFrameRect().wight_ << "; \n";
    shape->move(1,1);
    std::cout << "Move x: 1, y: 1 : \n";
    std::cout << "Frame area: center{ x = " << shape->getFrameRect().center.x_ << ", y = " <<  shape->getFrameRect().center.y_ << " }, height = " << shape->getFrameRect().height_ << ", wight = " << shape->getFrameRect().wight_ << "; \n";
    shape->print();
    std::cout << "Move to point 0,0 : \n";
    shape->move({0, 0});
    std::cout << "Frame area: center{ x = " << shape->getFrameRect().center.x_ << ", y = " <<  shape->getFrameRect().center.y_ << " }, height = " << shape->getFrameRect().height_ << ", wight = " << shape->getFrameRect().wight_ << "; \n";
    shape->print();
    std::cout << "Scale 2 : \n";
    shape->scale(2);
    std::cout << "Frame area: center{ x = " << shape->getFrameRect().center.x_ << ", y = " <<  shape->getFrameRect().center.y_ << " }, height = " << shape->getFrameRect().height_ << ", wight = " << shape->getFrameRect().wight_ << "; \n";
    shape->print();
    std::cout << "Scale 0.5 : \n";
    shape->scale(0.5);
    std::cout << "Frame area: center{ x = " << shape->getFrameRect().center.x_ << ", y = " <<  shape->getFrameRect().center.y_ << " }, height = " << shape->getFrameRect().height_ << ", wight = " << shape->getFrameRect().wight_ << "; \n";
    shape->print();
}
