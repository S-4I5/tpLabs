#ifndef TP_DATA_STRUCT_H
#define TP_DATA_STRUCT_H

#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <complex>

namespace iakov{

    struct Data{
        unsigned long long key1;
        std::complex<double> key2;
        std::string key3 = "Error";
    };

    struct DelimiterIO {
        char exp;
    };

    struct LabelIO {
        int &key;
    };

    struct ULLIO {
        unsigned long long &ref;
    };

    struct ComplexIO{
        std::complex<double> &ref;
    };

    struct StringIO {
        std::string &ref;
    };

    class iofmtguard {
    public:

        explicit iofmtguard(std::basic_ios< char > &s);

        ~iofmtguard();

    private:

        std::basic_ios< char > &s_;

        char fill_;

        std::streamsize precision_;

        std::basic_ios< char >::fmtflags fmt_;
    };

    iofmtguard::iofmtguard(std::basic_ios< char > &s) :
            s_(s),
            fill_(s.fill()),
            precision_(s.precision()),
            fmt_(s.flags())
    {}

    iofmtguard::~iofmtguard()
    {
        s_.fill(fill_);
        s_.precision(precision_);
        s_.flags(fmt_);
    }

    std::istream &operator>>(std::istream &in, DelimiterIO &&dest){

        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }

        char c = '0';
        in >> c;

        if(in && c != dest.exp) in.setstate(std::ios::failbit);

        return in;
    }

    std::istream &operator>>(std::istream &in, StringIO &&dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
    }

    std::istream &operator>>(std::istream &in, LabelIO &&dest) {

        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }

        std::string data = "";

        in >> data;

        if(data.find("key") != -1 && data.size() == 4){
            dest.key = data[3] - 48;
        } else if (in){
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream &operator>>(std::istream &in, ComplexIO &&dest){

        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }

        double first, second;

        in >> DelimiterIO{'#'} >> DelimiterIO{'c'} >> DelimiterIO{'('} >> first >> second >> DelimiterIO{')'};

        dest.ref = {first, second};

        return in;
    }

    std::istream &operator>>(std::istream &in, ULLIO &&dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }

        std::string ull = "";
        char f = 'g';

        in >> f;

        while(f >= '0' && f <= '9' && !in.eof()){
            ull+=f;
            in >> f;
        }

        if(f == 'U' || f == 'u')
            in >> DelimiterIO{static_cast<char>(f-9)} >> DelimiterIO{static_cast<char>(f-9)};
        else{
            in.setstate(std::ios::failbit);
            return in;
        }

        if(!in) return in;

        try{
            dest.ref = std::stoull(ull.c_str());
        }catch (std::exception &e){
            in.setstate(std::ios::failbit);
        }

        return in;
    }

    std::istream &operator>>(std::istream &in, Data &dest){

        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }

        Data input{};

        bool args[3] = {false, false, false};

        int curKey = 0;

        in >> DelimiterIO{'('} >> DelimiterIO{':'};

        for (int i = 0; i < 3; ++i) {
            in >> LabelIO{curKey};
            if (!args[curKey - 1]) {
                args[curKey - 1] = true;
                switch (curKey) {
                    case 1:
                        in >> ULLIO{input.key1};
                        break;
                        case 2:
                            in >> ComplexIO{input.key2};
                            break;
                        case 3:
                            in >> StringIO{input.key3};
                            break;
                        default:
                            break;
                }
            } else {
                in.setstate(std::ios::failbit);
            }
            in >> DelimiterIO{':'};
        }

        in >> DelimiterIO{')'};

        if (in) {
            dest = input;
        }
        return in;
    }

    std::ostream &operator<<(std::ostream &out, const Data &src ){
        std::ostream::sentry sentry(out);
        if (!sentry)
        {
            return out;
        }
        iofmtguard fmtguard(out);
        out << std::setprecision(2) << "(:\"key1\" " << src.key1 << "ull:\"key2\" #c" << src.key2 << R"(:"key3" ")" << src.key3 << "\":)";
        return out;
    }

    bool operator<(Data& first, Data &second){
        if(first.key1 < second.key1) return true;
        else if(first.key1 > second.key1) return false;
        if(abs(first.key2 - second.key2) > 0) return true;
        else if(abs(first.key2 - second.key2) < 0) return false;
        if(first.key3 < second.key3) return true;
        else if(first.key3 > second.key3) return false;
        return false;
    }
}

#endif //TP_DATA_STRUCT_H
