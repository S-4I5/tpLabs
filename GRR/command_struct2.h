//
// Created by Администратор on 18.05.2022.
//

#ifndef TP_COMMAND_STRUCT_H
#define TP_COMMAND_STRUCT_H

#include <string>
#include "sstream"
#include "Graph.h"

struct CommandIO{
    Graph &graph;
};

struct IndexIO{
    int &index;
    std::vector<std::string>& names;
};

struct DelimiterIO {
    char exp;
};

struct StringIO {
    std::string &ref;
};

struct IntIO{
    int &ref;
};

struct AddPointIO{
    Graph &graph;
};

struct AddArcIO{
    Graph &graph;
};

struct HasArcIO{
    Graph &graph;
};

struct HasPointIO{
    Graph &graph;
};

struct DeleteAcrIO{
    Graph &graph;
};

struct DeletePointIO{
    Graph &graph;
};

struct FindDistanceIO{
    Graph &graph;
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
        in.get(check);
    }

    if((!in || check != '\n') && in.eof()) {
        std::cout << "ss1";
        in.setstate(std::ios::badbit);
        printError(check);
        return false;
    }

    return true;
}

std::istream &operator>>(std::istream &in, DelimiterIO &&dest){

    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }

    char c = '0';
    in >> c;

    if(in && c != dest.exp) in.setstate(std::ios::badbit);

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

std::istream &operator>>(std::istream &in, IntIO &&dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }

    in >> dest.ref;

    return in;
}

std::istream &operator>>(std::istream &in, AddArcIO &&dest){
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }

    std::string firstPoint = "";
    std::string secondPoint = "";
    int weight = -1;

    in >> StringIO{firstPoint};
    in >> StringIO{secondPoint};
    in >> IntIO{weight};

    if(!check(in)) return in;

    std::cout << "Arc between" << firstPoint << " and " << secondPoint << " with weight " << weight;
    if(dest.graph.adArc(firstPoint, secondPoint, weight))
        std::cout << " was added!\n";
    else
        std::cout << " wasn't added.\n";

    return in;
}

std::istream &operator>>(std::istream &in, AddPointIO &&dest){
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }

    std::string pointName = "";

    in >> StringIO{pointName};

    if(!check(in)) return in;

    std::cout << "Point " << pointName;

    if(dest.graph.addPoint(pointName))
        std::cout  << " added!\n";
    else
        std::cout << " not added.\n";

    return in;
}

std::istream &operator>>(std::istream &in, HasArcIO &&dest) {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }

    std::string firstPoint = "";
    std::string secondPoint = "";

    in >> StringIO{firstPoint};
    in >> StringIO{secondPoint};

    if(!check(in)) return in;

    std::cout << "Arc between " << firstPoint << " and " << secondPoint;
    if(dest.graph.isArcExists(firstPoint,secondPoint))
        std::cout << " exists!\n";
    else
        std::cout << " don't exists.\n";

    return in;
}

std::istream &operator>>(std::istream &in, HasPointIO &&dest) {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }

    std::string pointName = "";

    in >> StringIO{pointName};

    std::cout << pointName;

    if(!check(in)) return in;

    std::cout << "Point " << pointName;

    if(dest.graph.hasPoint(pointName))
        std::cout << " exists!\n";
    else
        std::cout << " don't exists.\n";

    return in;
}

std::istream &operator>>(std::istream &in, DeleteAcrIO &&dest){

    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }

    std::string firstPoint = "";
    std::string secondPoint = "";

    in >> StringIO{firstPoint};
    in >> StringIO{secondPoint};

    if(!check(in)) return in;

    std::cout << "Arc between " << firstPoint << " and " << secondPoint;

    if(dest.graph.deleteArc(firstPoint, secondPoint))
        std::cout << " was deleted!\n";
    else
        std::cout << " wasn't deleted\n";

    return in;
}

std::istream &operator>>(std::istream &in, DeletePointIO &&dest){

    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }

    std::string pointName = "";

    in >> StringIO{pointName};

    std::cout << pointName;

    if(!check(in)) return in;

    std::cout << "Point " << pointName;

    if(dest.graph.deletePoint(pointName))
        std::cout << " was deleted!\n";
    else
        std::cout << " wasn't deleted.\n";

    return in;
}

std::istream &operator>>(std::istream &in,IndexIO &&dest) {

    dest.index = -1;

    std::string command = "";

    in >> command;

    for (int i = 0; i < dest.names.size(); ++i) {
        if(dest.names.at(i) == command) dest.index = i;
    }

    return in;
}

std::istream &operator>>(std::istream &in, FindDistanceIO &&dest) {

    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }

    std::vector<std::string> algorithmNames = {"DIJKSTRA", "BELLMAN-FORD", "WAVE"};

    int algorithmIndex = -1;

    in >> IndexIO{algorithmIndex, algorithmNames};

    std::string firstPoint = "";
    std::string secondPoint = "";

    in >> StringIO{firstPoint};
    in >> StringIO{secondPoint};

    if(!check(in)) return in;

    switch (algorithmIndex) {
        case 0:
            dest.graph.dijkstraPathFinderAlgorithm(firstPoint,secondPoint);
            break;
        case 1:
            dest.graph.bellmanFordPathFinderAlgorithm(firstPoint, secondPoint);
            break;
        case 2:
            dest.graph.wavePathFinderAlgorithm(firstPoint, secondPoint);
            break;
    }

    return in;
}

std::istream &operator>>(std::istream &in, CommandIO &&dest){

    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }

    std::string buffer = "";
    std::getline(in, buffer);
    std::istringstream commandStream(buffer);

    std::vector<std::string> commandNames = {"ADDPOINT", "ADDARC", "HASARC", "HASPOINT", "DELETEARC", "DELETEPOINT", "FINDDISTANCE", "PRINT"};

    int commandIndex;

    commandStream >> IndexIO{commandIndex, commandNames};

    switch (commandIndex) {
        case 0:
            commandStream >> AddPointIO{dest.graph};
            break;
        case 1:
            commandStream >> AddArcIO{dest.graph};
            break;
        case 2:
            commandStream >> HasArcIO{dest.graph};
            break;
        case 3:
            commandStream >> HasPointIO{dest.graph};
            break;
        case 4:
            commandStream >> DeleteAcrIO{dest.graph};
            break;
        case 5:
            commandStream >> DeletePointIO{dest.graph};
            break;
        case 6:
            commandStream >> FindDistanceIO{dest.graph};
            break;
        case 7:
            dest.graph.print();
            break;
        default:
            commandStream.setstate(std::ios::failbit);
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

#endif //TP_COMMAND_STRUCT_H
