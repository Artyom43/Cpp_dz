#include <iostream>
#include<vector>
#include <exception>

typedef size_t Vertex;

class Graph{
public:
    size_t getVertexCount() const;

protected:
    size_t vertex_count_;
    size_t edge_count_;
    bool is_directed_;

};


class GraphAdjMatrix: public Graph {
public:
    GraphAdjMatrix(size_t vertex_count, const std::vector<std::vector<int>>& edge_matrix, bool is_directed = 0) {
        if (edge_matrix.size() != vertex_count) {
            throw std::runtime_error("wrong matrix size");
        }
        for (int i =0; i < vertex_count; ++i) {
            if (edge_matrix_[i].size() != vertex_count) {
                throw std::runtime_error("wrong time error");
            }
        }
        vertex_count_ = vertex_count;
        edge_matrix_ = edge_matrix;
    }

    size_t getEdgeCount() {
        int result = 0;
        for (Vertex i = 0; i < vertex_count_; ++i) {
            for (Vertex j = 0; j < vertex_count_; ++j) {
                result += edge_matrix_[i][j];
            }
        }
        return result / 2;
    }


private:
    std::vector<std::vector<int>> edge_matrix_;
};


int main() {
    int vertex_count;
    std::cin >> vertex_count;
    std::vector<std::vector<int>> edge_matrix(vertex_count, std::vector<int>(vertex_count));

    for (Vertex i = 0; i < vertex_count; ++i) {
        for (Vertex j = 0; j < vertex_count; ++j) {
            std::cin >> edge_matrix[i][j];
        }
    }
    GraphAdjMatrix graph(vertex_count, edge_matrix);

    std::cout << graph.getEdgeCount();


    return 0;
}
