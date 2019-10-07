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


/*==============================================DerivedClasses============================================*/


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

    std::vector<size_t> getNeighbors(Vertex v) const {
        return edge_list_[v];
    }

    std::vector<std::vector<size_t>> getEdgeList() const {
        return edge_list_;
    }

private:
    std::vector<std::vector<size_t>> edge_list_;
};


/*=============================================Functions=================================================*/


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
        for (size_t i = 0; i < g.getVertexCount(); ++i) {
            if (color[i] == BLACK) {
                ++result;
            }
        }
        return result;
    }

    std::vector<int> bfs(const GraphAdjList& g, Vertex v) {
        std::vector<int> distances(g.getVertexCount(), -1);
        std::vector<VertexMark> color(g.getVertexCount(), WHITE);
        std::queue<size_t> cur_vertexes;
        distances[v] = 0;
        cur_vertexes.push(v);
        color[v] = GRAY;
        while (!cur_vertexes.empty()) {
            size_t v = cur_vertexes.front();
            cur_vertexes.pop();
            for (size_t i = 0; i < g.getNeighbors(v).size(); ++i) {
                Vertex u = g.getNeighbors(v)[i];
                if (color[u] == WHITE) {
                    distances[u] = distances[v] + 1;
                    color[u] = GRAY;
                    cur_vertexes.push(u);
                }
            }
        }
        return distances;
    }

    void findShortestWay(const GraphAdjList& g, int cur_distance, std::vector<size_t>& way,
                                         Vertex u, const std::vector<int>& distances) {
        --cur_distance;
        for (int i = 0; i < g.getNeighbors(u).size(); ++i) {
            Vertex neighbor = g.getNeighbors(u)[i];
            if (cur_distance < 0) {
                return;
            }
            if (distances[neighbor] == cur_distance) {
                way.push_back(neighbor + 1);
                findShortestWay(g, cur_distance, way, neighbor, distances);
                break;
            }
        }
    }

    std::pair<int, std::vector<size_t>> shortestWayFromVToU(const GraphAdjList& g, Vertex v, Vertex u) {
        --u;
        --v;
        std::vector<int> distances = bfs(g, v);
        int min_distance = distances[u];
        std::vector<size_t> way;
        way.push_back(u + 1);
        findShortestWay(g, min_distance, way, u, distances);
        return std::make_pair(min_distance, way);
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

    GraphAdjList g(num_vertexes, false, edge_matrix);

    std::pair<int, std::vector<size_t>> result = GraphProcessing::shortestWayFromVToU(g, v, u);
    int min_distance = result.first;
    std::vector<size_t> way = result.second;
    std::cout << min_distance << "\n";
    if (min_distance == -1 || min_distance == 0) {
        return 0;
    }
    for (int i = way.size() - 1; i >= 0; --i) {
        std::cout << way[i] << " ";
    }
    return 0;
}
