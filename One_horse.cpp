#include<iostream>
#include<vector>
#include<queue>
#include<map>


/*=============================================Vertex========================================================*/


class Vertex {
public:
    Vertex(size_t first, size_t second): pair(first, second) {}

    Vertex& operator=(const Vertex& v) {
        pair = v.pair;
    }

    std::pair<size_t, size_t> getPair() const {
        return pair;
    }

    size_t getFirst() const {
        return pair.first;
    }

    size_t getSecond() const {
        return pair.second;
    }

private:
    std::pair<size_t, size_t> pair;
};
std::ostream& operator<<(std::ostream& os, const Vertex& v) {
    os << v.getFirst() + 1 << " " << v.getSecond() + 1;
    return os;
}

class Cmp {
public:
    bool operator()(const Vertex& lhs, const Vertex& rhs) const{
        return (lhs.getFirst() > rhs.getFirst() ||
                lhs.getFirst() == rhs.getFirst() && lhs.getSecond() > rhs.getSecond());
    }
};


/*============================================Graph=========================================================*/


class Graph{
public:
    Graph(size_t vertex_count, bool is_directed = false): vertex_count_(vertex_count), is_directed_(is_directed) {}

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


/*============================================Derived_classes================================================*/


class GraphAdjList: public Graph {
public:
    GraphAdjList(size_t vertex_count, std::map<Vertex, std::vector<Vertex>, Cmp> edge_list,
                  bool is_directed = false): Graph(vertex_count, is_directed) {
        edge_list_ = edge_list;
    }

    std::vector<Vertex> getVertexes () const {
        std::map<Vertex, std::vector<Vertex>, Cmp>::const_iterator begin = edge_list_.begin();
        std::vector<Vertex> result;
        for (auto iter = begin; iter != edge_list_.end(); ++iter) {
            result.push_back(iter->first);
        }
        return result;
    }

    std::vector<Vertex> getNeighbors(const Vertex& v) const {
        return edge_list_.at(v);
    }

    std::map<Vertex, std::vector<Vertex>, Cmp> getEdgeList() const{
        return edge_list_;
    }

    void setNeighbor(const Vertex& v, const Vertex& u) {
        edge_list_[v].push_back(u);
    }

private:
    std::map<Vertex, std::vector<Vertex>, Cmp> edge_list_;
};


/*===========================================Graph_functions================================================*/


namespace GraphProcessing {
    enum VertexMark {WHITE, GRAY, BLACK};

    std::map<Vertex, int, Cmp> bfs(const GraphAdjList& g, const Vertex& v) {
        std::map<Vertex, int, Cmp> distances;
        std::map<Vertex, VertexMark, Cmp>  color;
        for (auto vertex : g.getVertexes()) {
            color[vertex] = WHITE;
            distances[vertex] = -1;
        }
        std::queue<Vertex> cur_vertexes;
        distances[v] = 0;
        cur_vertexes.push(v);
        color[v] = GRAY;
        while (!cur_vertexes.empty()) {
            Vertex u = cur_vertexes.front();
            cur_vertexes.pop();
            for (size_t i = 0; i < g.getNeighbors(u).size(); ++i) {
                Vertex k = g.getNeighbors(u)[i];
                if (color[k] == WHITE) {
                    distances[k] = distances[u] + 1;
                    color[k] = GRAY;
                    cur_vertexes.push(k);
                }
            }
        }
        return distances;
    }

    void findShortestWay(const GraphAdjList& g, int cur_distance, std::vector<Vertex>& way,
                                         const Vertex& u, const std::map<Vertex, int, Cmp>& distances) {
        --cur_distance;
        for (int i = 0; i < g.getNeighbors(u).size(); ++i) {
            Vertex neighbor = g.getNeighbors(u)[i];
            if (cur_distance < 0) {
                return;
            }
            if (distances.at(neighbor) == cur_distance) {
                way.push_back(neighbor);
                findShortestWay(g, cur_distance, way, neighbor, distances);
                break;
            }
        }
    }

    std::pair<int, std::vector<Vertex>> shortestWayFromVToU(const GraphAdjList& g, const Vertex& v, const Vertex& u) {
        std::map<Vertex, int, Cmp> distances = bfs(g, v);
        int min_distance = distances[u];
        std::vector<Vertex> way;
        way.push_back(u);
        findShortestWay(g, min_distance, way, u, distances);
        return std::make_pair(min_distance, way);
    }

}


/*==========================================Non-graph_functions==============================================*/


std::map<Vertex, std::vector<Vertex>, Cmp> makeAdjListFromChessTable(size_t size) {
    std::map<Vertex, std::vector<Vertex>, Cmp> edge_list;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            Vertex v{i, j};
            edge_list[v] = std::vector<Vertex>();
            if (i + 1 < size && j + 2 < size) {
                edge_list[v].push_back({i + 1, j + 2});
            }
            if (i + 2 < size && j + 1 < size) {
                edge_list[v].push_back({i + 2, j + 1});
            }
            if (i + 2 < size && j - 1 >= 0) {
                edge_list[v].push_back({i + 2, j - 1});
            }
            if (i + 1 < size && j - 2 >= 0) {
                edge_list[v].push_back({i + 1, j - 2});
            }
            if (i - 1 >= 0 && j - 2 >= 0) {
                edge_list[v].push_back({i - 1, j - 2});
            }
            if (i - 2 >= 0 && j - 1 >= 0) {
                edge_list[v].push_back({i - 2, j - 1});
            }
            if (i - 2 >= 0 && j + 1 < size) {
                edge_list[v].push_back({i - 2, j + 1});
            }
            if (i - 1 >= 0 && j + 2 < size) {
                edge_list[v].push_back({i - 1, j + 2});
            }
        }
    }
    return edge_list;
}


/*=================================================main======================================================*/

int main() {
    size_t table_size;
    std::cin >> table_size;
    size_t x1, y1, x2, y2;
    std::cin >> x1 >> y1 >> x2 >> y2;

    GraphAdjList g(table_size, makeAdjListFromChessTable(table_size));

    int min_distance = GraphProcessing::shortestWayFromVToU(g, {x1 - 1, y1 - 1}, {x2 - 1, y2 - 1}).first;
    std::vector<Vertex> way = GraphProcessing::shortestWayFromVToU(g, {x1 - 1, y1 - 1}, {x2 - 1, y2 - 1}).second;


    std::cout << min_distance << "\n";
    if (min_distance == -1 || min_distance == 0) {
        return 0;
    }
    for (int i = way.size() - 1; i >= 0; --i) {
        std::cout << way[i] << "\n";
    }
    return 0;
}

