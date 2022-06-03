#ifndef TP_RECTANGLE_H
#define TP_RECTANGLE_H

#include "Shape.h"

namespace iakov {

    class Rectangle : public Shape {
    private:

        point_t point1_{};
        point_t point2_{};

    public:

        explicit Rectangle(double left, double down, double right, double top);

        const double getArea() override;

        const rectangle_t getFrameRect() override ;

        void move(double x, double y) override ;

        void move(point_t newCenter) override ;

        void scale(double mult) override ;

        void print() override ;

        ~Rectangle() override = default;
    };
}

#endif //TP_RECTANGLE_H
