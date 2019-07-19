#ifndef ASSIGNMENTS_DG_GRAPH_H_
#define ASSIGNMENTS_DG_GRAPH_H_

#include <iostream>
#include <vector>

namespace gdwg {

template<typename N, typename E>
class Graph {
 public:
  Graph()= default;
  class Node;
  class Edge;
//  Graph<N, E>(std::vector<N> a,std::vector<N> b);

  class Node{
  public:
    Node(const N& v):val_{std::make_shared<N>(v)}{}
    const N& getval(){return *this->val;}
  private:
    std::shared_ptr<N> val_;
    std::vector<std::shared_ptr<Edge>> outEdge_;
    std::vector<std::shared_ptr<Edge>> inEdge_;

  };
  class Edge{
  public:
    Edge(std::shared_ptr<Node> src,std::shared_ptr<Node> dst , const E& w):
    begin_{src},end_{dst},weight_{w} {}
  private:
    E weight_;
    std::weak_ptr<Node> begin_;
    std::weak_ptr<Node> end_;
  };

 private:
  std::vector<std::shared_ptr<Node>> Node_;

};

// Define your graph_iterator here
// Define your graph_const_iterator here

}

//#include "assignments/dg/graph.tpp"
//template <typename N, typename E>
//gdwg::Graph<N, E>(std::vector<N> a,std::vector<N> b){
//
//};

#endif  // ASSIGNMENTS_DG_GRAPH_H_
