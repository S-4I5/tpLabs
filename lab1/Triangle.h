#ifndef TP_TRIANGLE_H
#define TP_TRIANGLE_H

#include "Shape.h"

namespace iakov {

    class Triangle : public Shape {
    private:

        point_t point1_{};
        point_t point2_{};
        point_t point3_{};

    public:

        Triangle(double x1, double y1, double x2, double y2, double x3, double y3);

        const double getArea() override;

        const rectangle_t getFrameRect() override;

        void move(double x, double y) override;

        void move(point_t newCenter) override;

        void scale(double mult) override;

        void print() override;

        ~Triangle() override = default;
    };
}

#endif //TP_TRIANGLE_H
