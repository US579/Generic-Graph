#ifndef ASSIGNMENTS_DG_GRAPH_H_
#define ASSIGNMENTS_DG_GRAPH_H_
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <vector>

namespace gdwg {

template <typename N, typename E> class Graph {
public:
  Graph() = default;
  Graph(const Graph &g);
  Graph(Graph &&g);
  ~Graph() = default;
  Graph(typename std::vector<N>::const_iterator first,
        typename std::vector<N>::const_iterator last);
  Graph(typename std::vector<std::tuple<N, N, E>>::const_iterator,
        typename std::vector<std::tuple<N, N, E>>::const_iterator);
  Graph(typename std::initializer_list<N>);

  class const_iterator {};
  class Node {
  public:
    Node(const N &v) {
      N newV = v;
      std::make_shared<N>(newV);
    }
    const N &getval() { return *this->val_; }

  private:
    std::shared_ptr<N> val_;
    std::vector<std::pair<std::weak_ptr<Node>, E>> edges_;
  };
  void printG();
  // std::map<N, std::shared_ptr<Node>> GetNodes();

private:
  std::map<N, std::shared_ptr<Node>> nodes_;
};

} // namespace gdwg

#include "assignments/dg/graph.tpp"

#endif // ASSIGNMENTS_DG_GRAPH_H_