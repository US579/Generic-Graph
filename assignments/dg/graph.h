#ifndef ASSIGNMENTS_DG_GRAPH_H_
#define ASSIGNMENTS_DG_GRAPH_H_
#include <iterator>
#include <vector>
#include <memory>
#include <iostream>

namespace gdwg {

template <typename N, typename E> class Graph {
public:
  Graph() = default;
  Graph(const Graph &g);
  Graph(Graph &&g);
  ~Graph<N, E>();
  Graph(typename std::vector<N>::const_iterator first,
        typename std::vector<N>::const_iterator last);
  Graph(typename std::vector<std::tuple<N, N, E>>::const_iterator,
        typename std::vector<std::tuple<N, N, E>>::const_iterator);
  Graph(typename std::initializer_list<N>);
  bool InsertEdge(const N &src, const N &dst, const E &w);
  bool IsNode(const N &val);
  bool IsConnected(const N &src, const N &dst);
  std::vector<N> GetNodes();
  const N &value() const { return Node_[itor]->getval(); }

  class Node;
  class Edge;
  //  Graph<N, E>(std::vector<N> a,std::vector<N> b);
  // helper function
  std::shared_ptr<Node> findNode(const N &val);

  class Node {
  public:
    Node(const N &v) : val_{std::make_shared<N>(v)} {}
    const N &getval() { return *this->val_; }
    void insertEdge(std::shared_ptr<Node> src, std::shared_ptr<Node> dst,
                    const E &w);
    std::vector<std::shared_ptr<Edge>> getEdge(){return edges_;}
    bool Connected(const std::shared_ptr<Node> &dst) const;

  private:
    std::shared_ptr<N> val_;
    std::vector<std::shared_ptr<Edge>> edges_;
    //    std::vector<std::shared_ptr<Edge>> outEdge_;
    //    std::vector<std::shared_ptr<Edge>> inEdge_;
  };
  class Edge {
  public:
    Edge(std::shared_ptr<Node> src, std::shared_ptr<Node> dst, const E &w)
        : begin_{src}, end_{dst}, weight_{w} {};
    const E &getval() { return *this->weight_; }
    // const N &getDstVal() { return *this->end_.getval(); }
    std::weak_ptr<Node> getDst() { return end_; }
  private:
    std::weak_ptr<Node> begin_;
    std::weak_ptr<Node> end_;
    E weight_;
  };

private:
  std::vector<std::shared_ptr<Node>> Node_;
  mutable unsigned int itor = 0;
};

// Define your graph_iterator here
// Define your graph_const_iterator here

} // namespace gdwg

//#include "assignments/dg/graph.tpp"

// copy constructor
// template <typename N, typename E>
// gdwg::Graph<N, E>(const gdwg::Graph<N, E> & ) {}
// move constructor
// template <typename N, typename E> gdwg::Graph<N, E>(gdwg::Graph<N, E> &&) {}

// deconstructor
template <typename N, typename E> gdwg::Graph<N, E>::~Graph() { Node_.clear(); }

template <typename N, typename E>
gdwg::Graph<N, E>::Graph(typename std::vector<N>::const_iterator first,
                         typename std::vector<N>::const_iterator last) {
  for (auto &it = first; it != last; ++it) {
    if (!this->IsNode(*it)) {
      Node new_node = Node{*it};
      Node_.push_back(std::make_shared<Node>(new_node));
    }
  }
}
// not finish
template <typename N, typename E>
gdwg::Graph<N, E>::Graph(
    typename std::vector<std::tuple<N, N, E>>::const_iterator first,
    typename std::vector<std::tuple<N, N, E>>::const_iterator last) {

  for (auto &it = first; it != last; ++it) {
    auto src = std::get<0>(*it);
    auto dst = std::get<1>(*it);
    std::shared_ptr<Node> s = std::make_shared<Node>(src);
    std::shared_ptr<Node> d = std::make_shared<Node>(dst);
    if (!this->IsNode(src)) {
      Node new_node = Node{src};
      Node_.push_back(std::make_shared<Node>(new_node));
      // new_node->insertEdge(s, d, std::get<2>(*it));
    }
    if (!this->IsNode(dst)) {
      Node new_node1 = Node{dst};
      Node_.push_back(std::make_shared<Node>(new_node1));
      // new_node1->insertEdge(s, d, std::get<2>(*it));
    }
    this->findNode(src)->insertEdge(s, d, std::get<2>(*it));
    this->findNode(dst)->insertEdge(s, d, std::get<2>(*it));    
    // Node new_node = Node{*it};
  }
}

template <typename N, typename E>
gdwg::Graph<N, E>::Graph(typename std::initializer_list<N> n) {
  for (auto it = n.begin(); it != n.end(); ++it) {
    Node new_node = Node(*it);
    Node_.push_back(std::make_shared<Node>(new_node));
  }
}

template <typename N, typename E>
bool gdwg::Graph<N, E>::InsertEdge(const N &src, const N &dst, const E &w) {
  if (!this->IsNode(src) || !this->IsNode(dst)) {
    throw std::runtime_error("Cannot call Graph::InsertEdge when either src or "
                             "dst node does not exist");
  }
  for (auto it = Node_.begin(); it != Node_.end(); ++it) {
    if ((*it)->getval() == src || (*it)->getval() == dst) {
      std::shared_ptr<Node> s = this->findNode(src);
      std::shared_ptr<Node> d = this->findNode(dst);
      (*it)->insertEdge(s, d, w);
      //      std::cout<<(*it)->getval()<<"\n";
      //      std::cout<<src<<"\n";
      // return true;
    }
  }
  //    if ((*it)->getval() == src || (*it)->getval() == dst){
  //      count++;
  //      std::cout<< (*it)->getval() << "\n";
  //    }
  //    std::cout<< src <<"\n";
  //    std::cout<< (*it)->getval() << "\n";
  //  }
  //  std::cout<< count <<"\n";
  //  if (count != 2){
  //    throw std::runtime_error("ERROR: attempt to access node that does not
  //    exist");
  //  }

  return true;
}

template <typename N, typename E>
void gdwg::Graph<N, E>::Node::insertEdge(std::shared_ptr<Node> src,
                                         std::shared_ptr<Node> dst,
                                         const E &w) {
  Edge new_Edge = Edge{src, dst, w};
  std::shared_ptr<Edge> new_edge = std::make_shared<Edge>(new_Edge);
  edges_.push_back(new_edge);
}

template <typename N, typename E> bool gdwg::Graph<N, E>::IsNode(const N &val) {
  for (auto it = Node_.begin(); it != Node_.end(); ++it) {
    if ((*it)->getval() == val) {
      return true;
    }
  }
  return false;
}

template <typename N, typename E> 
std::shared_ptr<typename gdwg::Graph<N, E>::Node> gdwg::Graph<N, E>::findNode(const N &val) {
  for (auto it = Node_.begin(); it != Node_.end(); ++it) {
    if ((*it)->getval() == val) {
      return *it;
    }
  }
  return nullptr;
}

template <typename N, typename E>
bool gdwg::Graph<N, E>::IsConnected(const N &src, const N &dst) {
  if (!IsNode(src) || !IsNode(dst))
    throw std::runtime_error("Cannot call Graph::IsConnected if src or dst "
                             "node don't exist in the graph");

  //  std::cout<< *from <<"\n";
  auto srcNode = this->findNode(src);
  std::vector<std::shared_ptr<Edge>> e = srcNode->getEdge();
  for (auto it = e.begin(); it != e.end(); ++it) {
    auto curr = (*it)->getDst().lock();
    if (curr->getval() == dst){
      return true;
    }
  }
  return false;
}

template <typename N, typename E> std::vector<N> gdwg::Graph<N, E>::GetNodes() {
  std::vector<N> nodes;
  for (auto it = Node_.begin(); it != Node_.end(); ++it) {
    nodes.push_back(((*it)->getval()));
  }
  std::sort(nodes.begin(), nodes.end());
  return nodes;
}

// template <typename N, typename E>
// bool gdwg::Graph<N, E>::Node::Connected(const std::shared_ptr<Node> & dst)
// const{
//  auto result = std::find_if(weight.cbegin(), weight.cend(),
//                             [&dst] (const std::pair<std::weak_ptr<Node>,E> &
//                             a) {
//                               if(a.first.expired()) return false;
//                               return a.first.lock()->getNode() ==
//                               dst->getNode();
//                             });
//  return (result != weight.cend());
//}

#endif // ASSIGNMENTS_DG_GRAPH_H_
