#pragma once

#include <vector>
#include <iostream>
#include <stdexcept>
#include <optional>
#include <map>

namespace Appledore
{
    template <typename VertexType, typename EdgeType = bool>
    class GraphMatrix
    {
    public:
        void addVertex(const VertexType &vertex);
        void addEdge(const VertexType &src, const VertexType &dest, std::optional<EdgeType> edgeValue, bool isDirected = false);
        void addEdge(const VertexType &src, const VertexType &dest, bool isDirected);
        const std::vector<VertexType> &getVertices() const;
        bool hasEdge(const VertexType &src, const VertexType &dest) const;
        EdgeType getEdgeValue(const VertexType &src, const VertexType &dest) const;

        GraphMatrix() : vertexToIndex(), indexToVertex(), adjacencyMatrix() {}

    private:
        std::map<VertexType, size_t> vertexToIndex;                        
        std::vector<VertexType> indexToVertex;                             
        std::vector<std::vector<std::optional<EdgeType>>> adjacencyMatrix; 
    };

    template <typename VertexType, typename EdgeType>
    void GraphMatrix<VertexType, EdgeType>::addVertex(const VertexType &vertex)
    {
        if (vertexToIndex.count(vertex))
        {
            std::cout << "Vertex already exists\n";
            return; 
        }

        size_t newIndex = indexToVertex.size();
        vertexToIndex[vertex] = newIndex;
        indexToVertex.push_back(vertex);

        for (auto &row : adjacencyMatrix)
        {
            row.push_back(std::nullopt);
        }
        adjacencyMatrix.emplace_back(newIndex + 1, std::nullopt);
    }

    template <typename VertexType, typename EdgeType>
    void GraphMatrix<VertexType, EdgeType>::addEdge(const VertexType &src, const VertexType &dest,
                                                    std::optional<EdgeType> edgeValue,
                                                    bool isDirected)
    {
        if (!vertexToIndex.count(src) || !vertexToIndex.count(dest))
        {
            throw std::invalid_argument("One or both vertices do not exist");
        }

        size_t srcIndex = vertexToIndex[src];
        size_t destIndex = vertexToIndex[dest];

        adjacencyMatrix[srcIndex][destIndex] = edgeValue.value_or(EdgeType());

        if (!isDirected)
        {
            adjacencyMatrix[destIndex][srcIndex] = edgeValue.value_or(EdgeType());
        }
    }

    template <typename VertexType, typename EdgeType>
    void GraphMatrix<VertexType, EdgeType>::addEdge(const VertexType &src, const VertexType &dest, bool isDirected)
    {
        addEdge(src, dest, std::nullopt, isDirected);
    }

    template <typename VertexType, typename EdgeType>
    const std::vector<VertexType> &GraphMatrix<VertexType, EdgeType>::getVertices() const
    {
        return indexToVertex; //just returns a const reference to the vector.
    }

    template <typename VertexType, typename EdgeType>
    bool GraphMatrix<VertexType, EdgeType>::hasEdge(const VertexType &src, const VertexType &dest) const
    {
        if (!vertexToIndex.count(src) || !vertexToIndex.count(dest))
        {
            throw std::invalid_argument("One or both vertices do not exist");
        }

        size_t srcIndex = vertexToIndex.at(src);
        size_t destIndex = vertexToIndex.at(dest);

        return adjacencyMatrix[srcIndex][destIndex].has_value();
    }

    template <typename VertexType, typename EdgeType>
    EdgeType GraphMatrix<VertexType, EdgeType>::getEdgeValue(const VertexType &src, const VertexType &dest) const
    {
        if (!vertexToIndex.count(src) || !vertexToIndex.count(dest))
        {
            throw std::invalid_argument("One or both vertices do not exist");
        }

        size_t srcIndex = vertexToIndex.at(src);
        size_t destIndex = vertexToIndex.at(dest);

        if (!adjacencyMatrix[srcIndex][destIndex].has_value())
        {
            throw std::runtime_error("No edge exists between the given vertices");
        }

        return adjacencyMatrix[srcIndex][destIndex].value();
    }
}
