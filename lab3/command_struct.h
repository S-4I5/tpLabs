#ifndef TP_COMMAND_STRUCT_H
#define TP_COMMAND_STRUCT_H

#include <vector>
#include "iostream"
#include <algorithm>
#include <functional>
#include <numeric>

namespace iakov{

    struct CommandIO{
        std::vector<Polygon> &polygons;
    };

    struct CommandNameIO{
        int &code;
    };

    struct ArgumentIO{
        int &code;
        const std::vector<std::string> &argumentNames;
    };

    struct AreaIO{
        std::vector<Polygon> &polygons;
    };

    struct MaxIO{
        std::vector<Polygon> &polygons;
    };

    struct MinIO{
        std::vector<Polygon> &polygons;
    };

    struct CountIO{
        std::vector<Polygon> &polygons;
    };

    struct InFrameIO{
        std::vector<Polygon> &polygons;
    };

    struct EchoIO{
        std::vector<Polygon> &polygons;
    };

    std::istream &operator>>(std::istream &in, ArgumentIO &&dest) {

        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }

        dest.code = 0;

        std::string currentArgument;

        in >> currentArgument;

        for (int i = 0; i < dest.argumentNames.size(); ++i) {
            if(dest.argumentNames[i] == currentArgument) dest.code = (i+1)*-1;
        }

        if(dest.code == 0) {
            try{
                dest.code = std::stoi(currentArgument);
            }catch (std::exception &e){};
        }
        return in;
    }

    std::istream &operator>>(std::istream &in, CommandNameIO &&dest) {

        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }

        std::string currentCommand;

        in >> currentCommand;

        std::cout << currentCommand;

        std::string commandNames [] = {"AREA", "MAX", "MIN", "COUNT", "ECHO","INFRAME"};

        for (int i = 0; i < 6; ++i) {
            if(currentCommand == commandNames[i]) dest.code = i+1;
        }

        return in;
    }

    std::istream &operator>>(std::istream &in, AreaIO &&dest){

        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }

        std::vector<std::string> argumentNames = {"EVEN", "ODD", "MEAN"};
        int argumentCode = 0;
        in >> ArgumentIO{argumentCode, argumentNames};


        if(argumentCode == 0){
            in.setstate(std::ios::failbit);
            return in;
        }

        double answer = 0;

        switch (argumentCode) {
            case -1:
                answer = std::accumulate(dest.polygons.cbegin(), dest.polygons.cend(), 0.0,[](double ans, const Polygon &polygon)
                {
                    if(polygon.points.size()%2 == 0)
                        return ans + getArea(polygon);
                    else
                        return ans;
                });
                break;
            case -2:
                answer = std::accumulate(dest.polygons.cbegin(), dest.polygons.cend(), 0.0,[](double ans, const Polygon &polygon)
                {
                    if(polygon.points.size()%2 != 0)
                        return ans + getArea(polygon);
                    else
                        return ans;
                });
                break;
            case -3:
                answer = std::accumulate(dest.polygons.cbegin(), dest.polygons.cend(), 0.0,[](double ans, const Polygon &polygon)
                {
                    return ans + getArea(polygon);
                });
                answer /= dest.polygons.size();
                break;
            default:
                answer = std::accumulate(dest.polygons.cbegin(), dest.polygons.cend(), 0.0,[&argumentCode](double ans, const Polygon &polygon)
                {
                    if(polygon.points.size() == argumentCode)
                        return ans + getArea(polygon);
                    else
                        return ans;
                });
                break;
        }

        std::cout << "ANSWER " << answer << "\n";

        return in;
    }

    std::istream &operator>>(std::istream &in, MaxIO &&dest){

        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }

        std::vector<std::string> argumentNames = {"AREA", "VERTEXES"};
        int argumentCode = 0;
        in >> ArgumentIO{argumentCode, argumentNames};

        if(argumentCode == 0){
            in.setstate(std::ios::failbit);
            return in;
        }

        double answer = 0;

        if(argumentCode == -1){
            answer = getArea(*std::max_element(dest.polygons.cbegin(), dest.polygons.cend(), [](const Polygon &f,const Polygon &s){
                if(getArea(f) < getArea(s)) return true;
                return false;
            }));
        }else if(argumentCode == -2){
            answer = (*std::max_element(dest.polygons.cbegin(), dest.polygons.cend(), [](const Polygon &f,const Polygon &s){
                if(f.points.size() < s.points.size()) return true;
                return false;
            })).points.size();
        }

        std::cout << "ANSWER " << answer << "\n";

        return in;
    };

    std::istream &operator>>(std::istream &in, MinIO &&dest){

        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }


        std::vector<std::string> argumentNames = {"AREA", "VERTEXES"};
        int argumentCode = 0;
        in >> ArgumentIO{argumentCode, argumentNames};

        if(argumentCode == 0){
            in.setstate(std::ios::failbit);
            return in;
        }

        double answer = 0;

        if(argumentCode == -1){
            answer = getArea(*std::min_element(dest.polygons.cbegin(), dest.polygons.cend(), [](const Polygon &f,const Polygon &s){
                if(getArea(f) < getArea(s)) return true;
                return false;
            }));
        }else if(argumentCode == -2){
            answer = (*std::min_element(dest.polygons.cbegin(), dest.polygons.cend(), [](const Polygon &f,const Polygon &s){
                if(f.points.size() < s.points.size()) return true;
                return false;
            })).points.size();
        }

        std::cout << answer << "\n";

        return in;
    };

    std::istream &operator>>(std::istream &in, CountIO &&dest){

        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }

        std::vector<std::string> argumentNames = {"EVEN", "ODD"};
        int argumentCode = 0;
        in >> ArgumentIO{argumentCode, argumentNames};

        if(argumentCode == 0){
            in.setstate(std::ios::failbit);
            return in;
        }

        int answer = 0;

        switch (argumentCode) {
            case -1:
                answer = std::count_if(dest.polygons.cbegin(), dest.polygons.cend(),[]( const Polygon &polygon)
                {
                    return polygon.points.size()%2 == 0;
                });
                break;
            case -2:
                answer = std::count_if(dest.polygons.cbegin(), dest.polygons.cend(), []( const Polygon &polygon)
                {
                    return polygon.points.size()%2 != 0;
                });
                break;
            default:
                answer = std::count_if(dest.polygons.cbegin(), dest.polygons.cend(),[&argumentCode](const Polygon &polygon)
                {
                    return polygon.points.size() == argumentCode;
                });
                break;
        }

        std::cout << "ANSWER " << answer << "\n";

        return in;
    };

    std::istream &operator>>(std::istream &in, InFrameIO &&dest){
        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }

        Polygon example{};
        in >> example;

        if(!in) return in;

        auto compX = [](const Point &f,const Point &s){
            return (f.x_ < s.x_);};
        auto compY = [](const Point &f,const Point &s){
            return (f.y_ < s.y_);};

        auto getLeftDown = [&compX, &compY](const Polygon &current){ ;
            {
                return Point{(*std::min_element(current.points.cbegin(), current.points.cend(), compX)).x_,
                        (*std::min_element(current.points.cbegin(), current.points.cend(), compY)).y_};
            };
        };
        auto getRightTop = [&compX, &compY](const Polygon &current){ ;
            {
                return Point{(*std::max_element(current.points.cbegin(), current.points.cend(),compX)).x_,
                                     (*std::max_element(current.points.cbegin(), current.points.cend(), compY)).y_};
            };
        };

        Point curLeftDown = getLeftDown(example);
        Point curRightTop = getRightTop(example);

        int left = getLeftDown(*std::min_element(dest.polygons.cbegin(), dest.polygons.cend(), [&getLeftDown](const Polygon &f,const Polygon &s){
            return getLeftDown(f).x_ < getLeftDown(s).x_;
        })).x_;

        int down = getLeftDown(*std::min_element(dest.polygons.cbegin(), dest.polygons.cend(), [&getLeftDown](const Polygon &f,const Polygon &s){
            return getLeftDown(f).y_ < getLeftDown(s).y_;
        })).y_;

        int right = getRightTop(*std::max_element(dest.polygons.cbegin(), dest.polygons.cend(), [&getRightTop](const Polygon &f,const Polygon &s){
            return getRightTop(f).x_ < getRightTop(s).x_;
        })).x_;

        int top = getRightTop(*std::max_element(dest.polygons.cbegin(), dest.polygons.cend(), [&getRightTop](const Polygon &f,const Polygon &s){
            return getRightTop(f).y_ < getRightTop(s).y_;
        })).y_;

        bool answer = left <= curLeftDown.x_ && down <= curLeftDown.y_
                             &&right >= curRightTop.x_ && top >= curRightTop.y_;

        if(answer)
            std::cout << "Yes!";
        else
            std::cout << "No!";

        return in;
    }

    std::istream &operator>>(std::istream &in, EchoIO &&dest){

        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }

        Polygon example{};
        in >> example;

        if(!in) return in;

        std::vector<Polygon>::iterator begin  = dest.polygons.begin();

        int answer = 0;

        for (int i = 0; i < dest.polygons.size(); ++i) {
            Polygon &polygon = dest.polygons[i];
            if(polygon.points.size() != example.points.size()) continue;
            if (std::equal(polygon.points.begin(), polygon.points.end(), example.points.begin(),[]( Point f,  Point s){
                return f.x_ == s.x_ && s.y_ == f.y_;
            })) {
                dest.polygons.insert(dest.polygons.begin()+i, polygon);
                i++;
                answer++;
            }
        }

        std::cout << "\nANSWER " << answer << "\n";

        std::copy(dest.polygons.begin(), dest.polygons.end(), std::ostream_iterator< iakov::Polygon >(std::cout, "\n"));

        return in;
    }

    std::istream &operator>>(std::istream &in, CommandIO &&dest) {
        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }

        int commandCode = -1;

        in >> CommandNameIO{commandCode };

        switch (commandCode) {
            case 1:
                in >> AreaIO{dest.polygons};
                break;
            case 2:
                in >> MaxIO{dest.polygons};
                break;
            case 3:
                in >> MinIO{dest.polygons};
                break;
            case 4:
                in >> CountIO{dest.polygons};
                break;
            case 5:
                in >> EchoIO{dest.polygons};
                break;
            case 6:
                in >> EchoIO{dest.polygons};
                in >> InFrameIO{dest.polygons};
                break;
            default:
                in.setstate(std::ios::failbit);
                break;
        }

        if(!in) {
            std::cout << "INCORRECT COMMAND!";
            in.clear();
            std::string buf;
            std::getline(in, buf);
        }

        return in;
    }


}

#endif //TP_COMMAND_STRUCT_H
