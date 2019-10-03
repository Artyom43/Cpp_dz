#include <iostream>
#include <vector>


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


class GraphAdjList: public Graph {
public:
    GraphAdjList(size_t vertex_count, std::vector<std::vector<Vertex>> edge_list, bool  is_directed_ = 0) {
        vertex_count_ = vertex_count;
        edge_list_ = edge_list;
    }

    std::vector<size_t> getDegs() {
        std::vector<size_t> result(vertex_count_, 0);
        for (int i =0; i < vertex_count_; ++i) {
            result[i] = edge_list_[i].size();
        }
        return result;
    }

private:
    std::vector<std::vector<Vertex>> edge_list_;
};


int main() {
    size_t vertex_count, m;
    std::cin >> vertex_count >> m;
    std::vector<std::vector<size_t>> edge_list(vertex_count);
    for (size_t i = 0; i < m; ++i) {
        size_t v1, v2;
        std::cin >> v1 >> v2;
        --v1;
        --v2;
        edge_list[v1].push_back(v2);
        edge_list[v2].push_back(v1);
    }

    GraphAdjList G(vertex_count, edge_list);

    std::vector<size_t> degs = G.getDegs();
    for (auto deg : degs) {
        std::cout << deg << " ";
    }


    return 0;
}
