#include <iostream>
#include <vector>


typedef size_t Vertex;

class Graph{
public:
    Vertex getVertexCount() const;

protected:
    Vertex vertex_count_;
    size_t edge_count_;
    bool is_directed_;

};


class GraphAdjList: public Graph {
public:
    GraphAdjList(Vertex vertex_count, std::vector<std::vector<Vertex>> edge_list, bool  is_directed_ = 0) {
        vertex_count_ = vertex_count;
        edge_list_ = edge_list;
    }

    std::vector<Vertex> getDegs() {
        std::vector<Vertex> result(vertex_count_, 0);
        for (int i = 0; i < vertex_count_; ++i) {
            result[i] = edge_list_[i].size();
        }
        return result;
    }

private:
    std::vector<std::vector<Vertex>> edge_list_;
};


int main() {
    Vertex vertex_count, m;
    std::cin >> vertex_count >> m;
    std::vector<std::vector<Vertex>> edge_list(vertex_count);
    for (Vertex i = 0; i < m; ++i) {
        Vertex v1, v2;
        std::cin >> v1 >> v2;
        --v1;
        --v2;
        edge_list[v1].push_back(v2);
        edge_list[v2].push_back(v1);
    }

    GraphAdjList G(vertex_count, edge_list);

    std::vector<Vertex> degs = G.getDegs();
    for (auto deg : degs) {
        std::cout << deg << " ";
    }


    return 0;
}
