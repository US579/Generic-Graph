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

template <typename N, typename E> bool gdwg::Graph<N, E>::IsNode(const N &val) {
  return (nodes_.find(val) != nodes_.end());
}

template <typename N, typename E>
bool gdwg::Graph<N, E>::InsertNode(const N &val) {
  //   if (!IsNode(val)) {
  //     return false;
  //   }
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

template <typename N, typename E>
bool gdwg::Graph<N, E>::IsConnected(const N &src, const N &dst) {
  auto srcNode = nodes_.at(src);
  std::vector<E> connected = srcNode->getWeights(dst);
  return (!connected.empty());
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

template <typename N, typename E> void gdwg::Graph<N, E>::printG() {
  for (typename std::map<N, std::shared_ptr<Node>>::iterator it =
           nodes_.begin();
       it != nodes_.end(); ++it) {
    std::cout << it->first << " => " << it->second->getVal() << '\n';

    // for (typename std::vector<std::pair<std::weak_ptr<Node>, E>>::iterator
    // it1 =
    //          it->second->getEdges().begin();
    //      it1 != it->second->getEdges(); ++it) {
    //   std::cout << it1->second << it1->first.lock()->getVal() << '\n';
    // }
  }
}