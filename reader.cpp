#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
  ifstream ifs("edges.csv");
  std::string line;
  while (ifs && getline(ifs, line)) {
    int u, v;
    double l;
    sscanf(line.c_str(), "%d\t%d\t%lf", &u, &v, &l);
    cout << "d(" << u << "," << v << ")=" << l << endl;
  }
  return 0;
}
