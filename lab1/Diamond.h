#ifndef TP_DIAMOND_H
#define TP_DIAMOND_H

#include "IncorrectTriangle.h"
#include "Shape.h"
#include "iostream"

namespace iakov {

    class Diamond : public Shape {
    private:

        point_t point1_{};
        point_t point2_{};
        point_t center_{};

        void setPoints(double x1, double y1, double x2, double y2);

    public:

        Diamond(double x1, double y1, double x2, double y2, double x3, double y3);

        const double getArea() override;

        const rectangle_t getFrameRect() override;

        void move(double x, double y) override;

        void move(point_t newCenter) override;

        void scale(double mult) override;

        void print() override;

        ~Diamond() override = default;
    };
}

#endif //TP_DIAMOND_H
