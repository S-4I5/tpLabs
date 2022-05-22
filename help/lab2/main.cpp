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

    if(in) std::cout << "no!";

    std::sort(std::begin(data), std::end(data));

    std::cout << "Data:\n";
    std::copy(std::begin(data),std::end(data),std::ostream_iterator< iakov::Data >(std::cout, "\n"));

    /*std::ifstream in("D:\\PTcodes\\c++\\TP\\lab2\\input2.txt");

    std::vector<int> data;

    std::copy(std::istream_iterator<int>(in),std::istream_iterator<int>(),std::back_inserter(data));

    if(!in) std::cout << "no!";

    /*std::string sus = "cum"; char d = '0';

    //in.setstate(std::ios::failbit);

    std::getline(in, sus, '(');

    if(!sus.ends_with('(')) std::cout << 9;

    in >> d;

    std::cout << "1" <<  d << "1" << "\n";

    std::cout << "2" << sus << "2" << "\n";*/

    //std::complex<double> z;

    /*unsigned long long z = 0;

    std::ifstream in("D:\\PTcodes\\c++\\TP\\help\\lab2\\input.txt");

    in >> iakov::ULLIO{z};

    std::cout << z;

    std::complex<double> complex;

    complex = {1.0, 2.0};

    std::cout << complex;*/

    //std::cout << int('u') << " " << int('l') << " " << int('U') << " " << int('L');

    return 0;
}