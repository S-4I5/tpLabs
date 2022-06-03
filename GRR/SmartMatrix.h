#ifndef ALGORITHMS_2021_SMARTMATRIX_H
#define ALGORITHMS_2021_SMARTMATRIX_H

#include <vector>

namespace iakov {

    class SmartMatrix {
    private:

        std::vector<std::vector<int> *> *matrix_;

        int size_;

    public:

        SmartMatrix();

        int &operator()(int pos1, int pos2);

        std::vector<int> *operator()(int pos1);

        void add();

        void cut(int index);

        ~SmartMatrix();
    };
}


#endif //ALGORITHMS_2021_SMARTMATRIX_H
