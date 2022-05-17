//
// Created by Администратор on 10.05.2022.
//

#ifndef TP_POLYGON_STRUCT_H
#define TP_POLYGON_STRUCT_H

#include <vector>
#include "point_struct.h"
#include <iostream>
#include <string>
#include <numeric>

namespace iakov {

    struct Polygon {

        std::vector<Point> points;

    };

    std::istream &operator>>(std::istream &in, Polygon &dest) {

        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }

            /*if(in.eof()){
                in.setstate(std::ios::failbit);
                return in;
            }*/

            Polygon input{};

            int number = 0;

            in >> number;

            if(number < 1){
                in.setstate(std::ios::failbit);
                return in;
            }

            for (int i = 0; i < number; ++i) {

                Point point{};
                in >> point;

                input.points.push_back(point);
            }

            if (in) {
                dest = input;
            }

        return in;
    }

    std::ostream &operator<<(std::ostream &out, const Polygon &dest) {

        std::ostream::sentry sentry(out);
        if (!sentry) {
            return out;
        }

        if(dest.points.empty()){
            out << "Empty!";
            return out;
        }

        out << dest.points.size();

        for (auto point : dest.points) {
            out << " " << point;
        }

        return out;
    }

    double getArea(const Polygon &polygon){

        if(polygon.points.size() < 3) return 0.0;

        /*double answer = 0;

        for (int i = 0; i < polygon.points.size(); ++i) {
            answer += polygon.points[i].x_ * polygon.points[(i+1)%polygon.points.size()].y_;
            //std::cout << polygon.points[i].x_ << " * " << polygon.points[(i+1)%polygon.points.size()].y_ << "\n";
            answer -= polygon.points[i].y_ * polygon.points[(i+1)%polygon.points.size()].x_;
            //std::cout << polygon.points[i].y_ << " * " << polygon.points[(i+1)%polygon.points.size()].x_ << "\n";
        }

        return abs(answer)/2;*/

        int i  = 0;

        double a = std::inner_product(polygon.points.cbegin(), polygon.points.cend(), polygon.points.begin()+1, 0, , 1);

        return abs(std::accumulate(polygon.points.cbegin(), polygon.points.cend(), 0, [&i, &polygon](double accum,const Point& point){
            i = (i++)%polygon.points.size();
            return accum + point.x_ * polygon.points[i].y_ -
                    point.y_ * polygon.points[i].x_;
        }))/2;

    }
}

#endif //TP_POLYGON_STRUCT_H
