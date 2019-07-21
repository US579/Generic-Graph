#include <string>

#include <iostream>

#include "assignments/dg/graph.h"

int main() {
  gdwg::Graph<std::string, int> g1;
  gdwg::Graph<int, int> g;
  std::vector<std::string> v{"Hello", "how", "are", "you"};
  gdwg::Graph<std::string, double> b{v.begin(), v.end()};
  //  std::cout<<b.value()<<'\n';
  std::vector<std::string> a{"a", "how", "c", "you"};
  gdwg::Graph<std::string, int> p{a.begin(), a.end()};
  std::string u{"c"};
  p.InsertEdge("a", u, 1);
  //  std::cout<<p.IsNode("a")<<"\n";
  //  p.IsConnected("a","c");
  //  std::cout<<  p.IsConnected("a","c")<<"\n";
  std::vector<std::string> lis = p.GetNodes();
  for (int i = 0; i < lis.size(); ++i) {
    std::cout << lis[i] + " ";
  }
  gdwg::Graph<char, std::string> z{'a', 'b', 'x', 'y'};
  auto li = z.GetNodes();
  for (int i = 0; i < li.size(); ++i) {
    std::cout << li[i];
  }
}
