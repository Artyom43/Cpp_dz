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
        for (int i = 0; i < vertex_count; ++i) {
            if (edge_matrix[i].size() != vertex_count) {
                throw std::runtime_error("wrong time error");
            }
        }
        edge_count_ = 0;
        vertex_count_ = vertex_count;
        edge_matrix_ = std::vector<std::vector<int>> (vertex_count_, std::vector<int>(vertex_count_));
        for (size_t i = 0; i < vertex_count_; ++i) {
            for (size_t j = 0; j < vertex_count_; ++j) {
                if (edge_matrix[i][j] == 1) {
                    ++edge_count_;
                }
                edge_matrix_[i][j] = edge_matrix[i][j];
            }
        }
        edge_count_ /= 2;
    }

    size_t getEdgeCount() {
        return edge_count_;
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
