#ifndef TP_DATA_STRUCT_H
#define TP_DATA_STRUCT_H

#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>

namespace iakov{

    struct Data{
        double key1 = 0.0;
        char key2 = '0';
        std::string key3 = "Error";
    };

    struct DelimiterIO {
        char exp;
    };

    struct LabelIO {
        int &key;
    };

    struct CharIO {
        char &exp;
    };

    struct DoubleIO {
        double &ref;
    };

    struct StringIO {
        std::string &ref;
    };

    struct IntIO{
        int &ref;
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

    std::istream &operator>>(std::istream &in, CharIO &&dest){

        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }

        in >> DelimiterIO{'\''};
        in >> dest.exp;
        in >> DelimiterIO{'\''};

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
        //in >> StringIO{data};

        in >> data;

        if(data.find("key") != -1){
            dest.key = data[3] - 48;
        } else if (in){
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream &operator>>(std::istream &in, DoubleIO &&dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }

        in >> dest.ref;

        return in;
    }

    std::istream &operator>>(std::istream &in, Data &dest){

        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }

        bool succ = false;

        while(!succ) {

            if (!in) {
                in.clear();
            }

            std::string buffer = "";
            std::getline(in, buffer, '(');

            char c = '0';

            in >> c;

            while(c == '(' && !in.eof()){
                in >> c;
            }

            if(c != ':'){
                continue;
            }

            Data input{};

            bool args[3] = {false, false, false};

            int curKey = 0;

            for (int i = 0; i < 3; ++i) {
                in >> LabelIO{curKey};
                if (!args[curKey - 1]) {
                    args[curKey - 1] = true;
                    switch (curKey) {
                        case 1:
                            in >> DoubleIO{input.key1};
                            break;
                        case 2:
                            in >> CharIO{input.key2};
                            break;
                        case 3:
                            in >> StringIO{input.key3};
                            break;
                        default:
                            break;
                    }
                } else {
                    if (in) in.setstate(std::ios::failbit);
                }
                in >> DelimiterIO{':'};
            }

            in >> DelimiterIO{')'};

            if(in.eof()){
                in.setstate(std::ios::eofbit);
                return in;
            }

            if (in) {
                dest = input;
                succ = true;
            }
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
        out << std::scientific << "(:\"key1\" " << src.key1 << ":\"key2\" '" << src.key2 << "':\"key3\" " << src.key3 << ":)";
        return out;
    }

    bool operator<(Data& first, Data &second){
        if(first.key1 < second.key1) return true;
        else if(first.key1 > second.key1) return false;
        if(first.key2 < second.key2) return true;
        else if(first.key2 > second.key2) return false;
        if(first.key3 < second.key3) return true;
        else if(first.key3 > second.key3) return false;
        return false;
    }
}

#endif //TP_DATA_STRUCT_H
