#ifndef ASSIGNMENTS_DG_GRAPH_H_
#define ASSIGNMENTS_DG_GRAPH_H_
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <vector>

namespace gdwg {
template <typename N, typename E>
class Graph {
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

  friend bool operator==(const gdwg::Graph<N, E> &a,
                         const gdwg::Graph<N, E> &b) {
    if (a.nodes_.size() != b.nodes_.size()) {
      return false;
    }
    for (auto &n : a.nodes_) {
      if (b.nodes_.find(n.first) == b.nodes_.end()) {
        return false;
      }
    }
    int cout = 0;
    int cout1 = 0;
    for (auto &n : a.nodes_) {
      auto bNode = b.nodes_.at(n.first);
      cout += bNode->getEdges().size();
      cout1 += (n.second)->getEdges().size();
    }
    if (cout1 != cout)
      return false;
    for (auto &n : a.nodes_) {
      auto bNode = b.nodes_.at(n.first);
      for (int i = 0; i < bNode->getEdges().size(); ++i) {
        if (*(bNode->getEdges()[i].second) !=
                *((n.second)->getEdges()[i].second) ||
            bNode->getEdges()[i].first.lock()->getVal() !=
                (n.second)->getEdges()[i].first.lock()->getVal()) {
          return false;
        }
      }
    }
    return true;
  }

  friend bool operator!=(const gdwg::Graph<N, E> &a,
                         const gdwg::Graph<N, E> &b) {
    return !(a == b);
  }

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



  class Node {
  public:
    Node(const N &v) {
      N newV = v;
      val_ = std::make_shared<N>(newV);
    }
    const N &getVal() { return *val_; }

    std::vector<std::pair<std::weak_ptr<Node>, std::shared_ptr<E>>> getEdges() {
      return edges_;
    }
    const typename std::vector<E> getWeights(const N &dst);
    bool isWeight(const N &dst, const E &w);
    bool InsertEdge(std::weak_ptr<Node> wDst, const E &w);
    void Replace(const N &newData) { val_ = std::make_shared<N>(newData); }
    bool deleteEdge(const std::shared_ptr<Node> &inEdge);
    bool deleteEdge(const N &inEdge, const E &w);

  private:
    friend class const_iterator;
    std::shared_ptr<N> val_;
    std::vector<std::pair<std::weak_ptr<Node>, std::shared_ptr<E>>> edges_;
  };

  void printG();

  class const_iterator {
  public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = std::tuple<N, N, E>;
    using reference = std::tuple<const N &, const N &, const E &>;
    using pointer = std::tuple<const N *, const N *, const E *>;
    using difference_type = int;
    friend bool operator==(const Graph<N, E>::const_iterator& lhs, const const_iterator& rhs);
    friend bool operator!=(const Graph<N, E>::const_iterator& lhs, const Graph<N, E>::const_iterator& rhs) { return !(lhs == rhs); }


    reference operator*() const {
      // std::cout << outer_->first << inner_->first.lock()->getVal() <<
      // inner_->second << "\n";

      return {outer_->first, inner_->first.lock()->getVal(), *(inner_->second)};
    }

    const_iterator &operator++();
    const_iterator operator++(int) {
      auto copy{*this};
      ++(*this);
      return copy;
    }
    const_iterator &operator--();
    const_iterator operator--(int) {
      auto copy{*this};
      ++(*this);
      return copy;
    }

  private:
    friend class Node;
    typename std::map<N, std::shared_ptr<Node>>::iterator outer_;
    const typename std::map<N, std::shared_ptr<Node>>::iterator sentinel_;
    typename std::vector<
        std::pair<std::weak_ptr<Node>, std::shared_ptr<E>>>::iterator inner_;

  public:
    const_iterator(const decltype(outer_) &outer,
                   const decltype(sentinel_) &sentinel,
                   const decltype(inner_) &inner)
        : outer_{outer}, sentinel_{sentinel}, inner_{inner} {
      std::cout << outer_->first << "\n"
                << inner_->first.lock()->getVal() << "\n"
                << *(inner_->second) << "\n";
    }
  };
  const_iterator cbegin();
  const_iterator begin();
  const_iterator cend();


private:
  std::map<N, std::shared_ptr<Node>> nodes_;
  mutable typename std::map<N, std::shared_ptr<Node>>::const_iterator Iter;
};

} // namespace gdwg

#include "assignments/dg/graph.tpp"

#endif // ASSIGNMENTS_DG_GRAPH_H_