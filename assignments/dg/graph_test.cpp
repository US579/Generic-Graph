/*

  == Explanation and rational of testing ==

  Explain and justify how you approached testing, the degree
   to which you're certain you have covered all possibilities,
   and why you think your tests are that thorough.

*/

#include "assignments/dg/graph.h"
#include "catch.h"

// TODO(students): Fill this in.
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

// TODO(students): Fill this in.

SCENARIO("Constructor of the graph", "Graph<N, E>") {
  WHEN("Takes vecotr of strings to construct") {
    std::vector<std::string> v{"world", "need", "you"};
    gdwg::Graph<std::string, double> b{v.begin(), v.end()};
    THEN("all nodes insert into the Graph") {
      REQUIRE(b.IsNode("world") == 1);
      REQUIRE(b.IsNode("need") == 1);
      REQUIRE(b.IsNode("you") == 1);
      REQUIRE(b.IsNode("iron") == 0);
    }
  }
  WHEN("Takes vecotr of strings to construct") {
    std::string s1{"i"};
    std::string s2{"am"};
    std::string s3{"ironman"};
    auto e1 = std::make_tuple(s1, s2, 9.0);
    auto e2 = std::make_tuple(s2, s3, 8.2);
    auto e = std::vector<std::tuple<std::string, std::string, double>>{e1, e2};
    gdwg::Graph<std::string, double> b{e.begin(), e.end()};
    THEN("all nodes insert into the Graph and edge connect between them") {
      REQUIRE(b.IsNode("i") == 1);
      REQUIRE(b.IsNode("am") == 1);
      REQUIRE(b.IsNode("ironman") == 1);
      REQUIRE(b.IsNode("iron") == 0);
      REQUIRE(b.IsConnected(s1, s2) == 1);
      REQUIRE(b.IsConnected(s2, s3) == 1);
      REQUIRE(b.IsConnected(s1, s3) == 0);
      auto num1 = b.GetWeights("i", "am");
      auto num2 = b.GetWeights("am", "ironman");
      REQUIRE(num1[0] == 9.0);
      REQUIRE(num2[0] == 8.2);
    }
  }
  WHEN("Takes initializer_list to construct") {
    gdwg::Graph<char, std::string> s{'u', 'n', 's', 'w'};
    THEN("all nodes insert into the Graph and edge connect between them") {
      REQUIRE(s.IsNode('u') == 1);
      REQUIRE(s.IsNode('n') == 1);
      REQUIRE(s.IsNode('s') == 1);
      REQUIRE(s.IsNode('w') == 1);
    }
  }
  WHEN("use copy constructor") {
    gdwg::Graph<char, std::string> a{'u', 'n', 's', 'w'};
    gdwg::Graph<char, std::string> p{a};
    THEN("all nodes insert into the Graph and edge connect between them") {
      REQUIRE(p.IsNode('u') == 1);
      REQUIRE(p.IsNode('n') == 1);
      REQUIRE(p.IsNode('s') == 1);
      REQUIRE(p.IsNode('w') == 1);
      REQUIRE(a == p);
    }
  }
  WHEN("use move constructor") {
    gdwg::Graph<char, std::string> a{'u', 'n', 's', 'w'};
    gdwg::Graph<char, std::string> p{std::move(a)};
    THEN("all nodes insert into the Graph and edge connect between them") {
      REQUIRE(p.IsNode('u') == 1);
      REQUIRE(p.IsNode('n') == 1);
      REQUIRE(p.IsNode('s') == 1);
      REQUIRE(p.IsNode('w') == 1);
    }
  }
}

SCENARIO("Creation of Graph", "Graph<N, E>") {
  GIVEN("two identical Graphs without node") {
    gdwg::Graph<std::string, int> a;
    gdwg::Graph<std::string, int> b;
    WHEN("insert nodes and edges to the both graph") {
      a.InsertNode("a");
      a.InsertNode("b");
      b.InsertNode("a");
      b.InsertNode("b");
      a.InsertEdge("a", "b", 1);
      b.InsertEdge("a", "b", 1);
      THEN("get their weight and the two graph shold be the same") {
        auto num1 = a.GetWeights("a", "b");
        auto num2 = b.GetWeights("a", "b");
        REQUIRE(num1 == num2);
        REQUIRE(a == b);
      }
      THEN("compare two graphs if there are not same") {
        a.InsertEdge("a", "b", 2);
        REQUIRE(a != b);
        b.InsertEdge("a", "b", 2);
        REQUIRE(a == b);
        a.InsertNode("p");
        REQUIRE(a != b);
        b.InsertNode("p");
        REQUIRE(a == b);
        a.DeleteNode("p");
        b.DeleteNode("p");
        REQUIRE(a == b);
      }
    }
  }
}
