#include<iostream>
#include<fstream>
#include<vector>

class Graph{
public:
    Graph(size_t numV, std::vector<std::pair<int, int>> edges) {
        _numV = numV;
        _degs = std::vector<int>(numV, 0);
        _edges = std::vector<std::vector<int>>(numV);
        for(auto edge : edges) {
            _edges[edge.first - 1].push_back(edge.second - 1);
            _edges[edge.second - 1].push_back(edge.first - 1);
            ++_degs[edge.second - 1];
            ++_degs[edge.first - 1];
        }
    }

    std::vector<int> getDegs() const {
        return _degs;
    }

private:
    size_t _numV;
    std::vector<std::vector<int>> _edges;
    std::vector<int> _degs;

};

int main() {
    std::ifstream ifst("INPUT.TXT");
    std::ofstream ofst("OUTPUT.TXT");
    size_t n,m;
    ifst >> n >> m;
    std::vector<std::pair<int, int>> edges(m);
    for (int i = 0; i < m; ++i) {
        ifst >> edges[i].first >> edges[i].second;
    }
    Graph g(n, edges);
    std::vector<int> degs = g.getDegs();
    for (auto deg : degs) {
        ofst << deg << " ";
    }

    return 0;
}
