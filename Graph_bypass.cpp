#include<iostream>
#include<vector>


typedef size_t Vertex;


class Graph{
public:
    Graph(size_t vertex_count, bool is_directed = 0) {
        vertex_count_ = vertex_count;
        is_directed_ = is_directed;
    }

    virtual std::vector<size_t> getNeighbors(Vertex v) const = 0;
    virtual void addEdge(Vertex v, Vertex u) = 0;

    size_t getVertexCount() const {
        return vertex_count_;
    }
    bool getIsDirected() const {
        return is_directed_;
    }
    size_t getEdgeCount() const {
        return edge_count_;
    }

protected:
    size_t edge_count_;
    size_t vertex_count_;
    bool is_directed_;

};


/*==============================================DerivedClasses============================================*/


class GraphAdjList: public Graph {
public:
    GraphAdjList(size_t vertex_count, const std::vector<std::vector<size_t>>& edge_matrix, bool is_directed = false)
        :Graph(vertex_count, is_directed) {
            if (edge_matrix.size() != vertex_count) {
                throw std::runtime_error("wrong matrix size");
            }
            for (int i = 0; i < vertex_count; ++i) {
                if (edge_matrix[i].size() != vertex_count) {
                    throw std::runtime_error("wrong time error");
                }
            }
            const size_t is_edge = -1;

            edge_count_ = 0;
            vertex_count_ = vertex_count;
            edge_list_ = std::vector<std::vector<Vertex>>(vertex_count);
            for (size_t i = 0; i < vertex_count_; ++i) {
                for (size_t j = 0; j < vertex_count_; ++j) {
                    if (edge_matrix[i][j] == is_edge) {
                        ++edge_count_;
                        edge_list_[i].push_back(j);
                    }
                }
            }
            edge_count_ /= 2;
        }

    void addEdge(Vertex v, Vertex u) override {
        if (v >= vertex_count_ || u >= vertex_count_) {
            throw std::runtime_error("Invalid vertex input");
        }
        if (is_directed_ == false) {
            for (auto neighbor : getNeighbors(u)) {
                if (neighbor == v) {
                    return;
                }
            }
            for (auto neighbor : getNeighbors(v)) {
                if (neighbor == u) {
                    return;
                }
            }
            edge_list_[u].push_back(v);
            edge_list_[v].push_back(u);
        } else {
            for (auto neighbor : getNeighbors(v)) {
                if (neighbor == u) {
                    return;
                }
            }
            edge_list_[v].push_back(u);
        }
    }

    std::vector<Vertex> getNeighbors(Vertex v) const override {
        return edge_list_[v];
    }

    std::vector<std::vector<Vertex>> getEdgeList() const {
        return edge_list_;
    }

private:
    std::vector<std::vector<Vertex>> edge_list_;
};


/*==============================================Functions=============================================*/


namespace GraphProcessing {

    enum VertexMark {WHITE, BLACK, GRAY};

    std::vector<VertexMark> dfsVisit(const Graph& g, Vertex v, std::vector<VertexMark>& color) {
        color[v] = GRAY;
        for (u : g.getNeighbors(v)) {
            if (color[u] == WHITE) {
                dfsVisit(g, u, color);
            }
        }
        color[v] = BLACK;
        return color;
    }

    size_t getCountOfVertexInOneComponent(const Graph& g, Vertex v) {
        size_t result = 0;
        std::vector<VertexMark> color(g.getVertexCount(), WHITE);
        dfsVisit(g, v, color);
        for (Vertex v = 0; v < g.getVertexCount(); ++v) {
            if (color[v] == BLACK) {
                ++result;
            }
        }
        return result;
    }

}


/*================================================main======================================*/


int main() {
    Vertex vertex_number, the_vertex;
    std::cin >> vertex_number >> the_vertex;

    std::vector<std::vector<Vertex>> edge_matrix;
    for (int i = 0; i < vertex_number; ++i) {
        edge_matrix.push_back(std::vector<Vertex>());
        for (int j = 0; j < vertex_number; ++j) {
            Vertex edge;
            std::cin >> edge;
            edge_matrix[i].push_back(edge);
        }
    }
    GraphAdjList g(vertex_number, edge_matrix);
    std::cout << GraphProcessing::getCountOfVertexInOneComponent(g, --the_vertex);
    return 0;
}
