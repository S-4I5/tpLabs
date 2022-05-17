#include <iostream>
#include <fstream>
#include "Graph.h"
#include "command_struct.h"

/*void testAll(std::string&& departmentPoint, std::string&& destinationPoint, Graph* graph){

    std::cout << "Wave: \n\n";

    graph->wavePathFinderAlgorithm(departmentPoint, destinationPoint);

    std::cout << "\nDijkstra: \n\n";

    graph->dijkstraPathFinderAlgorithm(departmentPoint, destinationPoint);

    std::cout << "\nBellman-Ford: \n\n";

    graph->bellmanFordPathFinderAlgorithm(departmentPoint, destinationPoint);

}

void defaultTest(){

    auto* graph = new Graph();

    graph->addPoint("A");

    graph->addPoint("B");

    graph->addPoint("C");

    graph->addPoint("D");

    graph->adArc("A", "B", 1);

    graph->adArc("B", "A", 3);

    graph->adArc("A", "C", 8);

    graph->adArc("B", "D", 6);

    graph->adArc("B", "C", 5);

    graph->adArc("C", "D", 4);

    graph->adArc("D", "C", 4);

    graph->print();

    testAll("A", "C", graph);
}

void bellmanFordTest(){

    auto* graph = new Graph();

    graph->addPoint("A");

    graph->addPoint("B");

    graph->addPoint("C");

    graph->addPoint("D");

    graph->adArc("A", "C", 2);

    graph->adArc("A", "B", 3);

    graph->adArc("B", "C", -2);

    graph->adArc("C", "D", 1);

    graph->print();

    testAll("A", "D", graph);
}

void loop(){

    auto* graph = new Graph();

    graph->addPoint("A");

    graph->addPoint("B");

    graph->addPoint("C");

    graph->addPoint("D");

    graph->addPoint("E");

    graph->addPoint("F");

    graph->adArc("A", "B", 1);

    graph->adArc("B", "E", 2);

    graph->adArc("E", "F", 1);

    graph->adArc("C", "B", -2);

    graph->adArc("D", "C", 2);

    graph->adArc("E", "D", -4);

    graph->print();

    testAll("A", "F", graph);

}

void graphTest(){
    auto* graph = new Graph();

    std::cout << graph->addPoint("A") << ": A added\n";

    graph->print();

    graph->addPoint("B");

    graph->print();

    std::cout << graph->addPoint("A") << ": second A added\n";

    graph->print();

    std::cout << graph->adArc("A", "B", 1) << ": Arc A-B added\n";

    std::cout << graph->adArc("A", "B", 1) << ": Arc A-B secondly added\n";

    std::cout << graph->isArcExists("A", "B") << ": exists A-B added\n";

    std::cout << graph->deleteArc("A", "B") << ": Arc A-B deleted\n";

    std::cout << graph->adArc("A", "V", 1) << ": Arc A-V added\n";

    std::cout << graph->deleteArc("A", "V") << ": Arc A-V deleted\n";

    std::cout << graph->adArc("A", "B", 0) << ": Arc A-B with mass 0 added\n";

    graph->print();

    std::cout << graph->deletePoint("B") << ": B deleted\n";

    graph->print();

    std::cout << graph->deletePoint("B") << ": B secondly deleted\n";

    std::cout << graph->deletePoint("A") << ": A deleted\n";

    graph->print();

}

int main()
{
    std::cout << "\nGraph test\n\n";

    graphTest();

    std::cout << "\nDefault test:\n\n";

    defaultTest();

    std::cout << "\nBellman-Ford test:\n\n";

    bellmanFordTest();

    std::cout << "\nNegative circle test:\n\n";

    loop();

    return 0;
}*/

int main(){
    Graph graph;
    /*while (std::cin >> CommandIO{graph});*/

    std::ifstream in("D:\\PTcodes\\c++\\TP\\GRR\\input.txt");

    while(in >> CommandIO{graph});
}

