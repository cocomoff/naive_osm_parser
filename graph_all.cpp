#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <deque>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/johnson_all_pairs_shortest.hpp>

using namespace std;

typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS,
                              boost::no_property, // vertex property
                              boost::property<boost::edge_weight_t, int> // edge property
                              > Graph;
typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
typedef std::pair<int, int> Edge;
const int N = 7; // 5574;

int main() {
  // info
  vector<Edge> edges;
  vector<int> weights;

  // read from file
  ifstream ifs("small_edges.csv");
  std::string line;
  while (ifs && getline(ifs, line)) {
    int u, v;
    double l;
    sscanf(line.c_str(), "%d\t%d\t%lf", &u, &v, &l);
    edges.push_back(make_pair(u, v));
    weights.push_back((int)l);
  }

  // build boost Graph
  Graph g(edges.begin(), edges.end(), weights.begin(), N);

  // johnson all pairs shortest paths
  vector<int> d(N, (std::numeric_limits<int>::max)());
  // int D[N][N];
  int **D;
  D = (int**)malloc(sizeof(int*) * N);
  for (int i = 0; i < N; i++) {
    D[i] = (int *)malloc(sizeof(int) * N);
  }
  johnson_all_pairs_shortest_paths(g, D, boost::distance_map(&d[0]));

  // output
  for (int i = 0; i < N; ++i) {
    std::cout << std::setw(3) << i << " -> ";
    for (int j = 0; j < N; ++j) {
      if (D[i][j] == (std::numeric_limits<int>::max)())
        std::cout << std::setw(5) << "inf";
      else
        std::cout << std::setw(5) << D[i][j];
    }
    std::cout << std::endl;
  }
}
