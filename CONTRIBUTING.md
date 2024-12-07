# Contributing to Appledore

Welcome to Appledore, a graph library designed to simplify graph representation and manipulation! Thank you for considering contributing to this project. Whether you're fixing a bug, adding a feature, or improving documentation, your efforts are greatly appreciated.

---


## How to Contribute

1. **Fork the repository** on GitHub.
2. **Clone your fork**:  
   ```bash
   git clone https://github.com/your-username/appledore.git
3. **Create a branch** for your feature or bug fix
    ```bash
    git checkout -b feature/your-feature-name
4. Write code and tests.
5. Submit a **pull request** (PR) with a clear description of your changes

# Ideas for Contributions
Here are some features and improvements you can work on.
To contribute, make sure to create a issue first and wait till it is assigned to you.
## Core features for GraphMatrix.h
- ``hasVertex`` function to check whether a vertex exists in the graph or not.
- ``getNeighbors`` function to get neighbors/adjacent neighbors of a vertex.
- ``removeEdge`` function to remove an edge between two vertices from the graph.
- ``removeVertex`` function to remove a vertex from the graph.
- ``clone`` function to support deep copy cloning a graph.
- ``getInDegree`` function to get number of indegrees for a vertex.
- ``outDegree`` function to get number of outdegrees for a vertex.

---

## Documentation and Examples
- Improve the API documentation to make it beginner-friendly.
- Write tutorials and example programs showcasing common use cases of the library.
- You can contribute towards documentation either by mentioning doxygen docstrings above functions and classes, or contribute markdown files for the wiki.

## Coding Guidelines
- Follow modern C++ best practices such as RAII (Resource Acquisition Is Initialization), avoiding raw pointers where possible, and using STL containers effectively.
- Use meaningful names for variables, functions, and classes.
- Maintain consistent indentation and formatting (4 spaces per indentation level is recommended).
- Document all public-facing methods using comments or docstrings.
- Ensure code compiles without warnings and passes all tests before submission.