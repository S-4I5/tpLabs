#include "Diamond.h"

namespace iakov{

    void Diamond::setPoints(double x1, double y1, double x2, double y2) {
        if (point1_.x_ == center_.x_) {
            point1_.x_ = x1;
            point1_.y_ = y1;
            point2_.x_ = x2;
            point2_.y_ = y2;
        } else {
            point1_.x_ = x2;
            point1_.y_ = y2;
            point2_.x_ = x1;
            point2_.y_ = y1;
        }
    }

    Diamond::Diamond(double x1, double y1, double x2, double y2, double x3, double y3) {
        try {
            if ((x1 == x2 && y1 == y3) || (x1 == x3 && y1 == y2)) {
                center_.x_ = x1;
                center_.y_ = y1;
                setPoints(x2, y2, x3, y3);
            }
            if ((x2 == x3 && y2 == y1) || (x2 == x1 && y2 == y3)) {
                center_.x_ = x2;
                center_.y_ = y2;
                setPoints(x1, y1, x3, y3);
            }
            if ((x3 == x1 && y3 == y2) || (x3 == x2 && y3 == y1)) {
                center_.x_ = x3;
                center_.y_ = y3;
                setPoints(x2, y2, x1, y1);
            } else { throw IncorrectTriangle(); }
        } catch (std::exception &error) {
            std::cerr << std::endl << error.what() << std::endl;
            exit(1);
        }
    }

    const double Diamond::getArea() {
        return abs(point1_.x_ - center_.x_) * abs(point2_.y_ - center_.y_) * 2;
    }

    const rectangle_t Diamond::getFrameRect() {
        return rectangle_t{abs(point1_.x_ - center_.x_) * 2, abs(point2_.y_ - center_.y_) * 2,
    point_t{center_.x_, center_.y_}};
    }

    void Diamond::move(double x, double y) {
        center_.x_ += x;
        center_.y_ += y;
        point1_.x_ += x;
        point1_.y_ += y;
        point2_.x_ += x;
        point2_.y_ += y;
    }

    void Diamond::move(point_t newCenter) {
        double x = newCenter.x_ - center_.x_;
        double y = newCenter.y_ - center_.y_;
        move(x, y);
    }

    void Diamond::scale(double mult) {
        mult--;
        point1_.x_ += (point1_.x_ - center_.x_) * mult;
        point2_.y_ += (point2_.y_ - center_.y_) * mult;
    }

    void Diamond::print() {
        point_t point3{center_.x_ + (point1_.x_ - center_.x_) * -1, point1_.y_};
        point_t point4{point2_.x_, center_.y_ + (point2_.y_ - center_.y_) * -1,};
        std::cout << "DIAMOND: " << point1_.x_ << " " << point1_.y_ <<
        "; " << point2_.x_ << " " << point2_.y_ <<
        "; " << point3.x_ << " " << point3.y_ <<
        "; " << point4.x_ << " " << point4.y_ << ";\n";
    };

}