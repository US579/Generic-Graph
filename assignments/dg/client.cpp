#include <string>

#include <iostream>

#include "assignments/dg/graph.h"

int main() {
  gdwg::Graph<std::string, int> g1;
  gdwg::Graph<int, int> g;

  // test for vector iterator constructor
  std::vector<std::string> v{"Hello", "how", "are", "you"};
  gdwg::Graph<std::string, double> b{v.begin(), v.end()};

  // // test for tuple iterator constructor
  std::string s1{"Hello"};
  std::string s2{"how"};
  std::string s3{"are"};
  auto e1 = std::make_tuple(s1, s2, 5.4);
  auto e2 = std::make_tuple(s2, s3, 7.6);
  auto e = std::vector<std::tuple<std::string, std::string, double>>{e1, e2};
  gdwg::Graph<std::string, double> b1{e.begin(), e.end()};
  std::vector<std::string> lis1 = b1.GetNodes();
  for (int i = 0; i < lis1.size(); ++i) {
    std::cout << lis1[i] + "----";
  }
  std::cout << "\n";

  //  std::cout<<b.value()<<'\n';
  std::vector<std::string> a{"a", "how", "c", "you"};
  gdwg::Graph<std::string, int> p{a.begin(), a.end()};
  std::string u{"c"};
  p.InsertEdge("a", u, 1);
  std::cout<<p.IsNode("a")<<"\n";
  p.IsConnected("a","c");
  std::cout<<  p.IsConnected("a","c")<<"\n";
  
  std::vector<std::string> lis = p.GetNodes();
  // auto how = p.IsNode("how");
  // std::cout << how << "========";
  
  auto how = p.findNode("how");
  std::cout << how->getval() << "========\n";

  for (int i = 0; i < lis.size(); ++i) {
    std::cout << lis[i] + " ";
  }
  std::cout << "\n";

  gdwg::Graph<char, std::string> z{'a', 'b', 'x', 'y'};
  auto li = z.GetNodes();
  for (int i = 0; i < li.size(); ++i) {
    std::cout << li[i];
  }
  std::cout << "\n";
}
