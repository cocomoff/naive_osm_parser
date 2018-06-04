#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <deque>
#include <boost/multi_array.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/johnson_all_pairs_shortest.hpp>
#include <boost/graph/floyd_warshall_shortest.hpp>

using namespace std;

typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS,
                              boost::no_property, // vertex property
                              boost::property<boost::edge_weight_t, int> // edge property
                              > Graph;
typedef Graph::edge_property_type Weight;
typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
typedef std::pair<int, int> Edge;

int main() {
  // read from file
  // const int N = 7;
  // const int N = 5574;
  const int N = 1646;
  Graph g(N);
  ifstream ifs("edges.csv");
  std::string line;
  while (ifs && getline(ifs, line)) {
    int u, v;
    double l;
    sscanf(line.c_str(), "%d\t%d\t%lf", &u, &v, &l);

    auto nu = boost::vertex(u, g);
    auto nv = boost::vertex(v, g);
    boost::add_edge(nu, nv, Weight((int)l), g);
  }

  // johnson all pairs shortest paths
  typedef boost::multi_array<int, 2> array_type;
  array_type D(boost::extents[N][N]);
  boost::floyd_warshall_all_pairs_shortest_paths(g, D);

  // output
  for (int i = 0; i < N; i++) {
    for (int j = i + 1; j < N; j++) {
      cout << "d[" << i << "," << j << "]=" << D[i][j] << endl;
    }
  }
}
