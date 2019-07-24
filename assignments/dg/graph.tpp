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

template <typename N, typename E>
gdwg::Graph<N, E>::Graph(typename std::initializer_list<N> n) {
  for (auto it = n.begin(); it != n.end(); ++it) {
    InsertNode(*it);
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
bool gdwg::Graph<N, E>::Replace(const N &oldData, const N &newData) {
  if (!IsNode(oldData)) {
    throw std::runtime_error{
        "Cannot call Graph::Replace on a node that doesn't exist"};
  }
  if (IsNode(newData)) {
    return false;
  }
  //   auto nodeHandler = nodes_.extract(oldData);
  //   nodeHandler.key() = newData;
  //   nodes_.insert(std::move(nodeHandler));
  auto node = nodes_.at(oldData);
  nodes_.erase(oldData);
  node->Replace(newData);

  const auto &couple = std::make_pair(newData, node);
  nodes_.insert(couple);
  return true;
}

template <typename N, typename E>
void gdwg::Graph<N,E>::MergeReplace(const N& oldData, const N& newData){

  if (!IsNode(oldData) || ! IsNode(newData)) {
    throw std::runtime_error{
        "Cannot call Graph::Replace on a node that doesn't exist"};
  }
  if (oldData == newData)
    return;
  auto newNode = nodes_.at(newData);
  auto oldeNode = nodes_.at(oldData);
};

template <typename N, typename E>
bool gdwg::Graph<N,E>::Graph::erase(const N& src, const N& dst, const E& w){
  if (!IsNode(src) || ! IsNode(dst))
    return false;
  auto srcNode = nodes_.at(src);
  if (srcNode->get){

  }

};

template <typename N, typename E>
bool gdwg::Graph<N,E>::Graph::DeleteNode(const N& node){
  if (!IsNode(node))
    return false;
  auto oldDate = nodes_.at(node);
  for(const auto & n : nodes_){
    n.second->deleteEdge(oldDate);
    std::cout<< n.first << "\n";
  }
  nodes_.erase(node);
  return true;
}

template <typename N, typename E>
bool gdwg::Graph<N,E>::Node::deleteEdge(const std::shared_ptr<Node> & inEdge){
  std::cout<< inEdge << "\n";
  auto result = std::remove_if(edges_.begin(),edges_.end(),
                               [&inEdge](const std::pair<std::weak_ptr<Node>,std::shared_ptr<E>> & ptr){
                                 return (ptr.first.lock() == inEdge);
                               });
  edges_.erase(result,edges_.end());
  return true;
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
