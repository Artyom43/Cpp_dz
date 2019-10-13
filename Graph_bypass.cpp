#include<iostream>
#include<vector>

typedef size_t Vertex;

class Graph{
public:
    Graph(Vertex vertex_count, bool is_directed = 0) {
        vertex_count_ = vertex_count;
        is_directed_ = is_directed;
    }

    virtual std::vector<Vertex> getNeighbors(Vertex v) const = 0;

    Vertex getVertexCount() const {
        return vertex_count_;
    }
    bool getIsDirected() const {
        return is_directed_;
    }

protected:
    Vertex vertex_count_;
    bool is_directed_;

};


class GraphAdjList: public Graph {
public:
    GraphAdjList(Vertex vertex_count, bool is_directed, const std::vector<std::vector<Vertex>>& edge_matrix)
        :Graph(vertex_count, is_directed) {
            edge_list_ = std::vector<std::vector<Vertex>>(vertex_count);
            for (Vertex i = 0; i < vertex_count_; ++i) {
                for (Vertex j = 0; j < vertex_count_; ++j) {
                    if (edge_matrix[i][j] == 1) {
                        edge_list_[i].push_back(j);
                    }
                }
            }
    }

    std::vector<Vertex> getNeighbors(Vertex v) const override{
        return edge_list_.at(v);
    }

    std::vector<std::vector<Vertex>> getEdgeList() const {
        return edge_list_;
    }

private:
    std::vector<std::vector<Vertex>> edge_list_;
};


namespace GraphProcessing{

    enum VertexMark {WHITE, BLACK, GRAY};

    std::vector<VertexMark> dfsVisitV(const Graph& g, Vertex v, std::vector<VertexMark>& color) {
        color[v] = GRAY;
        for (u : g.getNeighbors(v)) {
            if (color[u] == WHITE) {
                dfsVisitV(g, u, color);
            }
        }
        color[v] = BLACK;
        return color;
    }

    Vertex getCountOfVertexInOneComponent(const Graph& g, Vertex v) {
        size_t result = 0;
        std::vector<VertexMark> color = std::vector<VertexMark>{g.getVertexCount(), WHITE};
        dfsVisitV(g, v, color);
        for (Vertex v = 0; v < g.getVertexCount(); ++v) {
            if (color[v] == BLACK) {
                ++result;
            }
        }
        return result;
    }

}


int main() {
    Vertex vertex_number, the_vertex;
    std::cin >> vertex_number >> the_vertex;

    std::vector<std::vector<Vertex>> edge_matrix;
    for (int i = 0; i < vertex_number; ++i) {
        edge_matrix.push_back(std::vector<Vertex>());
        for (int j = 0; j < vertex_number; ++j) {
            Vertex have_edge;
            std::cin >> have_edge;
            edge_matrix[i].push_back(have_edge);
        }
    }
    GraphAdjList g(vertex_number, false, edge_matrix);
    std::cout << GraphProcessing::getCountOfVertexInOneComponent(g, --the_vertex);
    return 0;
}
