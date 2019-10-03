#include<iostream>
#include<vector>

typedef size_t Vertex;

class Graph{
public:
    Graph(size_t vertex_count, bool is_directed = 0) {
        vertex_count_ = vertex_count;
        is_directed_ = is_directed;
    }

    size_t getVertexCount() const {
        return vertex_count_;
    }
    bool getIsDirected() const {
        return is_directed_;
    }

protected:
    size_t vertex_count_;
    bool is_directed_;

};


class GraphAdjList: public Graph {
public:
    GraphAdjList(size_t vertex_count, size_t is_directed, const std::vector<std::vector<size_t>>& edge_matrix)
        :Graph(vertex_count, is_directed) {
            edge_list_ = std::vector<std::vector<size_t>>(vertex_count);
            for (size_t i = 0; i < vertex_count_; ++i) {
                for (size_t j = 0; j < vertex_count_; ++j) {
                    if (edge_matrix[i][j] == 1) {
                        edge_list_[i].push_back(j);
                    }
                }
            }
    }

    std::vector<std::vector<size_t>> getEdgeList() const {
        return edge_list_;
    }

private:
    std::vector<std::vector<size_t>> edge_list_;
};


namespace GraphProcessing{

    enum VertexMark {WHITE, BLACK, GRAY};

    std::vector<VertexMark> dfsVisitV(const GraphAdjList& g, Vertex v, std::vector<VertexMark>& color) {
        color[v] = GRAY;
        for (size_t i = 0; i < g.getEdgeList()[v].size(); ++i) {
            size_t v_neighbor = g.getEdgeList()[v][i];
            if (color[v_neighbor] == WHITE) {
                dfsVisitV(g, v_neighbor, color);
            }
        }
        color[v] = BLACK;
        return color;
    }

    size_t getAdjVertexNumber (const GraphAdjList& g, Vertex v) {
        size_t result = 0;
        std::vector<VertexMark> color = std::vector<VertexMark>{g.getVertexCount(), WHITE};
        dfsVisitV(g, v, color);
        for (size_t v = 0; v < g.getVertexCount(); ++v) {
            if (color[v] == BLACK) {
                ++result;
            }
        }
        return result;
    }

}


int main() {
    size_t vertex_number, the_vertex;
    std::cin >> vertex_number >> the_vertex;

    std::vector<std::vector<size_t>> edge_matrix;
    for (int i = 0; i < vertex_number; ++i) {
        edge_matrix.push_back(std::vector<size_t>());
        for (int j = 0; j < vertex_number; ++j) {
            size_t have_edge;
            std::cin >> have_edge;
            edge_matrix[i].push_back(have_edge);
        }
    }
    GraphAdjList g(vertex_number, false, edge_matrix);
    std::cout << GraphProcessing::getAdjVertexNumber(g, --the_vertex);
    return 0;
}
