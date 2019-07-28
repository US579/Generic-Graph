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
  b.InsertEdge("c", "d", 6);
  gdwg::Graph<std::string, double> o = std::move(b);
  // std::cout << o ;
  // for (auto it = o.crbegin(); it != o.crend(); ++it) {
  //   std::cout << std::get<0>(*it);
  // }

  for (auto tup1 = o.cbegin(); tup1 != o.cend(); ++tup1) {
    std::cout << std::get<0>(*tup1) << "-" << std::get<1>(*tup1) << "-"
              << std::get<2>(*tup1) << "\n";
    //         auto a = tup1;
    //         if (a != o.cbegin()) {
    //           --a;
    //  std::cout << std::get<0>(*a) << "-" << std::get<1>(*a) << "-"
    //         << std::get<2>(*a) << "\n";
    //         }
  }
  std::cout << "\n";

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