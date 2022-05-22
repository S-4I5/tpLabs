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

    std::sort(std::begin(data), std::end(data));

    std::cout << "Data:\n";
    std::copy(std::begin(data),std::end(data),std::ostream_iterator< iakov::Data >(std::cout, "\n"));

    return 0;
}