//
// Created by Администратор on 10.05.2022.
//

#ifndef TP_POLYGON_STRUCT_H
#define TP_POLYGON_STRUCT_H

#include <vector>
#include "point_struct.h"
#include <iostream>
#include <string>

namespace iakov {

    struct Polygon {

        std::vector<Point> points;

    };

    std::istream &operator>>(std::istream &in, Polygon &dest) {

        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }

        bool succ = false;

        while(!succ) {

            if(!in){
                in.clear();
                std::string buf;
                std::getline(in, buf);
            }

            if(in.eof()){
                in.setstate(std::ios::failbit);
                return in;
            }

            Polygon input{};

            int number = 0;

            in >> number;

            for (int i = 0; i < number; ++i) {

                Point point{};
                in >> point;

                input.points.push_back(point);
            }

            if (in) {
                dest = input;
                succ = true;
            }
        }

        return in;
    }

    std::ostream &operator<<(std::ostream &out, const Polygon &dest) {

        std::ostream::sentry sentry(out);
        if (!sentry) {
            return out;
        }

        out << dest.points.size();

        for (auto point : dest.points) {
            out << " " << point;
        }

        return out;
    }

    double getArea(const Polygon &polygon){
        double answer = 0;

        if(polygon.points.size() < 3) return answer;

        for (int i = 0; i < polygon.points.size(); ++i) {
            answer += polygon.points[i].x_ * polygon.points[(i+1)%polygon.points.size()].y_;
            //std::cout << polygon.points[i].x_ << " * " << polygon.points[(i+1)%polygon.points.size()].y_ << "\n";
            answer -= polygon.points[i].y_ * polygon.points[(i+1)%polygon.points.size()].x_;
            //std::cout << polygon.points[i].y_ << " * " << polygon.points[(i+1)%polygon.points.size()].x_ << "\n";
        }

        return abs(answer)/2;
    }
}

#endif //TP_POLYGON_STRUCT_H
