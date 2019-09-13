#include <iostream>
#include <fstream>
#include <vector>


class Graph {
public:
    Graph(size_t vertex_number, std::vector<std::vector<int>> ed_matrix) {
        vertex_number_ = vertex_number;
        ed_matrix_ = ed_matrix;
    }

    int numWays() {
        int sum = 0;
        for (int i = 0; i < vertex_number_; ++i) {
            for (int j = i; j < vertex_number_; ++j) {
                sum += ed_matrix_[i][j];
            }
        }
        return sum;
    }


private:
    size_t vertex_number_;
    std::vector<std::vector<int>> ed_matrix_;

};


int main() {
    std::ifstream ifst("INPUT.TXT");
    std::ofstream ofst("OUTPUT.TXT");

    int n;
    ifst >> n;
    std::vector<std::vector<int>> ed_matrix;
    for (int i = 0; i < n; ++i) {
        ed_matrix.push_back({});
        for (int j = 0; j < n; ++j) {
            int edge;
            ifst >> edge;
            ed_matrix[i].push_back(edge);
        }
    }
    Graph g(n, ed_matrix);
    ofst << g.numWays();
    return 0;
}
