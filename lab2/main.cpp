#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include "data_struct.h"


int main(){

    std::vector<iakov::Data> data;
    std::ifstream in("D:\\PTcodes\\c++\\TP\\lab2\\input.txt");

    std::copy(std::istream_iterator<iakov::Data>(in),std::istream_iterator<iakov::Data>(),std::back_inserter(data));

    std::sort(std::begin(data), std::end(data));

    std::cout << "Data:\n";
    std::copy(std::begin(data),std::end(data),std::ostream_iterator< iakov::Data >(std::cout, "\n"));

    return 0;
}