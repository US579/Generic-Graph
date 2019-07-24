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
  class Node;
  Graph() = default;
  Graph(const Graph &);
  Graph(Graph &&);
  ~Graph() = default;
  Graph(typename std::vector<N>::const_iterator first,
        typename std::vector<N>::const_iterator last);
  Graph(typename std::vector<std::tuple<N, N, E>>::const_iterator,
        typename std::vector<std::tuple<N, N, E>>::const_iterator);
  Graph(typename std::initializer_list<N>);
  friend bool operator==(const gdwg::Graph<N, E>&, const gdwg::Graph<N, E>&);
  friend bool operator!=(const gdwg::Graph<N, E>&, const gdwg::Graph<N, E>&);
  typename std::map<N, std::shared_ptr<Graph<N, E>::Node>>::const_iterator
  begin() const;
  typename std::map<N, std::shared_ptr<Graph<N, E>::Node>>::const_iterator
  end() const;
  bool IsNode(const N &val);
  bool InsertNode(const N &val);
  bool InsertEdge(const N &src, const N &dst, const E &w);
  bool IsConnected(const N &src, const N &dst);
  bool DeleteNode(const N &node);
  void Clear();
  bool erase(const N &src, const N &dst, const E &w);
  std::vector<E> GetWeights(const N &src, const N &dst);
  void MergeReplace(const N &oldData, const N &newData);
  bool Replace(const N &oldData, const N &newData);
  Graph &operator=(const gdwg::Graph<N, E> &);
  Graph &operator=(gdwg::Graph<N, E> &&) noexcept;
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
    std::vector<std::pair<std::weak_ptr<Node>, std::shared_ptr<E>>> getEdge() {
      return edges_;
    }
    const typename std::vector<E> getWeights(const N &dst);
    bool isWeight(const N &dst, const E &w);
    bool InsertEdge(std::weak_ptr<Node> wDst, const E &w);
    void Replace(const N &newData) { val_ = std::make_shared<N>(newData); }
    bool deleteEdge(const std::shared_ptr<Node> &inEdge);
    bool deleteEdge(const N &inEdge, const E &w);


  private:
    std::shared_ptr<N> val_;
    std::vector<std::pair<std::weak_ptr<Node>, std::shared_ptr<E>>> edges_;
  };
  void printG();

private:

  std::map<N, std::shared_ptr<Node>> nodes_;
  mutable typename std::map<N, std::shared_ptr<Node>>::const_iterator Iter;
};

} // namespace gdwg

#include "assignments/dg/graph.tpp"

#endif // ASSIGNMENTS_DG_GRAPH_H_