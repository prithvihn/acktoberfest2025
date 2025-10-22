#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <tuple>


// 1. DISJOINT SET UNION (DSU) CLASS

class DSU {
private:
    std::vector<int> parent;
    std::vector<int> rank;

public:
    DSU(int n) {
        parent.resize(n);
        std::iota(parent.begin(), parent.end(), 0); 
        rank.assign(n, 0); 
    }

    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]);
    }

    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);

        if (root_i != root_j) {
            if (rank[root_i] < rank[root_j]) {
                parent[root_i] = root_j;
            } else if (rank[root_i] > rank[root_j]) {
                parent[root_j] = root_i;
            } else {
                parent[root_j] = root_i;
                rank[root_i]++;
            }
            return true; 
        }
        return false; 
    }
};


// 2. TEMPLATED KRUSKAL'S ALGORITHM FUNCTION


template <typename T>
T kruskal_mst(int num_nodes, std::vector<std::tuple<T, int, int>>& edges,
              std::vector<std::tuple<T, int, int>>& mst_edges) {

    // 1. Sort the edges by weight (ascending order)
    std::sort(edges.begin(), edges.end());

    // 2. Initialize the DSU structure
    DSU dsu(num_nodes);
    T mst_weight = 0;
    int edges_count = 0;

    // 3. Iterate through sorted edges and build the MST
    for (const auto& edge : edges) {
        const auto& [weight, u, v] = edge;

        if (dsu.unite(u, v)) {
            // No cycle: include the edge in the MST
            mst_edges.push_back(edge);
            mst_weight += weight;
            edges_count++;

            // Optimization: MST is complete when it has V-1 edges
            if (edges_count == num_nodes - 1) {
                break;
            }
        }
    }

    if (edges_count < num_nodes - 1) {
        std::cerr << "Warning: Graph is disconnected. MST could not span all nodes." << std::endl;
    }

    return mst_weight;
}


// 3. MAIN DRIVER CODE

int main() {
    const int N = 5; 

    std::vector<std::tuple<int, int, int>> graph_edges = {
        {10, 0, 1},
        {6,  0, 2},
        {5,  0, 3},
        {15, 1, 3},
        {4,  2, 3},
        {4,  2, 4},
        {20, 3, 4}
    };

    std::vector<std::tuple<int, int, int>> mst_result;

    int total_weight = kruskal_mst(N, graph_edges, mst_result);

    std::cout << "--- Kruskal's MST (Modern C++ Implementation) ---\n";
    std::cout << "Total Nodes: " << N << "\n";
    std::cout << "MST Total Weight: " << total_weight << "\n\n";

    std::cout << "Edges in the Minimum Spanning Tree:\n";
    for (const auto& edge : mst_result) {
        const auto& [w, u, v] = edge;
        std::cout << "(" << u << " -- " << v << ") with weight " << w << "\n";
    }
    
    std::cout << "\n--- Example with Double Weights ---\n";
    std::vector<std::tuple<double, int, int>> double_edges = {
        {1.5, 0, 1},
        {0.8, 1, 2},
        {2.2, 0, 2}
    };
    std::vector<std::tuple<double, int, int>> mst_double_result;
    double double_weight = kruskal_mst(3, double_edges, mst_double_result);
    
    std::cout << "MST Total Weight (Double): " << double_weight << "\n";


    return 0;
}#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <tuple>

// 1. DISJOINT SET UNION (DSU) CLASS

class DSU {
private:
    std::vector<int> parent;
    std::vector<int> rank;

public:
    DSU(int n) {
        parent.resize(n);
        std::iota(parent.begin(), parent.end(), 0); 
        rank.assign(n, 0); 
    }

    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]);
    }

    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);

        if (root_i != root_j) {
            if (rank[root_i] < rank[root_j]) {
                parent[root_i] = root_j;
            } else if (rank[root_i] > rank[root_j]) {
                parent[root_j] = root_i;
            } else {
                parent[root_j] = root_i;
                rank[root_i]++;
            }
            return true; 
        }
        return false; 
    }
};


// 2. TEMPLATED KRUSKAL'S ALGORITHM FUNCTION


template <typename T>
T kruskal_mst(int num_nodes, std::vector<std::tuple<T, int, int>>& edges,
              std::vector<std::tuple<T, int, int>>& mst_edges) {

    // 1. Sort the edges by weight (ascending order)
    std::sort(edges.begin(), edges.end());

    // 2. Initialize the DSU structure
    DSU dsu(num_nodes);
    T mst_weight = 0;
    int edges_count = 0;

    // 3. Iterate through sorted edges and build the MST
    for (const auto& edge : edges) {
        const auto& [weight, u, v] = edge;

        if (dsu.unite(u, v)) {
            // No cycle: include the edge in the MST
            mst_edges.push_back(edge);
            mst_weight += weight;
            edges_count++;

            // Optimization: MST is complete when it has V-1 edges
            if (edges_count == num_nodes - 1) {
                break;
            }
        }
    }

    if (edges_count < num_nodes - 1) {
        std::cerr << "Warning: Graph is disconnected. MST could not span all nodes." << std::endl;
    }

    return mst_weight;
}


// 3. MAIN DRIVER CODE

int main() {
    const int N = 5; 

    std::vector<std::tuple<int, int, int>> graph_edges = {
        {10, 0, 1},
        {6,  0, 2},
        {5,  0, 3},
        {15, 1, 3},
        {4,  2, 3},
        {4,  2, 4},
        {20, 3, 4}
    };

    std::vector<std::tuple<int, int, int>> mst_result;

    int total_weight = kruskal_mst(N, graph_edges, mst_result);

    std::cout << "--- Kruskal's MST (Modern C++ Implementation) ---\n";
    std::cout << "Total Nodes: " << N << "\n";
    std::cout << "MST Total Weight: " << total_weight << "\n\n";

    std::cout << "Edges in the Minimum Spanning Tree:\n";
    for (const auto& edge : mst_result) {
        const auto& [w, u, v] = edge;
        std::cout << "(" << u << " -- " << v << ") with weight " << w << "\n";
    }
    
    std::cout << "\n--- Example with Double Weights ---\n";
    std::vector<std::tuple<double, int, int>> double_edges = {
        {1.5, 0, 1},
        {0.8, 1, 2},
        {2.2, 0, 2}
    };
    std::vector<std::tuple<double, int, int>> mst_double_result;
    double double_weight = kruskal_mst(3, double_edges, mst_double_result);
    
    std::cout << "MST Total Weight (Double): " << double_weight << "\n";


    return 0;
}
