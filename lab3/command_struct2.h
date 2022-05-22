#ifndef TP_COMMAND_STRUCT_H
#define TP_COMMAND_STRUCT_H

#include <vector>
#include "iostream"
#include <algorithm>
#include <functional>
#include <sstream>
#include <numeric>
#include "iofmtguard.h"

using namespace std::placeholders;

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

    template<class T>
    void printError(T& error){
        std::cout << " ... " << error << " <- !";
    }

    bool check(std::istream &in){

        if(!in){
            printError("<INCORRECT ARGUMENT>");
            return false;
        }

        char check = '0';

        in.get(check);

        while(check == ' ' && !in.eof()){
            //std::cout << check << "\n";
            in.get(check);
        }

        //std::cout << (int)check << "!\n";

        if((!in || check != '\n') && !in.eof()) {
            printError(check);
            return false;
        }
        return true;
    }

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

        if(dest.code == 0)
            printError(currentArgument);
        else
            std::cout << " " << currentArgument;

        return in;
    }

    std::istream &operator>>(std::istream &in, CommandNameIO &&dest) {

        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }

        std::string currentCommand;

        in >> currentCommand;

        std::string commandNames [] = {"AREA", "MAX", "MIN", "COUNT", "ECHO","INFRAME"};

        for (int i = 0; i < 6; ++i) {
            if(currentCommand == commandNames[i]) dest.code = i+1;
        }

        std::cout << "\n" << currentCommand;

        return in;
    }

    double getArea(const std::vector<Polygon>& polygons, const int argumentIndex){

        switch (argumentIndex) {
            case -1:
                return std::accumulate(polygons.cbegin(), polygons.cend(), 0.0,[](double ans, const Polygon &polygon)
                {
                    if(polygon.points.size()%2 == 0)
                        return ans + getArea(polygon);
                    else
                        return ans;
                });
            case -2:
                return std::accumulate(polygons.cbegin(), polygons.cend(), 0.0,[](double ans, const Polygon &polygon)
                {
                    if(polygon.points.size()%2 != 0)
                        return ans + getArea(polygon);
                    else
                        return ans;
                });
            case -3:
                return std::accumulate(polygons.cbegin(), polygons.cend(), 0.0,[](double ans, const Polygon &polygon)
                {
                    return ans + getArea(polygon);
                })/polygons.size();
            default:
                return std::accumulate(polygons.cbegin(), polygons.cend(), 0.0,[&argumentIndex](double ans, const Polygon &polygon)
                {
                    if(polygon.points.size() == argumentIndex)
                        return ans + getArea(polygon);
                    else
                        return ans;
                });
        }
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
            in.setstate(std::ios::badbit);
            return in;
        }

        if(!check(in)){
            in.setstate(std::ios::badbit);
            return in;
        }


        std::cout << "\nANSWER " << getArea(dest.polygons, argumentCode) << "\n";

        return in;
    }

    double max(const std::vector<Polygon>& polygons, const int argumentIndex){
        double answer = 0;

        if(argumentIndex == -1){
            answer = getArea(*std::max_element(polygons.cbegin(), polygons.cend(), [](const Polygon &f,const Polygon &s){
                if(getArea(f) < getArea(s)) return true;
                return false;
            }));
        }else if(argumentIndex == -2){
            answer = (*std::max_element(polygons.cbegin(),polygons.cend(), [](const Polygon &f,const Polygon &s){
                if(f.points.size() < s.points.size()) return true;
                return false;
            })).points.size();
        }

        return answer;
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
            in.setstate(std::ios::badbit);
            return in;
        }

        if(!check(in)){
            in.setstate(std::ios::badbit);
            return in;
        }

        std::cout << "\nANSWER " << max(dest.polygons, argumentCode) << "\n";

        return in;
    };

    double min(const std::vector<Polygon>& polygons, const int argumentIndex){
        double answer = 0;

        if(argumentIndex == -1){
            return getArea(*std::min_element(polygons.cbegin(), polygons.cend(), [](const Polygon &f,const Polygon &s){
                if(getArea(f) < getArea(s)) return true;
                return false;
            }));
        }else if(argumentIndex == -2){
            return (*std::min_element(polygons.cbegin(), polygons.cend(), [](const Polygon &f,const Polygon &s){
                if(f.points.size() < s.points.size()) return true;
                return false;
            })).points.size();
        }

        return answer;
    }

    std::istream &operator>>(std::istream &in, MinIO &&dest){

        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }

        std::vector<std::string> argumentNames = {"AREA", "VERTEXES"};
        int argumentCode = 0;
        in >> ArgumentIO{argumentCode, argumentNames};

        if(argumentCode == 0){
            in.setstate(std::ios::badbit);
            return in;
        }

        if(!check(in)){
            in.setstate(std::ios::badbit);
            return in;
        }

        std::cout << "\nANSWER " << min(dest.polygons, argumentCode) << "\n";

        return in;
    };

    int count(const std::vector<Polygon>& polygons, const int argumentIndex){

        int answer = 0;

        switch (argumentIndex) {
            case -1:
                return std::count_if(polygons.cbegin(), polygons.cend(),[]( const Polygon &polygon)
                {
                    return polygon.points.size()%2 == 0;
                });
                break;
            case -2:
                return std::count_if(polygons.cbegin(), polygons.cend(), []( const Polygon &polygon)
                {
                    return polygon.points.size()%2 != 0;
                });
                break;
            default:
                return std::count_if(polygons.cbegin(), polygons.cend(),[&argumentIndex](const Polygon &polygon)
                {
                    return polygon.points.size() == argumentIndex;
                });
        }
    }

    std::istream &operator>>(std::istream &in, CountIO &&dest){

        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }

        std::vector<std::string> argumentNames = {"EVEN", "ODD"};
        int argumentCode = 0;
        in >> ArgumentIO{argumentCode, argumentNames};

        if(argumentCode == 0){
            in.setstate(std::ios::badbit);
            return in;
        }

        if(!check(in)){
            in.setstate(std::ios::badbit);
            return in;
        }

        std::cout << "\nANSWER " << count(dest.polygons, argumentCode) << "\n";

        return in;
    };

    bool inFrame(const std::vector<Polygon>& polygons,const Polygon &example){

        auto getX = [](const Point& point){return point.x_;};

        auto getY = [](const Point& point){return point.y_;};

        auto getLeftDown = [&getX, &getY](const Polygon &current){
            return Point{(*std::min_element(current.points.cbegin(), current.points.cend(), std::bind(std::less<int>(), std::bind(getX, _1), std::bind(getX, _2)))).x_,
                         (*std::min_element(current.points.cbegin(), current.points.cend(), std::bind(std::less<int>(), std::bind(getY, _1), std::bind(getY, _2)))).y_};
        };

        auto getRightTop = [&getX, &getY](const Polygon &current){
            return Point{(*std::max_element(current.points.cbegin(), current.points.cend(),std::bind(std::less<int>(), std::bind(getX, _1), std::bind(getX, _2)))).x_,
                         (*std::max_element(current.points.cbegin(), current.points.cend(),std::bind(std::less<int>(), std::bind(getY, _1), std::bind(getY, _2)))).y_};
        };

        Point curLeftDown = getLeftDown(example);
        Point curRightTop = getRightTop(example);

        int left = getLeftDown(*std::min_element(polygons.cbegin(), polygons.cend(),
                                                 std::bind(std::less<int>(),
                                                           std::bind(getX, std::bind(getLeftDown, _1)),
                                                           std::bind(getX, std::bind(getLeftDown, _2))
                                                 ))).x_;

        int down = getLeftDown(*std::min_element(polygons.cbegin(), polygons.cend(),
                                                 std::bind(std::less<int>(),
                                                           std::bind(getY, std::bind(getLeftDown, _1)),
                                                           std::bind(getY, std::bind(getLeftDown, _2))
                                                 ))).y_;

        int right = getRightTop(*std::max_element(polygons.cbegin(), polygons.cend(),
                                                  std::bind(std::less<int>(),
                                                            std::bind(getX, std::bind(getRightTop, _1)),
                                                            std::bind(getX, std::bind(getRightTop, _2))
                                                  ))).x_;

        int top = getRightTop(*std::max_element(polygons.cbegin(), polygons.cend(),
                                                std::bind(std::less<int>(),
                                                          std::bind(getY, std::bind(getRightTop, _1)),
                                                          std::bind(getY, std::bind(getRightTop, _2))
                                                ))).y_;

        return left <= curLeftDown.x_ && down <= curLeftDown.y_
                      &&right >= curRightTop.x_ && top >= curRightTop.y_;
    }

    std::istream &operator>>(std::istream &in, InFrameIO &&dest){
        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }

        Polygon example{};
        in >> example;

        if(!check(in)){
            in.setstate(std::ios::badbit);
            return in;
        }

        std::cout << example << "\nANSWER ";

        if(inFrame(dest.polygons, example))
            std::cout << "Yes!\n";
        else
            std::cout << "No!\n";

        return in;
    }

    int echo(std::vector<Polygon>& polygons,const Polygon &example){

        std::vector<Polygon> newDest;
        int answer = 0;

        std::copy_if(polygons.begin(),  polygons.end(), std::back_inserter(newDest), [ &example, &newDest, &answer](const Polygon& polygon){

            if(polygon.points.size() != example.points.size()) {
                return true;
            }

            if (std::equal(polygon.points.begin(), polygon.points.end(), example.points.begin(),[](const Point& f,const  Point& s){
                return f.x_ == s.x_ && s.y_ == f.y_;
            })){
                answer++;
                newDest.push_back(polygon);
            }
            return true;
        });

        polygons = newDest;

        return answer;

    }

    std::istream &operator>>(std::istream &in, EchoIO &&dest){

        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }

        Polygon example{};
        in >> example;

        int i = -1;

        if(!check(in)){
            in.setstate(std::ios::badbit);
            return in;
        }


        std::cout << example << "\nANSWER " << echo(dest.polygons, example) << "\n";

        std::copy(dest.polygons.begin(), dest.polygons.end(), std::ostream_iterator< iakov::Polygon >(std::cout, "\n"));

        return in;
    }

    std::istream &operator>>(std::istream &in, CommandIO &&dest) {

        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }

        std::string buffer = "";
        std::getline(in, buffer);
        std::istringstream commandStream(buffer);

        int commandCode = -1;

        commandStream >> CommandNameIO{commandCode };

        switch (commandCode) {
            case 1:
                commandStream >> AreaIO{dest.polygons};
                break;
            case 2:
                commandStream >> MaxIO{dest.polygons};
                break;
            case 3:
                commandStream >> MinIO{dest.polygons};
                break;
            case 4:
                commandStream >> CountIO{dest.polygons};
                break;
            case 5:
                commandStream >> EchoIO{dest.polygons};
                break;
            case 6:
                commandStream >> InFrameIO{dest.polygons};
                break;
            default:
                commandStream.setstate(std::ios::badbit);
                break;
        }

        if(commandStream.bad()) {
            std::cout << "\n<INCORRECT COMMAND!>\n";
            /*in.clear();
            std::string buf;
            std::getline(in, buf);*/
        }

        return in;
    }
}

#endif //TP_COMMAND_STRUCT_H
