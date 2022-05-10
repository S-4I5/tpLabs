#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <fstream>
#include "polygon_struct.h"
#include "command_struct.h"


int main() {

    std::vector<iakov::Polygon> data;
    std::ifstream in("D:\\PTcodes\\c++\\TP\\lab3\\input.txt");

    std::copy(std::istream_iterator<iakov::Polygon>(in),std::istream_iterator<iakov::Polygon>(),std::back_inserter(data));

    std::cout << "Data:\n";
    std::copy(std::begin(data),std::end(data),std::ostream_iterator< iakov::Polygon >(std::cout, "\n"));

    for(;;){
        std::cin >> iakov::CommandIO{data};
    }

}
