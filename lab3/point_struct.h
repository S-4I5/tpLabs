//
// Created by Администратор on 10.05.2022.
//

#ifndef TP_POINT_STRUCT_H
#define TP_POINT_STRUCT_H

#include <iosfwd>

namespace iakov {

    struct Point {
        int x_, y_;
    };

    struct DelimiterIO {
        char exp;
    };

    struct IntIo {
        int &ref;
    };

    std::istream &operator>>(std::istream &in, DelimiterIO &&dest) {

        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }

        char c = '0';
        in >> c;

        if (in && c != dest.exp) in.setstate(std::ios::failbit);

        return in;
    }

    std::istream &operator>>(std::istream &in, IntIo &&dest) {
        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }

        in >> dest.ref;

        return in;
    }

    std::istream &operator>>(std::istream &in, Point &dest) {

        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }

        Point input{};

        in >> DelimiterIO{'('};
        in >> IntIo{input.x_};
        in >> DelimiterIO{';'};
        in >> IntIo{input.y_};
        in >> DelimiterIO{')'};

        if (in)
            dest = input;

        return in;
    }

    std::ostream &operator<<(std::ostream &out, const Point & dest) {

        std::ostream::sentry sentry(out);
        if (!sentry) {
            return out;
        }

        std::cout << "(" << dest.x_ << ";" << dest.y_ << ")";

        return out;
    }

}

#endif //TP_POINT_STRUCT_H
