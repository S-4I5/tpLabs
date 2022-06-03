
#include "SmartMatrix.h"

namespace iakov{

    SmartMatrix::SmartMatrix(){
        matrix_ = new std::vector<std::vector<int>*>;
        matrix_->push_back(new std::vector<int>);
        matrix_->back()->push_back(0);
        size_ = 1;
    }

    int& SmartMatrix::operator()(int pos1, int pos2){
        return matrix_->at(pos1)->at(pos2);
    };

    std::vector<int>* SmartMatrix::operator()(int pos1){
        return matrix_->at(pos1);
    };

    void SmartMatrix::add(){
        for (int i = 0; i < matrix_->size(); ++i) {
            matrix_->at(i)->push_back(0);
        }
        ++size_;
        matrix_->push_back(new std::vector<int>());
        for (int i = 0; i < size_; ++i) {
            matrix_->back()->push_back(0);
        }
    };

    void SmartMatrix::cut(int index){
        for (int i = 0; i < matrix_->size(); ++i) {
            matrix_->at(i)->erase(matrix_->at(i)->begin() + index - 1);
        }
        matrix_->erase(matrix_->begin() + index - 1);
        --size_;
    }

    SmartMatrix::~SmartMatrix(){
        for (int i = 0; i < size_; ++i) {
            delete [] matrix_->at(i);
        }
        delete [] matrix_;
    }
}
