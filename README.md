## 2D KDTree for Nearest Neighbor Search

### Overview

This C++ program implements a 2D KDTree to efficiently perform nearest neighbor searches. KDTrees are a type of binary search tree that partition data points in a k-dimensional space, making them ideal for multidimensional search queries.

### Features

- **KDTree Construction**: Builds a KDTree from a set of 2D points.
- **Nearest Neighbor Search**: Efficiently finds the nearest neighbor to a given query point.
- **Balanced Tree Structure**: Ensures optimal search performance by balancing the tree during construction.

### Dependencies

- **C++ Standard Library**: Utilizes standard libraries such as `<vector>`, `<algorithm>`, and `<iostream>` for data handling and input/output operations.

### Usage

1. **Compilation**: Use a C++ compiler to compile the program. For example:
   ```bash
   g++ -o kdtree kdtree.cpp
   ```

2. **Execution**: Run the compiled program:
   ```bash
   ./kdtree
   ```

3. **Input/Output**: The program will prompt for input points and query points, then output the nearest neighbor for each query.

### Code Structure

- **KDTree Class**:
  - **Node Structure**: Represents each node in the tree with pointers to left and right children and the point stored at the node.
  - **Build Method**: Recursively constructs the KDTree by choosing median points to ensure balance.
  - **Nearest Neighbor Method**: Searches the tree to find the closest point to a given query using recursive traversal and backtracking.

- **Main Function**:
  - Reads input points and queries from standard input.
  - Constructs the KDTree with the input points.
  - Performs nearest neighbor searches for each query point and outputs the results.

### Example

```cpp
std::vector<std::pair<double, double>> points = {{2.0, 3.0}, {5.0, 4.0}, {9.0, 6.0}, {4.0, 7.0}, {8.0, 1.0}, {7.0, 2.0}};
KDTree tree(points);
auto nearest = tree.nearestNeighbor({9.0, 2.0});
std::cout << "Nearest neighbor: (" << nearest.first << ", " << nearest.second << ")\n";
```

### Notes

- Ensure that your input data is well-formatted and within valid ranges for best performance.
- The KDTree implementation assumes a static set of points; dynamic insertion or deletion is not supported in this version.
