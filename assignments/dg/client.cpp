#include "assignments/dg/graph.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <ostream>
#include <tuple>
#include <utility>
#include <vector>

int main() {
  std::vector<std::string> v{"a", "b", "c", "d", "e"};
  gdwg::Graph<std::string, double> b{v.begin(), v.end()};
  b.InsertEdge("a", "b", 1);
  b.InsertEdge("a", "c", 2);
  b.InsertEdge("a", "d", 3);
  b.InsertEdge("b", "c", 4);
  b.InsertEdge("b", "d", 5);
  b.InsertEdge("c", "c", 6);
  b.InsertEdge("c", "d", 8);
  // b.InsertEdge("e", "c", 8);
  // b.InsertEdge("e", "c", 9);
  // b.InsertEdge("e", "c", 10);
  // b.InsertEdge("e", "b", 8);
  // b.DeleteNode("a");
  // b.InsertNode("a");
  // gdwg::Graph<std::string, double> o = std::move(b);
  // std::cout<< b;

  for (auto tup1 = b.cbegin(); tup1 != b.cend(); ++tup1) {
    std::cout << std::get<0>(*tup1) << "-" << std::get<1>(*tup1) << "-"
              << std::get<2>(*tup1) << "\n";
  }
  return 0;
  auto tup1 = b.end();
  --tup1;
  // ++tup1;
  // ++tup1;

  // std::cout << std::get<0>(*tup1) << "-" << std::get<1>(*tup1) << "-"
  //   << std::get<2>(*tup1) << ":";
  do {
    std::cout << std::get<0>(*tup1) << "---" << std::get<1>(*tup1) << std::endl;
    //           << std::get<2>(*tup1) << "\n";
    --tup1;
  } while (tup1 != b.begin());
  return 0;

  // for (auto it = b.cend(); it != b.cbegin();) {
  //   --it;
  //   std::cout << std::get<0>(*it) << "-" << std::get<1>(*it) <<
  //   std::get<2>(*it)
  //             << "\n";
  // }
  // for (auto tup1 = o.cbegin(); tup1 != o.cend(); ++tup1) {
  //   // std::cout << std::get<0>(*tup1) << "-" << std::get<1>(*tup1) << "-"
  //   //           << std::get<2>(*tup1) << ":";
  // }
  // std::cout << "\n";
  // for (auto e : o.GetWeights("a", "c")) {
  //   std::cout << e;
  // }
  // o.GetWeights("a", "b");
  // o.GetWeights("a", "c");
  // o.GetWeights("a", "d");
  // o.GetWeights("b", "c");
  // o.GetWeights("b", "d");
  // auto a = o.cend();
  // --a;
  // //  std::cout << std::get<0>(*a) << "-" << std::get<1>(*a) << "-"
  // //         << std::get<2>(*a) << "\n";
  // --a;
  // std::cout << std::get<0>(*a) << "-" << std::get<1>(*a) << "-"
  //           << std::get<2>(*a) << "\n";
  // for (auto it = o.cend(); it != o.cbegin();) {
  //   --it;
  //   std::cout << std::get<0>(*it) << "-" << std::get<1>(*it) << "\n";
  //   // for (auto e : o.GetWeights(std::get<0>(*it), std::get<1>(*it))) {
  //   //   std::cout << e;
  //   // }
  //   // std::cout << std::get<0>(*it) << "-" << std::get<1>(*it) << "-"
  //   //           << std::get<2>(*it) << "\n";
  // }
  // std::cout << "\n";

  // for (auto tup1 = o.cbegin(); tup1 != o.cend(); ++tup1) {
  //   std::cout << std::get<0>(*tup1) << "-" << std::get<1>(*tup1) << "-"
  //             << std::get<2>(*tup1) << "\n";
  // }
  // auto a = o.end();
  // --a;
  // for (auto tup2 = o.rbegin(); tup2 != o.rend(); ++tup2) {
  //   std::cout << std::get<0>(*tup2) << "-" << std::get<1>(*tup2) << "-"
  //             << std::get<2>(*tup2) << "\n";
  // }
}