// constructor
template <typename N, typename E>
gdwg::Graph<N, E>::Graph(typename std::vector<N>::const_iterator first,
                         typename std::vector<N>::const_iterator last) {
  for (auto &it = first; it != last; ++it) {
    InsertNode(*it);
  }
}


template <typename N, typename E>
gdwg::Graph<N, E>::Graph(
    typename std::vector<std::tuple<N, N, E>>::const_iterator first,
    typename std::vector<std::tuple<N, N, E>>::const_iterator last) {

  for (auto &it = first; it != last; ++it) {
    auto src = std::get<0>(*it);
    auto dst = std::get<1>(*it);
    if (!this->IsNode(src)) {
      InsertNode(src);
    }
    if (!this->IsNode(dst)) {
      InsertNode(dst);
    }
    InsertEdge(src, dst, std::get<2>(*it));
  }
}



// Methods

template <typename N, typename E> bool gdwg::Graph<N, E>::IsNode(const N &val) {
  return (nodes_.find(val) != nodes_.end());
}

template <typename N, typename E>
bool gdwg::Graph<N, E>::InsertNode(const N &val) {
  Node newN = Node{val};
  const auto &couple = std::make_pair(val, std::make_shared<Node>(newN));
  nodes_.insert(couple);
  return true;
}

template <typename N, typename E>
bool gdwg::Graph<N, E>::InsertEdge(const N &src, const N &dst, const E &w) {
  if (!IsNode(src) || !IsNode(dst)) {
    throw std::runtime_error{"Cannot call Graph::InsertEdge when either src or "
                             "dst node does not exist"};
  }
  //   auto srcNode = nodes_.at(src);
  std::weak_ptr<Node> wDst = nodes_.at(dst);
  //   auto weights = srcNode->isWeight(dst, w);
  //   if (!weights) {
  return nodes_.at(src)->InsertEdge(wDst, w);
  // return true;
  //   }
  //   return false;
}

template <typename N, typename E> bool gdwg::Graph<N, E>::IsConnected(const N& src, const N& dst){
    auto srcNode = nodes_.at(src);
    std::vector<E> connected = srcNode->getWeights(dst);    
    return (!connected.empty());
}


template <typename N, typename E>
std::vector<E> gdwg::Graph<N,E>::Graph::GetWeights(const N& src, const N& dst){

}

template <typename N, typename E> void gdwg::Graph<N, E>::printG() {
  for (typename std::map<N, std::shared_ptr<Node>>::iterator it =
           nodes_.begin();
       it != nodes_.end(); ++it) {
    std::cout << it->first << " => " << it->second->getVal() << '\n';
  }
}





template <typename N, typename E>
typename std::map<N, std::shared_ptr<typename gdwg::Graph<N,E>::Node>>::const_iterator gdwg::Graph<N,E>::begin() const{
  Iter = nodes_.cbegin();
  return Iter;
}

template <typename N, typename E>
typename std::map<N, std::shared_ptr<typename gdwg::Graph<N,E>::Node>>::const_iterator gdwg::Graph<N,E>::end() const{
  Iter = nodes_.cend();
  return Iter;
}
