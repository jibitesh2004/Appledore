# Appledore
A simple and efficient graph library in modern C++ Supports directed/undirected graphs with customizable edge type and vertices, designed for performance and ease of use.

## Features
- Adjacency matrix-based representation.
- Adjacency list-based representation
- Supports custom vertex and edge types
- Efficient management of vertices and edges
- Easy querying of graph structure and properties
- Upcoming features: support for graph degrees, advanced graph algorithms (e.g., Dijkstra, BFS, DFS), and additional utilities for graph analysis.

## Installation
1. Clone the repository
```
 git clone https://github.com/yourusername/appledore.git
```
2. Include the ``GraphMatrix`` header in your project

## Example Diagram
Code below implements this Graph relationship between USA States and transport medium.
![Screenshot_20241205_124620-1](https://github.com/user-attachments/assets/1db263c6-1538-4b14-8b33-725bb68ebc06)
## Example using Custom Structures/Classes
Below is an example of how to use the library with custom vertex and edge types.
Find more examples [here](https://github.com/SharonIV0x86/Appledore/tree/main/examples)
```cpp
#include <iostream>
#include <string>
#include "./include/GraphMatrix.h"

// Vertex class representing a state in the USA
class State
{
public:
    std::string stateName;
    std::string capitalCity;
    int population;

    State(const std::string &name, const std::string &capital, int pop)
        : stateName(name), capitalCity(capital), population(pop) {}

    bool operator<(const State &other) const
    {
        return stateName < other.stateName;
    }
};

class Connection
{
public:
    int distance;
    std::string transportMode;

    Connection(){}
    Connection(int dist, const std::string &mode)
        : distance(dist), transportMode(mode) {}
};

int main()
{
    Appledore::GraphMatrix<State, Connection> americaNetwork;

    // American States
    State california("California", "Sacramento", 39538223);
    State texas("Texas", "Austin", 29145505);
    State florida("Florida", "Tallahassee", 21538187);
    State newYork("New York", "Albany", 20201249);

    americaNetwork.addVertex(california);
    americaNetwork.addVertex(texas);
    americaNetwork.addVertex(florida);
    americaNetwork.addVertex(newYork);

    Connection roadConnection(1500, "Road");   // Distance: 1500 miles, Mode: Road
    Connection trainConnection(1300, "Train"); // Distance: 1300 miles, Mode: Train
    Connection airConnection(1000, "Air");     // Distance: 1000 miles, Mode: Air
    Connection waterConnection(400, "Water");  // Distance: 400 miles,  Mode: Water
    // Add edges (connections) between states
    americaNetwork.addEdge(california, texas, roadConnection, false);   // California <-> Texas (Road)
    americaNetwork.addEdge(florida, newYork, trainConnection, false);  // Florida <-> New York (Train)
    americaNetwork.addEdge(texas, florida, airConnection, true);       // Texas <-> Florida (Air)
    americaNetwork.addEdge(california, florida, waterConnection, true); // California -> Florida (water)
    // Print details of the states and connections
    std::cout << "American States and Connections:" << std::endl;
    std::vector<State> states = americaNetwork.getVertices();
    for (const State &st : states)
    {
        for (const State &st2 : states)
        {
            if (americaNetwork(st, st2))
            {
                Connection edgeValue = americaNetwork.getEdgeValue(st, st2);
                std::cout << "Edge Connection between " << st.stateName << " and " << st2.stateName << "\n";
                std::cout << "Distance: " << edgeValue.distance << "\n";
                std::cout << "Transport: " << edgeValue.transportMode << "\n";
            }
        }
    }

    return 0;
}

```
# Contributions
If you'd like to contribute anything, any new feature, work on required features or submit a bug fix make sure to read the [contributing](https://github.com/SharonIV0x86/Appledore/blob/main/CONTRIBUTING.md)