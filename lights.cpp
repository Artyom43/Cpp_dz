#include <iostream>
#include<vector>

class Graph{
public:
    typedef size_t Vertex;

    size_t getVertexCount() const;
    virtual void addEdge(const Vertex& start, const Vertex& finish) {
        ++edge_count_;
    }


protected:
    size_t vertex_count_; //get
    size_t edge_count_;   //get
    bool is_directed_;    //get

};


class GraphAdjMatrix: public Graph {
public:
    GraphAdjMatrix(size_t vertex_count, const std::vector<std::vector<int>>& edge_matrix, bool is_directed = 0) {
        vertex_count_ = vertex_count;
        edge_matrix_ = edge_matrix;
    }

    size_t getEdgeCount() {
        int result = 0;
        for (int i = 0; i < vertex_count_; ++i) {
            for (int j = 0; j < vertex_count_; ++j) {
                result += edge_matrix_[i][j];
            }
        }
        return result / 2;
    }


private:
    std::vector<std::vector<int>> edge_matrix_;
};


int main() {
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> edge_matrix(n, std::vector<int>(n));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> edge_matrix[i][j];
        }
    }
    GraphAdjMatrix G(n, edge_matrix, false);

    std::cout << G.getEdgeCount();


    return 0;
}
