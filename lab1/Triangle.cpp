#include "iostream"
#include "Triangle.h"

namespace iakov{

    Triangle::Triangle(double x1, double y1, double x2, double y2, double x3, double y3) {

        point1_.x_ = x1;
        point1_.y_ = y1;
        point2_.x_ = x2;
        point2_.y_ = y2;
        point3_.x_ = x3;
        point3_.y_ = y3;

    };

    const double Triangle::getArea()  {
        return abs((point2_.x_ - point1_.x_) * (point3_.y_ - point1_.y_) -
        (point2_.y_ - point1_.y_) * (point3_.x_ - point1_.x_)) / 2;
    }

    const rectangle_t Triangle::getFrameRect()  {
        return rectangle_t{std::max(point1_.x_, std::max(point2_.x_, point3_.x_)) -
        std::min(point1_.x_, std::min(point2_.x_, point3_.x_)),
        std::max(point1_.y_, std::max(point2_.y_, point3_.y_)) -
        std::min(point1_.y_, std::min(point2_.y_, point3_.y_)),
        {(point3_.x_ + point2_.x_ + point1_.x_) / 3, (point3_.y_ + point2_.y_ + point1_.y_) / 3}
        };
    }

    void Triangle::move(double x, double y)  {
        point1_.x_ += x;
        point1_.y_ += y;
        point2_.x_ += x;
        point2_.y_ += y;
        point3_.x_ += x;
        point3_.y_ += y;
    }

    void Triangle::move(point_t newCenter)  {
        double x = newCenter.x_ - (point3_.x_ + point2_.x_ + point1_.x_) / 3;
        double y = newCenter.y_ - (point3_.y_ + point2_.y_ + point1_.y_) / 3;
        move(x, y);
    }

    void Triangle::scale(double mult)  {
        double x = (point3_.x_ + point2_.x_ + point1_.x_) / 3;
        double y = (point3_.y_ + point2_.y_ + point1_.y_) / 3;
        mult = (mult - 1);
        point1_.x_ += (point1_.x_ - x) * mult;
        point1_.y_ += (point1_.y_ - y) * mult;
        point2_.x_ += (point2_.x_ - x) * mult;
        point2_.y_ += (point2_.y_ - y) * mult;
        point3_.x_ += (point3_.x_ - x) * mult;
        point3_.y_ += (point3_.y_ - y) * mult;
    }

    void Triangle::print()  {
        std::cout << "TRIANGLE: " << point1_.x_ << " " << point1_.y_ << "; "
        << point2_.x_ << " " << point2_.y_ << "; "
        << point3_.x_ << " " << point3_.y_ << ";\n";
    }

}
