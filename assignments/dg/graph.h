#ifndef ASSIGNMENTS_DG_GRAPH_H_
#define ASSIGNMENTS_DG_GRAPH_H_

#include <iostream>
#include <vector>

namespace gdwg {

template <typename N, typename E> class Graph {
public:
  Graph() = default;
  Graph(const Graph & g);
  Graph(Graph && g);
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

  class Node {
  public:
    Node(const N &v) : val_{std::make_shared<N>(v)} {}
    const N &getval() { return *this->val_; }
    void insertEdge(std::shared_ptr<Node> src, std::shared_ptr<Node> dst,
                    const E &w);
    //      std::vector<std::shared_ptr<Edge>> getEdge(){return edges_;}
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
//template <typename N, typename E>
//gdwg::Graph<N, E>(const gdwg::Graph<N, E> & ) {}
// move constructor
//template <typename N, typename E> gdwg::Graph<N, E>(gdwg::Graph<N, E> &&) {}

// deconstructor
template <typename N, typename E> gdwg::Graph<N, E>::~Graph() { Node_.clear();}

template <typename N, typename E>
gdwg::Graph<N, E>::Graph(typename std::vector<N>::const_iterator first,
                         typename std::vector<N>::const_iterator last) {
  for (auto &it = first; it != last; ++it) {
    Node new_node = Node{*it};
    Node_.push_back(std::make_shared<Node>(new_node));
  }
}

template <typename N, typename E>
gdwg::Graph<N, E>::Graph(
    typename std::vector<std::tuple<N, N, E>>::const_iterator first,
    typename std::vector<std::tuple<N, N, E>>::const_iterator last) {
  for (auto &it = first; it != last; ++it) {
    Node new_node = Node{*it};
  }
}


template <typename N,typename E>
gdwg::Graph<N, E>::Graph(typename std::initializer_list<N> n){
  for (auto it = n.begin(); it != n.end() ; ++it){
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
    if ((*it)->getval() == src) {
      std::shared_ptr<Node> s = std::make_shared<Node>(src);
      std::shared_ptr<Node> d = std::make_shared<Node>(dst);
      (*it)->insertEdge(s, d, w);
      //      std::cout<<(*it)->getval()<<"\n";
      //      std::cout<<src<<"\n";
      return true;
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
bool gdwg::Graph<N, E>::IsConnected(const N &src, const N &dst) {
  if (!IsNode(src) || !IsNode(dst))
    throw std::runtime_error("Cannot call Graph::IsConnected if src or dst "
                             "node don't exist in the graph");

  //  std::cout<< *from <<"\n";
  return true;
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
