#include <string>

#include "assignments/dg/graph.h"

int main() {
  // gdwg::Graph<std::string, int> g1;
  std::vector<std::string> v{"Hello", "how", "are", "you"};
  gdwg::Graph<std::string, double> b{v.begin(), v.end()};
}
