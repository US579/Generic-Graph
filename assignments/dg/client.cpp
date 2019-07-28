#include "assignments/dg/graph.h"

#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <ostream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>
int main() {
  gdwg::Graph<std::string, double> g1;
  //  gdwg::Graph<int, int> g;
  // test for vector iterator constructor
  std::vector<std::string> v{"a", "b", "c", "d"};
  gdwg::Graph<std::string, double> b{v.begin(), v.end()};
  b.InsertEdge("a", "b", 1);
  // gdwg::Graph<std::string, double> aCopy{b};
  // aCopy.printG();
  //  b.printG();
  //  std::cout << b.InsertEdge("how", "how", 11) << '\n';
  //  std::cout << b.InsertEdge("how", "how", 11) << '\n';
  //  gdwg::Graph<char, std::string> x{'a', 'b', 'x', 'y'};
  b.InsertEdge("a", "c", 2);
  b.InsertEdge("a", "d", 3);
  b.InsertEdge("b", "c", 4);
  b.InsertEdge("b", "d", 5);
  b.InsertEdge("c", "d", 6);
  //  b.InsertEdge("a", "c", 2);
  //  b.InsertEdge("a", "d", 3);
  // gdwg::Graph<std::string, double> a = b;
  // a.printG();
  gdwg::Graph<std::string, double> o = std::move(b);
  gdwg::Graph<std::string, double> c = o;
  if ( c == o ){
    std::cout<< "cppppppppppppp" << "\n";
  }
  for (auto tup2 = o.crbegin(); tup2 != o.crend(); ++tup2) {
    std::cout << std::get<0>(*tup2) << "-" << std::get<1>(*tup2) << "-"
              << std::get<2>(*tup2) << "\n";
  }







  // o.printG();
  // b.printG();

  // // if (o == aCopy) {
  // std::cout << "appppppppppppppppp"

  //
  //  gdwg::Graph<std::string, int> g2{g};
  //
  //  std::cout << g2 << "\n";
  //
  //  // This is a structured binding.
  //  // https://en.cppreference.com/w/cpp/language/structured_binding
  //  // It allows you to unpack your tuple.
  //  for (const auto& [from, to, weight] : g) {
  //    std::cout << from << " -> " << to << " (weight " << weight << ")\n";
  //  }
}
//
// int main() {
//  gdwg::Graph<std::string, double> g1;
//  //  gdwg::Graph<int, int> g;
//  // test for vector iterator constructor
//  std::vector<std::string> v{"a", "b", "c", "d"};
//  gdwg::Graph<std::string, double> b{v.begin(), v.end()};
//  b.InsertEdge("a", "b", 1);
//  // gdwg::Graph<std::string, double> aCopy{b};
//  // aCopy.printG();
//  //  b.printG();
//  //  std::cout << b.InsertEdge("how", "how", 11) << '\n';
//  //  std::cout << b.InsertEdge("how", "how", 11) << '\n';
//  //  gdwg::Graph<char, std::string> x{'a', 'b', 'x', 'y'};
//  b.InsertEdge("a", "c", 2);
//  b.InsertEdge("a", "d", 3);
//  b.InsertEdge("b", "c", 4);
//  b.InsertEdge("b", "d", 5);
//  b.InsertEdge("c", "d", 6);
////  b.InsertEdge("a", "c", 2);
////  b.InsertEdge("a", "d", 3);
//  // gdwg::Graph<std::string, double> a = b;
//  // a.printG();
////  gdwg::Graph<std::string, double> o = std::move(b);
//  // o.printG();
//  // b.printG();
//
//  // // if (o == aCopy) {
//  // std::cout << "appppppppppppppppp"
//  //           << "\n";
//  // // }
//  // std::cout <<
////   auto tup1 = o.crbegin();
////  std::cout << std::get<0>(*tup1) << "-" << std::get<1>(*tup1) << "-"
////              << std::get<2>(*tup1) << "\n";
////
//
//
//
////  auto tup2 = o.cbegin();
////  std::cout << std::get<0>(*tup2) << "-" << std::get<1>(*tup2) << "-"
////            << std::get<2>(*tup2) << "\n";
////  ++tup2;
////  std::cout << std::get<0>(*tup2) << "-" << std::get<1>(*tup2) << "-"
////            << std::get<2>(*tup2) << "\n";
////  ++tup2;
////  std::cout << std::get<0>(*tup2) << "-" << std::get<1>(*tup2) << "-"
////            << std::get<2>(*tup2) << "\n";
////  --tup2;
////  std::cout << std::get<0>(*tup2) << "-" << std::get<1>(*tup2) << "-"
////            << std::get<2>(*tup2) << "\n";
//
//
//
//  for (auto tup2 = b.cbegin(); tup2 != b.cend(); ++tup2) {
//    std::cout << std::get<0>(*tup2) << "-" << std::get<1>(*tup2) << "-"
//              << std::get<2>(*tup2) << "\n";
//  }
////  auto tup2 = o.crbegin();
//  std::cout << std::get<0>(*tup2) << "-1111" << std::get<1>(*tup2) << "-"
//              << std::get<2>(*tup2) << "\n";
//
//  ++tup2;
//  std::cout << std::get<0>(*tup2) << "-222" << std::get<1>(*tup2) << "-"
//              << std::get<2>(*tup2) << "\n";
//  ++tup2;

//  ++tup2;
//  std::cout << std::get<0>(*tup2) << "-" << std::get<1>(*tup2) << "-"
//            << std::get<2>(*tup2) << "\n";

// // if (o == aCopy) {

//  gdwg::Graph<std::string, double> g1;
//  //  gdwg::Graph<int, int> g;
//  // test for vector iterator constructor
//  std::vector<std::string> v{"Hello", "how", "are", "you"};
//  gdwg::Graph<std::string, double> b{v.begin(), v.end()};
//  b.InsertEdge("you", "Hello", 11);
//  gdwg::Graph<std::string, double> aCopy{b};
//  //  aCopy.printG();
//  //  b.printG();
//  //  std::cout << b.InsertEdge("how", "how", 11) << '\n';
//  //  std::cout << b.InsertEdge("how", "how", 11) << '\n';
//  //  gdwg::Graph<char, std::string> x{'a', 'b', 'x', 'y'};
//  b.InsertEdge("Hello", "you", 11);
//  b.InsertEdge("you", "are", 11);
//  b.InsertEdge("you", "are", 2);
//  b.InsertEdge("you", "are", 34);
//  b.InsertEdge("you", "Hello", 11);
//  gdwg::Graph<std::string, double> a = b;
//  //  a.printG();
//  gdwg::Graph<std::string, double> o = b;
//  o.printG();
//  a.InsertEdge("you", "Hello", 199);
//  o.InsertEdge("you", "Hello", 199);
//  o.InsertNode("a");
//  a.InsertNode("a");
////  a.InsertEdge("you", "Hello", 12);
//  if (o == a) {
//    std::cout << "equal -----------------"
//              << "\n";
//  }
//  if ( o != a){
//    std::cout << "not equal ------------"
//              << "\n";
//  }
//
//  o.cbegin();
//  //  x.printG();
//  //  b.DeleteNode("Hello");
//  //  b.printG();
//  //  b.erase("you","are",11);
//  //  b.GetWeights("you","are");
//  //  b.Clear();
//  //  b.InsertNode("ads");
//  //  b.printG();
//  //  b.GetWeights("you");
//  // std::cout << b.InsertEdge("Hello", "how", 1.0) << '\n';
//
//  // std::cout << b.IsNode("ow") << '\n';
//
//  //   auto lis2 = b.GetNodes();
//  //   std::cout << "graph b2 is: \n";
//  // for (std::map<N, std::shared_ptr<Node>>::iterator it = mymap.begin();
//  //      it != mymap.end(); ++it)
//  //   std::cout << it->first << " => " << it->second << '\n';
//  // for (int i = 0; i < lis2.size(); ++i) {
//  //   std::cout << lis2[i] + " ";
//  // }
//  // std::cout << "\n";
//
//  // test for tuple iterator constructor
//  // std::string s1{"Hello"};
//  // std::string s2{"how"};
//  // std::string s3{"are"};
//  // auto e1 = std::make_tuple(s1, s2, 5.4);
//  // auto e2 = std::make_tuple(s2, s3, 7.6);
//  // auto e = std::vector<std::tuple<std::string, std::string, double>>{e1,
//  e2};
//  // gdwg::Graph<std::string, double> b1{e.begin(), e.end()};
//  // b1.printG();
//  // std::cout << b1.InsertEdge(s1, s2, 514) << "\n";
//  // std::vector<std::string> lis1 = b1.GetNodes();
//  // std::cout << "graph b1 is: \n";
//  // for (int i = 0; i < lis1.size(); ++i) {
//  //   std::cout << lis1[i] + " ";
//  // }
//  // std::cout << "\n";
//
//  // // test for copy constructor
//  // gdwg::Graph<std::string, double> b2{b1};
//  // std::vector<std::string> lis2 = b2.GetNodes();
//  // std::cout << "graph b2 is: \n";
//  // for (int i = 0; i < lis2.size(); ++i) {
//  //   std::cout << lis2[i] + " ";
//  // }
//  // std::cout << "\n";
//
//  // //  std::cout<<b.value()<<'\n';
//  // std::vector<std::string> a{"a", "how", "c", "you"};
//  // gdwg::Graph<std::string, int> p{a.begin(), a.end()};
//  // std::string u{"c"};
//  // std::cout << "InsertNode(a): " << p.InsertNode("a") << "\n";
//  // std::cout << "InsertNode(b): " << p.InsertNode("b") << "\n";
//
//  // p.InsertEdge("a", u, 1);
//  // std::cout << "IsNode(a): " << p.IsNode("a") << "\n";
//  // p.IsConnected("a", "c");
//  // std::cout << "IsConnected(a, c): " << p.IsConnected("a", "c") << "\n";
//  // std::cout << "IsConnected(how, c): " << p.IsConnected("how", "c") <<
//  "\n";
//
//  // std::vector<std::string> lis = p.GetNodes();
//  // // auto how = p.IsNode("how");
//  // // std::cout << how << "========";
//
//  // std::cout << "p.findNode(how)->getval()" << p.findNode("how")->getval()
//  //           << "\n";
//
//  // for (int i = 0; i < lis.size(); ++i) {
//  //   std::cout << lis[i] + " ";
//  // }
//  // std::cout << "\n";
//
//  // gdwg::Graph<char, std::string> z{'a', 'b', 'x', 'y'};
//  // auto li = z.GetNodes();
//  // for (int i = 0; i < li.size(); ++i) {
//  //   std::cout << li[i];
//  // }
////  // std::cout << "\n";
//}
