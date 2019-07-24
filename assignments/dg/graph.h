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
  bool IsNode(const N &val);
  bool InsertNode(const N &val);
  bool InsertEdge(const N &src, const N &dst, const E &w);
  bool IsConnected(const N& src, const N& dst);

  class const_iterator {};
  class Node {
  public:
    Node(const N &v) {
      N newV = v;
      val_ = std::make_shared<N>(newV);
    }
    const N &getVal() { return *val_; }
    const std::vector<std::pair<std::weak_ptr<Node>, std::unique_ptr<E>>>
    getEdges() {
      return edges_;
    }

    const typename std::vector<E> getWeights(const N &dst) {
      std::vector<E> connected;
      // for (typename std::vector<std::pair<std::weak_ptr<Node>,
      // std::unique_ptr<E>>>::iterator
      for (auto it = edges_.begin(); it != edges_.end(); ++it) {
        if (it->first.lock()->getVal() == dst) {
          connected.push_back(*(it->second));
          // std::cout << it->first.lock()->getVal() << "\n";
        }
      }
      return connected;
    }

    bool isWeight(const N &dst, const E &w) {
      std::vector<E> connected = getWeights(dst);
      for (auto it = connected.begin(); it != connected.end(); ++it) {
        if (*it == w) {
          return true;
        }
      }
      return false;
    }
    bool InsertEdge(std::weak_ptr<Node> wDst, const E &w) {
      if (isWeight(wDst.lock()->getVal(), w) == false) {
        edges_.push_back(std::make_pair(wDst, std::make_unique<E>(w)));
      }
      return isWeight(wDst.lock()->getVal(), w);
    }

  private:
    std::shared_ptr<N> val_;
    std::vector<std::pair<std::weak_ptr<Node>, std::unique_ptr<E>>> edges_;
    // std::map<std::weak_ptr<Node>, E> edges_;
  };
  void printG();
  // std::map<N, std::shared_ptr<Node>> GetNodes();

private:
  std::map<N, std::shared_ptr<Node>> nodes_;
};

} // namespace gdwg

#include "assignments/dg/graph.tpp"

#endif // ASSIGNMENTS_DG_GRAPH_H_