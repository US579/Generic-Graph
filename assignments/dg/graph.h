#ifndef ASSIGNMENTS_DG_GRAPH_H_
#define ASSIGNMENTS_DG_GRAPH_H_

#include <iostream>
#include <vector>

namespace gdwg {

template<typename N, typename E>
class Graph {
 public:
  Graph()= default;
//  Graph<N, E>(std::vector<N> a,std::vector<N> b);

  class Node{
  public:
    Node(const N& v):val{std::make_shared<N>(v)}{}
    const N& getval(){return *this->val;}
  private:
    std::shared_ptr<N> val;
  };
  class Edge{
  public:
  private:
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
