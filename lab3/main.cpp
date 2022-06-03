#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <fstream>
#include "polygon_struct.h"
#include "command_struct2.h"

int cock(){
    static int a = 0;
    return ++a;
}

int main() {

    /*std::vector<iakov::Polygon> data;
    std::ifstream in("D:\\PTcodes\\c++\\TP\\lab3\\input.txt");

    std::copy(std::istream_iterator<iakov::Polygon>(in),std::istream_iterator<iakov::Polygon>(),std::back_inserter(data));

    std::cout << "Data:\n";
    std::copy(std::begin(data),std::end(data),std::ostream_iterator< iakov::Polygon >(std::cout, "\n"));

    std::ifstream userIn("D:\\PTcodes\\c++\\TP\\lab3\\userInput.txt");

    //while(userIn >> iakov::CommandIO{data});

    while(userIn >>  iakov::CommandIO{data});*/

    std::cout << cock() << cock() << cock();

}
