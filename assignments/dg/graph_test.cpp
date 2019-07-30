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
SCENARIO("delete one node from connected graph", "Graph<N, E>") {
  WHEN("the node need to delete connectd with another node") {
    gdwg::Graph<std::string, int> a;
    a.InsertNode("a");
    a.InsertNode("b");
    a.InsertEdge("a", "b", 8);
    THEN("the edge between tow connected node also be deleted") {
      REQUIRE(a.IsConnected("a", "b") == 1);
      a.DeleteNode("a");

      REQUIRE(a.IsNode("a") == 0);
      REQUIRE(a.IsNode("b") == 1);
      REQUIRE_THROWS_WITH(a.IsConnected("a", "b") == 0,
                          "Cannot call Graph::IsConnected if src or dst node "
                          "don't exist in the graph");
    }
  }
  WHEN("the node need to delete connectd with another node") {
    gdwg::Graph<std::string, int> a;
    a.InsertNode("a");
    a.InsertNode("b");
    a.InsertEdge("b", "a", 8);
    THEN("the edge between tow connected node also be deleted") {
      REQUIRE(a.IsConnected("a", "b") == 0);
      REQUIRE(a.IsConnected("b", "a") == 1);
      std::vector<std::string> v{"a"};
      REQUIRE(a.GetConnected("b") == v);
      a.DeleteNode("a");
      REQUIRE(a.IsNode("a") == 0);
      REQUIRE(a.IsNode("b") == 1);
      std::vector<std::string> v1;
      REQUIRE(a.GetConnected("b") == v1);
    }
  }
}

SCENARIO("erase method for connected graph", "Graph<N, E>") {
  WHEN("Deletes an edge from src to dst with weight w") {
    gdwg::Graph<std::string, int> a;
    a.InsertNode("a");
    a.InsertNode("b");
    a.InsertEdge("b", "a", 1);
    a.InsertEdge("b", "a", 2);
    a.InsertEdge("b", "a", 3);
    a.erase("b", "a", 2);
    THEN("only edges are not delete remains") {
      std::vector<std::string> v1{"a"};
      REQUIRE(a.GetConnected("b") == v1);
    }
    std::vector<int> v2{1, 3};
    REQUIRE(a.GetWeights("b", "a") == v2);
  }
}

// TODO(students): Fill this in.
SCENARIO("replace a node", "Graph<N, E>") {
  GIVEN("A Graph with simple edges") {
    std::vector<std::string> v{"a", "b", "c", "d"};
    gdwg::Graph<std::string, double> b{v.begin(), v.end()};
    b.InsertEdge("a", "b", 1);
    b.InsertEdge("a", "c", 2);
    b.InsertEdge("a", "d", 3);
    WHEN("replace a node not exist in the graph") {
      REQUIRE_THROWS_WITH(
          b.Replace("g", "b"),
          "Cannot call Graph::Replace on a node that doesn't exist");
    }
    WHEN("replace a node with a node already inside the graph") {
      REQUIRE_FALSE(b.Replace("a", "b"));
    }
    WHEN("replace a node with a node not in the graph") {
      REQUIRE(b.Replace("a", "f"));
      REQUIRE_FALSE(b.IsNode("a"));
      REQUIRE(b.IsConnected("f", "b"));
      REQUIRE((b.GetWeights("f", "b").at(0) == 1));
      REQUIRE(b.IsConnected("f", "c"));
      REQUIRE((b.GetWeights("f", "c").at(0) == 2));
      REQUIRE(b.IsConnected("f", "d"));
      REQUIRE((b.GetWeights("f", "d").at(0) == 3));
    }
  }
}
SCENARIO("merge 2 nodes", "Graph<N, E>") {
  GIVEN("A Graph with distinct edges") {
    std::vector<std::string> v{"a", "b", "c", "d"};
    gdwg::Graph<std::string, double> b{v.begin(), v.end()};
    b.InsertEdge("a", "b", 1);
    b.InsertEdge("a", "c", 2);
    b.InsertEdge("a", "d", 3);
    WHEN("either src node or dst node no in the graph") {
      REQUIRE_THROWS_WITH(b.MergeReplace("e", "a"),
                          "Cannot call Graph::MergeReplace on old or new data "
                          "if they don't exist in the graph");
      REQUIRE_THROWS_WITH(b.MergeReplace("a", "e"),
                          "Cannot call Graph::MergeReplace on old or new data "
                          "if they don't exist in the graph");
    }
    WHEN("merge node A and node B which both have egdes") {
      b.MergeReplace("a", "b");
      REQUIRE_FALSE(b.IsNode("a"));
      REQUIRE(b.IsConnected("b", "b"));
      REQUIRE((b.GetWeights("b", "b").at(0) == 1));
      REQUIRE(b.IsConnected("b", "c"));
      REQUIRE((b.GetWeights("b", "c").at(0) == 2));
      REQUIRE(b.IsConnected("b", "d"));
      REQUIRE((b.GetWeights("b", "d").at(0) == 3));
    }
  }
  GIVEN("A graph have same weights for some different nodes") {
    std::vector<std::string> v{"a", "b", "c", "d", "e"};
    gdwg::Graph<std::string, double> b{v.begin(), v.end()};
    b.InsertEdge("a", "b", 4);
    b.InsertEdge("a", "c", 4);
    b.InsertEdge("a", "d", 4);
    b.InsertEdge("b", "e", 4);
    b.InsertEdge("b", "d", 4);
    b.MergeReplace("a", "b");
    WHEN("merge 2 existing node a and b") {
      REQUIRE_FALSE(b.IsNode("a"));
      REQUIRE(b.IsConnected("b", "b"));
      REQUIRE((b.GetWeights("b", "b").at(0) == 4));
      REQUIRE((b.GetWeights("b", "b").size() == 1));
      REQUIRE(b.IsConnected("b", "c"));
      REQUIRE((b.GetWeights("b", "c").at(0) == 4));
      REQUIRE((b.GetWeights("b", "c").size() == 1));
      REQUIRE(b.IsConnected("b", "d"));
      REQUIRE((b.GetWeights("b", "d").at(0) == 4));
      REQUIRE((b.GetWeights("b", "d").size() == 1));
      REQUIRE(b.IsConnected("b", "e"));
      REQUIRE((b.GetWeights("b", "e").at(0) == 4));
      REQUIRE((b.GetWeights("b", "e").size() == 1));
    }
  }
}
