/*

  == Explanation and rational of testing ==

  Explain and justify how you approached testing, the degree
   to which you're certain you have covered all possibilities,
   and why you think your tests are that thorough.

*/
#include "assignments/dg/graph.h"
#include "catch.h"
#include <string>

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