#ifndef TP_SHAPE_H
#define TP_SHAPE_H

#include "point_struct.h"
#include "rectangle_struct.h"

namespace iakov {

    class Shape {

    public:

        Shape() = default;

        virtual const double getArea() = 0;

        virtual const rectangle_t getFrameRect() = 0;

        virtual void move(double x, double y) = 0;

        virtual void move(point_t newCenter) = 0;

        virtual void scale(double mult) = 0;

        virtual void print() = 0;

        virtual ~Shape() = default;
    };
}

#endif //TP_SHAPE_H
