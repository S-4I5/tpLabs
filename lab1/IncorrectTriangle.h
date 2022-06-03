#ifndef TP_INCORRECTTRIANGLE_H
#define TP_INCORRECTTRIANGLE_H

#include "iostream"

namespace iakov {

    class IncorrectTriangle : public std::exception {

    public:

        IncorrectTriangle() : reason_("Incorrect triangle for diamond!") {}

        [[nodiscard]] const char *what() const override { return reason_; }

    private:

        const char *reason_;
    };
}


#endif //TP_INCORRECTTRIANGLE_H
