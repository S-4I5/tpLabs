//
// Created by Администратор on 18.05.2022.
//

#ifndef TP_COMMAND_STRUCT_H
#define TP_COMMAND_STRUCT_H

#include <string>
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

    if(!in) return in;

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

    if(!in) return in;

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

    if(!in) return in;

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

    if(!in) return in;

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

    if(!in) return in;

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

    if(!in) return in;

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

    std::vector<std::string> commandNames = {"ADDPOINT", "ADDARC", "HASARC", "HASPOINT", "DELETEARC", "DELETEPOINT", "FINDDISTANCE", "PRINT"};

    int commandIndex;

    in >> IndexIO{commandIndex, commandNames};

    switch (commandIndex) {
        case 0:
            in >> AddPointIO{dest.graph};
            break;
        case 1:
            in >> AddArcIO{dest.graph};
            break;
        case 2:
            in >> HasArcIO{dest.graph};
            break;
        case 3:
            in >> HasPointIO{dest.graph};
            break;
        case 4:
            in >> DeleteAcrIO{dest.graph};
            break;
        case 5:
            in >> DeletePointIO{dest.graph};
            break;
        case 6:
            in >> FindDistanceIO{dest.graph};
            break;
        case 7:
            dest.graph.print();
            break;
        default:
            in.setstate(std::ios::failbit);
            break;
    }

    if(!in) {
        std::cout << "<INCORRECT COMMAND!>\n";
        in.clear();
        std::string buf;
        std::getline(in, buf);
    }

    return in;
}

#endif //TP_COMMAND_STRUCT_H
