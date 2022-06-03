
#include "iostream"
#include "Rectangle.h"

namespace iakov{

     Rectangle::Rectangle(double left, double down, double right, double top) {
        point1_.x_ = std::min(left, right);
        point1_.y_ = std::min(down, top);
        point2_.x_ = std::max(left, right);
        point2_.y_ = std::max(down, top);
    }

    const double Rectangle::getArea() {
        return (std::max(point1_.x_, point2_.x_) - std::min(point1_.x_, point2_.x_)) *
        (std::max(point1_.y_, point2_.y_) - std::min(point1_.y_, point2_.y_));
    }

    const rectangle_t Rectangle::getFrameRect() {
        return rectangle_t{point2_.x_ - point1_.x_,
        point2_.y_ - point1_.y_,
        point_t{(point1_.x_ + point2_.x_) / 2, (point1_.y_ + point2_.y_) / 2}};
    };

    void Rectangle::move(double x, double y) {
        point1_.x_ += x;
        point1_.y_ += y;
        point2_.x_ += x;
        point2_.y_ += y;
    }

    void Rectangle::move(point_t newCenter) {
    double x = newCenter.x_ - ((point2_.x_ + point1_.x_) / 2);
    double y = newCenter.y_ - ((point2_.y_ + point1_.y_) / 2);
    move(x, y);
    }

    void Rectangle::scale(double mult) {
        double wight = point2_.x_ - point1_.x_;
        double height = point2_.y_ - point1_.y_;
        mult--;
        point1_.x_ = point1_.x_ - wight * mult / 2;
        point1_.y_ = point1_.y_ - height * mult / 2;
        point2_.x_ = point2_.x_ + wight * mult / 2;
        point2_.y_ = point2_.y_ + height * mult / 2;
    }

    void Rectangle::print() {
        std::cout << "RECTANGLE: " << point1_.x_ << " " << point1_.y_ << "; " << point2_.x_ << " " << point2_.y_
        << ";\n";
    }
}