#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <deque>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

using namespace std;

typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS,
                              boost::no_property, // vertex property
                              boost::property<boost::edge_weight_t, int> // edge property
                              > Graph;
typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
typedef std::pair<int, int> Edge;
const int N = 5574;

int main() {
  // info
  vector<Edge> edges;
  vector<int> weights;

  // read from file
  ifstream ifs("edges.csv");
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

  // dijkstra shortest path
  const Vertex from = 5000;
  const Vertex to = 4000;
  const int nG = boost::num_vertices(g);
  vector<Vertex> parents(nG);
  vector<size_t> distance(nG);
  boost::dijkstra_shortest_paths(g, from,
                                 boost::predecessor_map(&parents[0]).distance_map(&distance[0]));

  // length
  cout << "route length:" << (distance[to]) << endl;
  
  std::deque<Vertex> route;
  for (Vertex v = to; v != from; v = parents[v])
    route.push_front(v);
  for (const Vertex v: route)
    cout << v << endl;
  return 0;
}
