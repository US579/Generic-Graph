#ifndef ASSIGNMENTS_DG_GRAPH_H_
#define ASSIGNMENTS_DG_GRAPH_H_
#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <ostream>
#include <tuple>
#include <utility>
#include <vector>

namespace gdwg {
template <typename N, typename E> class Graph {
public:
  class Node;
  class const_iterator;
  // class const_reverse_iterator;
  struct CustomCmp;
  // 2.1 Constructors & Destructors
  Graph() = default;
  Graph(typename std::vector<N>::const_iterator,
        typename std::vector<N>::const_iterator);
  Graph(typename std::vector<std::tuple<N, N, E>>::const_iterator,
        typename std::vector<std::tuple<N, N, E>>::const_iterator);
  Graph(typename std::initializer_list<N>);
  Graph(const Graph &);
  Graph(Graph &&) noexcept;
  ~Graph() = default;
  // 2.2. Operations
  Graph &operator=(const gdwg::Graph<N, E> &);
  Graph &operator=(gdwg::Graph<N, E> &&) noexcept;
  // 2.3. Methods
  bool InsertNode(const N &val);
  bool InsertEdge(const N &src, const N &dst, const E &w);
  bool DeleteNode(const N &node);
  bool Replace(const N &oldData, const N &newData);
  void MergeReplace(const N &oldData, const N &newData);
  void Clear();
  bool IsNode(const N &val);
  bool IsConnected(const N &src, const N &dst);
  void printG();
  std::vector<N> GetNodes();
  std::vector<N> GetConnected(const N &src);
  std::vector<E> GetWeights(const N &src, const N &dst);
  const_iterator find(const N &, const N &, const E &);
  bool erase(const N &src, const N &dst, const E &w);
  const_iterator erase(const_iterator it);
  const_iterator cbegin();
  const_iterator begin() { return cbegin(); }
  const_iterator cend();
  const_iterator end() { return cend(); }
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;
  const_reverse_iterator rbegin() { return crbegin(); }
  const_reverse_iterator rend() { return crend(); }
  const_reverse_iterator crbegin() { return const_reverse_iterator{cend()}; }
  const_reverse_iterator crend() { return const_reverse_iterator{cbegin()}; }

  // 2.4. Friends
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
      for (auto i = 0; i < static_cast<int>(bNode->getEdges().size()); ++i) {
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
  friend std::ostream &operator<<(std::ostream &o, gdwg::Graph<N, E> &g) {
    auto it = g.begin();
    for (auto node = g.nodes_.begin(); node != g.nodes_.end(); ++node) {
      o << node->first << " (\n";
      node->second->sort();
      for (auto i = 0; i < static_cast<int>(node->second->getEdges().size());
           ++i) {
        o << "  " << std::get<1>(*it) << " | " << std::get<2>(*it) << "\n";
        ++it;
      }
      o << ")\n";
    }
    return o;
  }

  std::map<N, std::shared_ptr<Node>> getNodes() { return nodes_; }

  struct CustomCmp {
    bool operator()(
        const typename std::pair<std::weak_ptr<Node>, std::shared_ptr<E>> &left,
        const typename std::pair<std::weak_ptr<Node>, std::shared_ptr<E>>
            &right) const {
      if (left.first.lock()->getVal() == right.first.lock()->getVal()) {
        return *(left.second) < *(right.second);
      }
      return left.first.lock()->getVal() < right.first.lock()->getVal();
    }
  };
  class Node {
  public:
    explicit Node(const N &v) {
      N newV = v;
      val_ = std::make_shared<N>(newV);
    }
    const N &getVal() { return *val_; }
    std::vector<std::pair<std::weak_ptr<Node>, std::shared_ptr<E>>> &
    getEdges() {
      return edges_;
    }
    const typename std::vector<E> getWeights(const N &dst);
    bool isWeight(const N &dst, const E &w);
    bool InsertEdge(std::weak_ptr<Node> wDst, const E &w);
    void Replace(const N &newData) { val_ = std::make_shared<N>(newData); }
    bool deleteEdge(const std::shared_ptr<Node> &inEdge);
    bool deleteEdge(const N &inEdge, const E &w);
    void sort() { std::sort(edges_.begin(), edges_.end(), CustomCmp()); }

  private:
    std::shared_ptr<N> val_;
    std::vector<std::pair<std::weak_ptr<Node>, std::shared_ptr<E>>> edges_;
  };
  class const_iterator {
  public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = std::tuple<N, N, E>;
    using reference = std::tuple<const N &, const N &, const E &>;
    using pointer = std::tuple<const N *, const N *, const E *>;
    using difference_type = int;

    reference operator*() const {
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
      --(*this);
      return copy;
    }
    friend bool operator==(const Graph<N, E>::const_iterator &lhs,
                           const Graph<N, E>::const_iterator &rhs) {
      return lhs.outer_ == rhs.outer_ &&
             (lhs.outer_ == lhs.sentinel_ || lhs.inner_ == rhs.inner_);
    }
    friend bool operator!=(const Graph<N, E>::const_iterator &lhs,
                           const Graph<N, E>::const_iterator &rhs) {
      return !(lhs == rhs);
    }

  private:
    typename std::map<N, std::shared_ptr<Node>>::iterator outer_;
    const typename std::map<N, std::shared_ptr<Node>>::iterator sentinel_;
    const typename std::map<N, std::shared_ptr<Node>>::iterator sentinel2_;
    typename std::vector<
        std::pair<std::weak_ptr<Node>, std::shared_ptr<E>>>::iterator inner_;
    const_iterator(const decltype(outer_) &outer,
                   const decltype(sentinel_) &sentinel,
                   const decltype(sentinel2_) &sentinel2,
                   const decltype(inner_) &inner)
        : outer_{outer}, sentinel_{sentinel},
          sentinel2_{sentinel2}, inner_{inner} {
    }
    friend class Graph;
  };

private:
  std::map<N, std::shared_ptr<Node>> nodes_;
};

} // namespace gdwg

#include "assignments/dg/graph.tpp"

#endif // ASSIGNMENTS_DG_GRAPH_H_
