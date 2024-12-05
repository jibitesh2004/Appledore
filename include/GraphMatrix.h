#pragma once

#include <vector>
#include <iostream>
#include <stdexcept>
#include <optional>
#include <map>

namespace Appledore
{
    template <typename EdgeType>
    struct EdgeInfo
    {
        EdgeType value;
        bool isDirected;

        EdgeInfo() : value(), isDirected(false) {}
        EdgeInfo(const EdgeType &value, bool isDirected = false)
            : value(value), isDirected(isDirected) {}
    };
    template <typename VertexType, typename EdgeType = bool>
    class GraphMatrix
    {
    public:
        void addVertex(const VertexType &vertex);
        const std::vector<VertexType> &getVertices() const;
        bool hasEdge(const VertexType &src, const VertexType &dest) const;
        EdgeType getEdgeValue(const VertexType &src, const VertexType &dest) const;
        std::vector<EdgeType> getEdges() const;
        GraphMatrix() : vertexToIndex(), indexToVertex(), adjacencyMatrix() {};
        void removeEdge(const VertexType &src, const VertexType &dest);
        void updateEdge(const VertexType &, const VertexType &, const EdgeType &);
        void addEdge(const VertexType &src, const VertexType &dest, std::optional<EdgeType> edgeValue, bool isDirected = false);
        void addEdge(const VertexType &src, const VertexType &dest, bool isDirected);
        void addEdge(const VertexType &src, const VertexType &dest, const EdgeType &edge);
        void addEdge(const VertexType &src, const VertexType &dest, const EdgeType &edge, bool isDirected);

        const bool operator()(VertexType src, VertexType dest) const
        {
            if (!vertexToIndex.count(src) || !vertexToIndex.count(dest))
            {
                return false;
            }

            size_t srcIndex = vertexToIndex.at(src);
            size_t destIndex = vertexToIndex.at(dest);

            size_t index = getIndex(srcIndex, destIndex);

            return adjacencyMatrix[index].has_value();
        }

    private:
        std::map<VertexType, size_t> vertexToIndex;
        std::vector<VertexType> indexToVertex;
        std::vector<std::optional<EdgeInfo<EdgeType>>> adjacencyMatrix;
        size_t numVertices = 0;
        inline size_t getIndex(size_t src, size_t dest) const;
    };

    template <typename VertexType, typename EdgeType>
    void GraphMatrix<VertexType, EdgeType>::addVertex(const VertexType &vertex)
    {
        if (vertexToIndex.count(vertex))
        {
            std::cout << "Vertex already exists\n";
            return;
        }

        size_t newIndex = numVertices;
        vertexToIndex[vertex] = newIndex;
        indexToVertex.push_back(vertex);
        numVertices++;

        adjacencyMatrix.resize(numVertices * numVertices, std::nullopt);
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

        size_t index = getIndex(srcIndex, destIndex);

        if (!adjacencyMatrix[index].has_value())
        {
            throw std::runtime_error("Edge does not exist");
        }

        return adjacencyMatrix[index]->value;
    }

    template <typename VertexType, typename EdgeType>
    inline size_t GraphMatrix<VertexType, EdgeType>::getIndex(size_t src, size_t dest) const
    {
        return src * numVertices + dest;
    }

    template <typename VertexType, typename EdgeType>
    // generic, being used by all overloads.
    void GraphMatrix<VertexType, EdgeType>::addEdge(const VertexType &src, const VertexType &dest, std::optional<EdgeType> edgeValue, bool isDirected)
    {
        if (!vertexToIndex.count(src) || !vertexToIndex.count(dest))
        {
            throw std::invalid_argument("One or both vertices do not exist");
        }

        size_t srcIndex = vertexToIndex.at(src);
        size_t destIndex = vertexToIndex.at(dest);

        size_t index = getIndex(srcIndex, destIndex);
        adjacencyMatrix[index] = EdgeInfo<EdgeType>(edgeValue.value_or(EdgeType()), isDirected);

        if (!isDirected)
        {
            size_t reverseIndex = getIndex(destIndex, srcIndex);
            adjacencyMatrix[reverseIndex] = EdgeInfo<EdgeType>(edgeValue.value_or(EdgeType()), isDirected);
        }
    }
    template <typename VertexType, typename EdgeType>
    // case 1: non weidghted, directed/undirected egde.
    void GraphMatrix<VertexType, EdgeType>::addEdge(const VertexType &src, const VertexType &dest, bool isDirected)
    {
        addEdge(src, dest, std::nullopt, isDirected);
    }
    template <typename VertexType, typename EdgeType>
    // case 2: weighted, undirected egde.
    void GraphMatrix<VertexType, EdgeType>::addEdge(const VertexType &src, const VertexType &dest, const EdgeType &edge)
    {
        addEdge(src, dest, edge, false);
    }
    template <typename VertexType, typename EdgeType>
    // case 3: weighted, undirected egde.
    void GraphMatrix<VertexType, EdgeType>::addEdge(const VertexType &src, const VertexType &dest, const EdgeType &edge, bool isDirected)
    {
        addEdge(src, dest, std::optional<EdgeType>(edge), isDirected);
    }

    template <typename VertexType, typename EdgeType>
    void GraphMatrix<VertexType, EdgeType>::removeEdge(const VertexType &src, const VertexType &dest)
    {
        if (!vertexToIndex.count(src) || !vertexToIndex.count(dest))
        {
            throw std::invalid_argument("One or both vertices do not exist");
        }

        size_t srcIndex = vertexToIndex[src];
        size_t destIndex = vertexToIndex[dest];

        size_t index = getIndex(srcIndex, destIndex);
        adjacencyMatrix[index] = std::nullopt;

        if (!adjacencyMatrix[getIndex(destIndex, srcIndex)].value_or(EdgeInfo<EdgeType>()).isDirected)
        {
            adjacencyMatrix[getIndex(destIndex, srcIndex)] = std::nullopt;
        }
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

        return adjacencyMatrix[getIndex(srcIndex, destIndex)].has_value();
    }
    template <typename VertexType, typename EdgeType>
    void GraphMatrix<VertexType, EdgeType>::updateEdge(const VertexType &src, const VertexType &dest, const EdgeType &newValue)
    {
        if (!vertexToIndex.count(src) || !vertexToIndex.count(dest))
        {
            throw std::invalid_argument("One or both vertices do not exist");
        }

        size_t srcIndex = vertexToIndex.at(src);
        size_t destIndex = vertexToIndex.at(dest);

        size_t index = getIndex(srcIndex, destIndex);

        if (!adjacencyMatrix[index].has_value())
        {
            throw std::runtime_error("Edge does not exist");
        }

        adjacencyMatrix[index]->value = newValue;

        // If the edge is undirected, update the reverse edge too
        if (!adjacencyMatrix[index]->isDirected)
        {
            size_t reverseIndex = getIndex(destIndex, srcIndex);
            adjacencyMatrix[reverseIndex]->value = newValue;
        }
    }

    template <typename VertexType, typename EdgeType>
    const std::vector<VertexType> &GraphMatrix<VertexType, EdgeType>::getVertices() const
    {
        return indexToVertex;
    }

    template <typename VertexType, typename EdgeType>
    std::vector<EdgeType> GraphMatrix<VertexType, EdgeType>::getEdges() const
    {
        std::vector<EdgeType> edges;

        for (size_t src = 0; src < numVertices; ++src)
        {
            for (size_t dest = 0; dest < numVertices; ++dest)
            {
                size_t index = getIndex(src, dest);

                if (adjacencyMatrix[index].has_value() && adjacencyMatrix[index]->isDirected)
                {
                    edges.push_back(adjacencyMatrix[index]->value);
                }
                else if (adjacencyMatrix[index].has_value() && src <= dest) // For undirected, avoid duplicates
                {
                    edges.push_back(adjacencyMatrix[index]->value);
                }
            }
        }

        return edges;
    }

};
