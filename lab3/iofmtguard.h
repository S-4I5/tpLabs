//
// Created by Администратор on 18.05.2022.
//

#ifndef TP_IOFMTGUARD_H
#define TP_IOFMTGUARD_H


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

#endif //TP_IOFMTGUARD_H
