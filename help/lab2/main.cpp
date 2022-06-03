#include <iostream>
#include <iterator>
#include <algorithm>
#include "data_struct.h"
#include <complex>

int main(){

    std::vector<iakov::Data> data;
    std::ifstream in("D:\\PTcodes\\c++\\TP\\help\\lab2\\input.txt");

    while(!in.eof())
    {
        std::copy(std::istream_iterator<iakov::Data>(in), std::istream_iterator<iakov::Data>(),
                  std::back_inserter(data));
        if(!in && !in.eof()){
            in.clear();
        }
    }

    std::sort(std::begin(data), std::end(data), [](const iakov::Data first,const iakov::Data second ){
        if(first.key1 < second.key1) return true;
        else if(first.key1 > second.key1) return false;
        if(abs(first.key2 - second.key2) > 0) return true;
        else if(abs(first.key2 - second.key2) < 0) return false;
        if(first.key3 < second.key3) return true;
        else if(first.key3 > second.key3) return false;
        return false;
    });

    std::cout << "Data:\n";
    std::copy(std::begin(data),std::end(data),std::ostream_iterator< iakov::Data >(std::cout, "\n"));

    return 0;
}