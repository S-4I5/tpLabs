#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include "data_struct.h"


int main(){

    std::vector<iakov::Data> data;
    std::ifstream in("D:\\PTcodes\\c++\\TP\\lab2\\input.txt");

    std::copy(std::istream_iterator<iakov::Data>(in),std::istream_iterator<iakov::Data>(),std::back_inserter(data));

    if(!in) std::cout << "no!";

    std::sort(std::begin(data), std::end(data));

    std::cout << "Data:\n";
    std::copy(std::begin(data),std::end(data),std::ostream_iterator< iakov::Data >(std::cout, "\n"));

    /*std::ifstream in("D:\\PTcodes\\c++\\TP\\lab2\\input2.txt");

    std::string sus = "cum"; char d = '0';

    //in.setstate(std::ios::failbit);

    std::getline(in, sus, '(');

    if(!sus.ends_with('(')) std::cout << 9;

    in >> d;

    std::cout << d << "1";

    std::cout << sus << "2";*/

    return 0;
}