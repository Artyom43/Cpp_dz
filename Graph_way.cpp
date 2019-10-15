#include<iostream>
#include<vector>
#include<queue>


typedef size_t Vertex;


class Graph{
public:
    Graph(size_t vertex_count, bool is_directed = 0) {
        vertex_count_ = vertex_count;
        is_directed_ = is_directed;
    }

    virtual std::vector<size_t> getNeighbors(Vertex v) const = 0;

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
            edge_count_ = 0;
            vertex_count_ = vertex_count;
            edge_list_ = std::vector<std::vector<Vertex>>(vertex_count);
            for (size_t i = 0; i < vertex_count_; ++i) {
                for (size_t j = 0; j < vertex_count_; ++j) {
                    if (edge_matrix[i][j] == 1) {
                        ++edge_count_;
                        edge_list_[i].push_back(j);
                    }
                }
            }
            edge_count_ /= 2;
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


/*=============================================Functions=================================================*/


namespace GraphProcessing{

    enum VertexMark {WHITE, BLACK, GRAY};

    const int no_way = -1;

    std::pair<std::vector<int>, std::vector<std::vector<Vertex>>> bfs(const Graph& g, Vertex v) {
        std::vector<int> distances(g.getVertexCount(), no_way);
        std::vector<VertexMark> color(g.getVertexCount(), WHITE);
        std::queue<Vertex> cur_vertexes;
        std::vector<std::vector<Vertex>> prevs(g.getVertexCount());
        distances[v] = 0;
        cur_vertexes.push(v);
        color[v] = GRAY;
        while (!cur_vertexes.empty()) {
            Vertex v = cur_vertexes.front();
            cur_vertexes.pop();
            for (Vertex u : g.getNeighbors(v)) {
                if (color[u] == WHITE) {
                    prevs[u].push_back(v);
                    distances[u] = distances[v] + 1;
                    color[u] = GRAY;
                    cur_vertexes.push(u);
                }
            }
        }
        return std::make_pair(distances, prevs);
    }

    std::vector<Vertex> shortestWay(const Graph& g, Vertex v, Vertex u) {
        auto bfs_return = bfs(g, v);
        std::vector<int> distances = bfs_return.first;
        std::vector<std::vector<Vertex>> prevs = bfs_return.second;
        int min_distance = distances[u];
        if (min_distance == no_way) {
            return std::vector<Vertex>(0);
        }
        std::vector<Vertex> way;
        way.push_back(u);
        while (u != v) {
            way.push_back(prevs[u][0]);
            u = prevs[u][0];
        }
        return way;
    }

}


/*==========================================main=====================================================*/


int main() {
    size_t num_vertexes;
    std::cin >> num_vertexes;
    std::vector<std::vector<size_t>> edge_matrix;

    for (int i = 0; i < num_vertexes; ++i) {
        edge_matrix.push_back(std::vector<size_t>());
        for (int j = 0; j < num_vertexes; ++j) {
            int edge;
            std::cin >> edge;
            edge_matrix[i].push_back(edge);
        }
    }

    Vertex v, u;
    std::cin >> v >> u;
    --v; --u;

    GraphAdjList g(num_vertexes, edge_matrix);

    std::vector<size_t> way = GraphProcessing::shortestWay(g, v, u);
    if (way.size() == 0) {
        std::cout << -1;
        return 0;
    }
    if (way.size() == 1) {
        std::cout << 0;
        return 0;
    }
    std::cout << (way.size() - 1) << "\n";
    for (int i = way.size() - 1; i >= 0; --i) {
        std::cout << (way[i] + 1) << " ";
    }
    return 0;
}
