# Appledore
A simple and efficient graph library in modern C++ Supports directed/undirected graphs with customizable edge type and vertices, designed for performance and ease of use.

## Features
- Adjacency matrix-based representation.
- Adjacency list-based representation
- Supports custom vertex and edge types
- Efficient management of vertices and edges
- Easy querying of graph structure and properties

## Installation
1. Clone the repository
```
 git clone https://github.com/yourusername/appledore.git
```
2. Include the ``GraphMatrix`` header in your project

## Example usage
Below is an example of how to use the library with custom vertex and edge types.
## Custom Structures
```cpp
#include "GraphMatrix.h"
#include <iostream>
#include <string>

// Custom structure for vertex
struct City
{
    std::string name;

    City(std::string n) : name(n) {}

    bool operator==(const City &other) const {
        return name == other.name;
    }

    friend std::ostream &operator<<(std::ostream &os, const City &city) {
        os << city.name;
        return os;
    }
};

// Custom structure for edge value
struct Road
{
    int distance; // in kilometers

    Road(int dist) : distance(dist) {}

    friend std::ostream &operator<<(std::ostream &os, const Road &road) {
        os << road.distance << " km";
        return os;
    }
};

int main()
{
    Appledore::GraphMatrix<City, Road> cityGraph;

    City city1("New York");
    City city2("Los Angeles");
    City city3("Chicago");
    cityGraph.addVertex(city1);
    cityGraph.addVertex(city2);
    cityGraph.addVertex(city3);

    cityGraph.addEdge(city1, city2, Road(450), false); 
    cityGraph.addEdge(city2, city3, Road(200), true);  

    for (const auto &vertex : cityGraph.getVertices()) {
        std::cout << "City: " << vertex << std::endl;
    }

    if (cityGraph.hasEdge(city1, city2)) {
        std::cout << "Road from " << city1 << " to " << city2 << " is " 
                  << cityGraph.getEdgeValue(city1, city2) << std::endl;
    }

    if (cityGraph.hasEdge(city2, city3)) {
        std::cout << "Road from " << city2 << " to " << city3 << " is " 
                  << cityGraph.getEdgeValue(city2, city3) << std::endl;
    }

    return 0;
}
```
Output
```
City: New York
City: Los Angeles
City: Chicago
Road from New York to Los Angeles is 450 km
Road from Los Angeles to Chicago is 200 km
```
