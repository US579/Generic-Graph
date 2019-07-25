//  constructor
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

// copy constructor
template <typename N, typename E>
gdwg::Graph<N, E>::Graph(const gdwg::Graph<N, E> &g) {
  for (auto &node : g.nodes_) {
    InsertNode(node.first);
  }
  for (auto &nodes : g.nodes_) {
    for (const auto &Val : nodes.second->getEdge()) {
      InsertEdge(nodes.first, Val.first.lock()->getVal(), *(Val.second));
    }
  }
}

// move constructor
template <typename N, typename E>
gdwg::Graph<N, E>::Graph(gdwg::Graph<N, E> &&g) {
  nodes_ = std::move(g.nodes_);
}


// operator  overload
template <typename N, typename E>
gdwg::Graph<N, E> &gdwg::Graph<N, E>::operator=(const gdwg::Graph<N, E> &g) {
  for (auto &node : g.nodes_) {
    InsertNode(node.first);
  }
  for (auto &nodes : g.nodes_) {
    for (const auto &Val : nodes.second->getEdge()) {
      InsertEdge(nodes.first, Val.first.lock()->getVal(), *(Val.second));
    }
  }
}

template <typename N, typename E>
gdwg::Graph<N, E> &gdwg::Graph<N, E>::operator=(gdwg::Graph<N, E> &&g) noexcept {
  nodes_ = std::move(g.nodes_);
  return *this;
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
  auto srcNode = nodes_.at(src);
  std::weak_ptr<Node> wDst = nodes_.at(dst);
  auto weights = srcNode->isWeight(dst, w);
  if (!weights) {
    return nodes_.at(src)->InsertEdge(wDst, w);
    return true;
  }
  return false;
}

template <typename N, typename E>
bool gdwg::Graph<N, E>::IsConnected(const N &src, const N &dst) {
  auto srcNode = nodes_.at(src);
  std::vector<E> connected = srcNode->getWeights(dst);
  return (!connected.empty());
}

template <typename N, typename E>
std::vector<E> gdwg::Graph<N, E>::Graph::GetWeights(const N &src,
                                                    const N &dst) {
  auto srcNode = nodes_.at(src);
  std::vector<E> weights = srcNode->getWeights(dst);

  sort(weights.begin(), weights.end());
  for (auto i : weights) {
    std::cout << i << "\n";
  }
  return weights;
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
void gdwg::Graph<N, E>::MergeReplace(const N &oldData, const N &newData) {
  if (!IsNode(oldData) || !IsNode(newData)) {
    throw std::runtime_error{"Cannot call Graph::MergeReplace on old or new "
                             "data if they don't exist in the graph"};
  }
  auto newNode = nodes_.at(oldData);
  auto oldNode = nodes_.at(newData);
  auto newEdges = newNode->getEdges();
  auto oldEdges = oldNode->getEdges();
  for (auto newIt = newEdges.begin(); newIt != newEdges.end(); ++newIt) {
    for (auto oldIt = oldEdges.begin(); oldIt != oldEdges.end(); ++oldIt) {
      auto linkNodeOld = newIt->first.lock()->getVal();
      auto linkNodeNew = oldIt->first.lock()->getVal();
      if (linkNodeOld == linkNodeNew && *newIt->second == *oldIt->second) {
        std::cout << "duplicate!!\n";
        erase(oldData, linkNodeOld, *oldIt->second);
      }
    }
  }
  Replace(oldData, newData);
}

template <typename N, typename E> void gdwg::Graph<N, E>::Graph::Clear() {
  nodes_.clear();
}

template <typename N, typename E>
bool gdwg::Graph<N, E>::Graph::DeleteNode(const N &node) {
  if (!IsNode(node))
    return false;
  auto oldDate = nodes_.at(node);
  for (const auto &n : nodes_) {
    n.second->deleteEdge(oldDate);
    std::cout << n.first << "\n";
  }
  nodes_.erase(node);
  return true;
}

template <typename N, typename E>
bool gdwg::Graph<N, E>::Node::isWeight(const N &dst, const E &w) {
  std::vector<E> connected = getWeights(dst);
  for (auto it = connected.begin(); it != connected.end(); ++it) {
    if (*it == w) {
      // std::cout << "found" << "\n";
      return true;
    }
  }
  return false;
}

template <typename N, typename E>
const typename std::vector<E>
gdwg::Graph<N, E>::Node::getWeights(const N &dst) {
  std::vector<E> connected;
  // for (typename std::vector<std::pair<std::weak_ptr<Node>,
  // std::unique_ptr<E>>>::iterator
  for (auto it = edges_.begin(); it != edges_.end(); ++it) {
    if (it->first.lock()->getVal() == dst) {
      connected.push_back(*(it->second));
      // std::cout << it->first.lock()->getVal() << "\n";
    }
  }
  return connected;
}

template <typename N, typename E>
bool gdwg::Graph<N, E>::Node::InsertEdge(std::weak_ptr<Node> wDst, const E &w) {

  if (!isWeight(wDst.lock()->getVal(), w)) {
    edges_.push_back(std::make_pair(wDst, std::make_shared<E>(w)));
    return true;
  }
  return false;
}

template <typename N, typename E>
bool gdwg::Graph<N, E>::Node::deleteEdge(const std::shared_ptr<Node> &inEdge) {
  std::cout << inEdge << "\n";
  auto result = std::remove_if(
      edges_.begin(), edges_.end(),
      [&inEdge](const std::pair<std::weak_ptr<Node>, std::shared_ptr<E>> &ptr) {
        return (ptr.first.lock() == inEdge);
      });
  edges_.erase(result, edges_.end());
  return true;
}

template <typename N, typename E>
bool gdwg::Graph<N, E>::Graph::erase(const N &src, const N &dst, const E &w) {
  if (!IsNode(src) || !IsNode(dst))
    return false;
  auto srcNode = nodes_.at(src);
  std::vector<E> v = srcNode->getWeights(dst);
  typename std::vector<E>::iterator it = find(v.begin(), v.end(), w);
  if (it == v.end()) {
    return false;
  }
  srcNode->deleteEdge(dst, w);
  return true;
}

template <typename N, typename E>
bool gdwg::Graph<N, E>::Node::deleteEdge(const N &inEdge, const E &w) {
  auto result = std::remove_if(
      edges_.begin(), edges_.end(),
      [&w](const std::pair<std::weak_ptr<Node>, std::shared_ptr<E>> &ptr) {
        return (*(ptr.second) == w);
      });
  edges_.erase(result, edges_.end());
  return true;
}

template <typename N, typename E>
typename std::map<
    N, std::shared_ptr<typename gdwg::Graph<N, E>::Node>>::const_iterator
gdwg::Graph<N, E>::begin() const {
  Iter = nodes_.cbegin();
  return Iter;
}

template <typename N, typename E>
typename std::map<
    N, std::shared_ptr<typename gdwg::Graph<N, E>::Node>>::const_iterator
gdwg::Graph<N, E>::end() const {
  Iter = nodes_.cend();
  return Iter;
}
