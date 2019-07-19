#ifndef ASSIGNMENTS_DG_GRAPH_H_
#define ASSIGNMENTS_DG_GRAPH_H_
#include <iterator>
#include <vector>

namespace gdwg {

template <typename N, typename E>
class Graph {
 public:
  class Node {
   public:
    Node(N n) : node_{std::make_shared<N>(n)} {}

   private:
    std::shared_ptr<N> node_;
  };
  class Edge {
   public:
   private:
    Node src;
    Node dst;
    std::shared_ptr<E> weight;
  };
  Graph<N, E>() = default;
  Graph<N, E>(typename std::vector<N>::const_iterator a, typename std::vector<N>::const_iterator b);

 private:
  std::vector<Node> nList;
  std::vector<Edge> eList;
  // std::vector<std::shared_ptr<N>> nList;
  // std::vector<std::shared_ptr<std::tuple<N, N, E>>> eList;
};

// Define your graph_iterator here
// Define your graph_const_iterator here

}  // namespace gdwg

#include "assignments/dg/graph.tpp"

#endif  // ASSIGNMENTS_DG_GRAPH_H_
