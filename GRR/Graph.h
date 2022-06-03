#ifndef ALGORITHMS_2021_GRAPH_H
#define ALGORITHMS_2021_GRAPH_H

#include "SmartMatrix.h"
#include <stack>
#include <queue>
#include <limits>
#include <vector>
#include <iostream>

namespace iakov {

    class Graph {
    private:

        SmartMatrix *matrix_;

        std::vector<std::string> *pointNames_;

        int numberOfPoints_;

        const int isPointExists(std::string &name);

        const bool hasArcs(int departmentPointIndex);

        const bool isArcExists(int departmentPointName, int destinationPointName);

    public:

        Graph();

        [[nodiscard]] bool isEmpty() const;

        const bool hasPoint(std::string &name);

        const bool hasPoint(std::string &&name);

        const bool addPoint(std::string &name);

        const bool addPoint(std::string &&name);

        const bool deletePoint(std::string &name);

        const bool deletePoint(std::string &&name);

        void print();

        const bool deleteArc(std::string &departmentPointName, std::string &destinationPointName);

        const bool deleteArc(std::string &&departmentPointName, std::string &&destinationPointName);

        const bool adArc(std::string &departmentPointName, std::string &destinationPointName, int mass);

        const bool adArc(std::string &&departmentPointName, std::string &&destinationPointName, int mass);

        const bool hasArcs(std::string &departmentPointName);

        const bool isArcExists(std::string &departmentPointName, std::string &destinationPointName);

        const bool isArcExists(std::string &&departmentPointName, std::string &&destinationPointName);

        const bool wavePathFinderAlgorithm(std::string &departmentPointName, std::string &destinationPointName);

        const bool dijkstraPathFinderAlgorithm(std::string &departmentPointName, std::string &destinationPointName);

        const bool bellmanFordPathFinderAlgorithm(std::string &departmentPointName, std::string &destinationPointName);

        ~Graph();

    };
}


#endif //ALGORITHMS_2021_GRAPH_H
