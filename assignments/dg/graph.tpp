// 2.1 Constructors & Destructors
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
    for (const auto &Val : nodes.second->getEdges()) {
      InsertEdge(nodes.first, Val.first.lock()->getVal(), *(Val.second));
    }
  }
}

// move constructor
template <typename N, typename E>
gdwg::Graph<N, E>::Graph(gdwg::Graph<N, E> &&g) noexcept {
  nodes_ = std::move(g.nodes_);
}

// 2.2. Operations
// copy assignment
template <typename N, typename E>
gdwg::Graph<N, E> &gdwg::Graph<N, E>::operator=(const gdwg::Graph<N, E> &g) {
  for (auto &node : g.nodes_) {
    InsertNode(node.first);
  }
  for (auto &nodes : g.nodes_) {
    for (const auto &Val : nodes.second->getEdges()) {
      InsertEdge(nodes.first, Val.first.lock()->getVal(), *(Val.second));
    }
  }
}

// move assignment
template <typename N, typename E>
gdwg::Graph<N, E> &gdwg::Graph<N, E>::
operator=(gdwg::Graph<N, E> &&g) noexcept {
  nodes_ = std::move(g.nodes_);
  return *this;
}

// 2.3. Methods
template <typename N, typename E>
bool gdwg::Graph<N, E>::InsertNode(const N &val) {
  if (IsNode(val)) {
    return false;
  }
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
  std::weak_ptr<Node> wDst = nodes_.at(dst);
  auto a = w;
  return nodes_.at(src)->InsertEdge(wDst, a);
}

template <typename N, typename E>
bool gdwg::Graph<N, E>::Graph::DeleteNode(const N &node) {
  if (!IsNode(node))
    return false;
  auto oldDate = nodes_.at(node);
  for (const auto &n : nodes_) {
    n.second->deleteEdge(oldDate);
    // std::cout << n.first << "\n";
  }
  nodes_.erase(node);
  return true;
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
  auto newNode = nodes_.at(newData);
  auto oldNode = nodes_.at(oldData);
  for (auto oldEdge : oldNode->getEdges()) {
    newNode->InsertEdge(oldEdge.first, *(oldEdge.second));
    oldNode->deleteEdge(oldEdge.first.lock()->getVal(), *(oldEdge.second));
  }
  nodes_.erase(oldData);
  const auto &couple = std::make_pair(newData, newNode);
  nodes_.insert(couple);
}

template <typename N, typename E> void gdwg::Graph<N, E>::Graph::Clear() {
  nodes_.clear();
}

template <typename N, typename E> bool gdwg::Graph<N, E>::IsNode(const N &val) {
  return (nodes_.find(val) != nodes_.end());
}

template <typename N, typename E>
bool gdwg::Graph<N, E>::IsConnected(const N &src, const N &dst) {
  auto srcNode = nodes_.at(src);
  std::vector<E> connected = srcNode->getWeights(dst);
  return (!connected.empty());
}

template <typename N, typename E> std::vector<N> gdwg::Graph<N, E>::GetNodes() {
  std::vector<N> nodes;
  for (auto node : nodes_) {
    nodes.push_back(node.first);
  }
  return nodes;
}

template <typename N, typename E>
std::vector<N> gdwg::Graph<N, E>::GetConnected(const N &src) {
  if (!IsNode(src)) {
    throw std::out_of_range{
        "Cannot call Graph::GetConnected if src doesn't exist in the graph"};
  }
  std::vector<N> nodes;
  auto node = nodes_.at(src);
  for (auto edge : node->getEdges()) {
    auto n = edge.first.lock()->getVal();
    if (std::find(nodes.begin(), nodes.end(), n) == nodes.end()) {
      nodes.push_back(n);
    }
  }
  std::sort(nodes.begin(), nodes.end());
  return nodes;
}

template <typename N, typename E>
std::vector<E> gdwg::Graph<N, E>::Graph::GetWeights(const N &src,
                                                    const N &dst) {
  auto srcNode = nodes_.at(src);
  std::vector<E> weights = srcNode->getWeights(dst);

  sort(weights.begin(), weights.end());
  // for (auto i : weights) {
  //   std::cout << i << "\n";
  // }
  return weights;
}

template <typename N, typename E>
typename gdwg::Graph<N, E>::const_iterator
gdwg::Graph<N, E>::Graph::find(const N &src, const N &dst, const E &w) {
  for (auto it = begin(); it != end(); ++it) {
    if (std::get<0>(*it) == src && std::get<1>(*it) == dst &&
        std::get<2>(*it) == w) {
      return it;
    }
  }
  return end();
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
typename gdwg::Graph<N, E>::const_iterator
gdwg::Graph<N, E>::Graph::erase(gdwg::Graph<N, E>::const_iterator it) {
  auto &src = std::get<0>(*it);
  auto &dst = std::get<1>(*it);
  auto &w = std::get<2>(*it);
  if (!IsNode(src) || !IsNode(dst))
    return end();
  auto srcNode = nodes_.at(src);
  std::vector<E> v = srcNode->getWeights(dst);
  typename std::vector<E>::iterator it1 = find(v.begin(), v.end(), w);
  if (it1 == v.end()) {
    return end();
  }
  srcNode->deleteEdge(dst, w);
  return ++it;
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
      // auto w = ;
      connected.push_back(*(it->second));
      // std::cout << it->first.lock()->getVal() << "\n";
    }
  }
  return connected;
}

template <typename N, typename E>
bool gdwg::Graph<N, E>::Node::InsertEdge(std::weak_ptr<Node> wDst, const E &w) {

  if (!isWeight(wDst.lock()->getVal(), w)) {
    // std::cout << "1";
    edges_.push_back(std::make_pair(wDst, std::make_shared<E>(w)));
    return true;
  }
  return false;
}

template <typename N, typename E>
bool gdwg::Graph<N, E>::Node::deleteEdge(const std::shared_ptr<Node> &inEdge) {
  // std::cout << inEdge << "\n";
  auto result = std::remove_if(
      edges_.begin(), edges_.end(),
      [&inEdge](const std::pair<std::weak_ptr<Node>, std::shared_ptr<E>> &ptr) {
        return (ptr.first.lock() == inEdge);
      });
  edges_.erase(result, edges_.end());
  return true;
}

template <typename N, typename E>
bool gdwg::Graph<N, E>::Node::deleteEdge(const N &inEdge, const E &w) {
  auto result = std::remove_if(
      edges_.begin(), edges_.end(),
      [&inEdge,
       &w](const std::pair<std::weak_ptr<Node>, std::shared_ptr<E>> &ptr) {
        if (ptr.first.expired())
          return false;
        return (inEdge == ptr.first.lock()->getVal() && *(ptr.second) == w);
      });
  edges_.erase(result, edges_.end());
  return true;
}

template <typename N, typename E>
typename gdwg::Graph<N, E>::const_iterator gdwg::Graph<N, E>::cbegin() {
  auto first =
      std::find_if(nodes_.begin(), nodes_.end(),
                   [](const std::pair<N, std::shared_ptr<Node>> &curr) {
                     return !(curr.second->getEdges().empty());
                   });
  if (first != nodes_.end()) {
    return {first, nodes_.end(), nodes_.begin(),
            first->second->getEdges().begin()};
  }
  return cend();
}

template <typename N, typename E>
typename gdwg::Graph<N, E>::const_iterator gdwg::Graph<N, E>::cend() {
  return {nodes_.end(), nodes_.end(), nodes_.begin(), {}};
}

template <typename N, typename E>
typename gdwg::Graph<N, E>::const_iterator &gdwg::Graph<N, E>::const_iterator::
operator++() {
  ++inner_;
  if (inner_ == outer_->second->getEdges().end()) {
    // std::cout << ":" << std::endl;
    do {
      ++outer_;
      // if (outer_ != sentinel_) {
      //   std::cout << outer_->first << outer_->second->getEdges().size()
      //             << std::endl;
      // }
      // if (outer_ == sentinel_) {
      //   std::cout << "11dsahdkjhasjkdhasjk" << std::endl;
      // }
      // std::cout << outer_->first ;
    } while (outer_ != sentinel_ && outer_->second->getEdges().empty());
    // std::cout << "\n" << std::endl;
    if (outer_ != sentinel_) {
      // std::cout << "1" << std::endl;
      inner_ = outer_->second->getEdges().begin();
      // std::cout << inner_->first.lock()->getVal();
    } else {
      // std::cout << "2" << std::endl;
      inner_ = {};
    }
  }
  // if (outer_ != sentinel_) {
  //   std::cout << outer_->first << " " << inner_->first.lock()->getVal() << "\n"
  //             << *(inner_->second);
  // }
  return *this;
}

template <typename N, typename E>
typename gdwg::Graph<N, E>::const_iterator &gdwg::Graph<N, E>::const_iterator::
operator--() {
  // std::cout << "new round:" << std::endl;
  if (outer_ == sentinel_ || inner_ == outer_->second->getEdges().begin()) {
    // std::cout << ":" << std::endl;
    do {
      --outer_;
      // std::cout << outer_->first << outer_->second->getEdges().size()
      //           << std::endl;
    } while (outer_->second->getEdges().empty());
    // std::cout << "-" << std::endl;
    inner_ = outer_->second->getEdges().end();
  }
  // if (inner_ == outer_->second->getEdges().end()) {
  // std::cout << "i am ironman" << "\n";
  // }
  --inner_;
  // std::cout <<  ( inner_ == outer_->second->getEdges().begin()) << std::endl;
  // std::cout << outer_->first << " " << inner_->first.lock()->getVal()
  // <<std::endl;
  //           << *(inner_->second) << std::endl;
  return *this;
}

template <typename N, typename E>
typename gdwg::Graph<N, E>::const_reverse_iterator
gdwg::Graph<N, E>::crbegin() {
  auto first =
      std::find_if(nodes_.crbegin(), nodes_.crend(),
                   [](const std::pair<N, std::shared_ptr<Node>> &curr) {
                     return !(curr.second->getEdges().empty());
                   });
  if (first != nodes_.crend()) {
    return {first, nodes_.crend(), first->second->getEdges().crbegin()};
  }
  return crend();
}

template <typename N, typename E>
typename gdwg::Graph<N, E>::const_reverse_iterator gdwg::Graph<N, E>::crend() {
  return {nodes_.crend(), nodes_.crend(), {}};
}

template <typename N, typename E>
typename gdwg::Graph<N, E>::const_reverse_iterator &
gdwg::Graph<N, E>::const_reverse_iterator::operator++() {
  // std::cout << *(inner_->second);
  // std::cout << inner_->first.lock()->getVal();
  // if (inner_ == outer_->second->getEdges().crend()) {
  //   std::cout << "hey";
  // }
  ++inner_;
  // std::cout << outer_->first;
  if (inner_ == outer_->second->getEdges().crend()) {
    do {
      ++outer_;
      // std::cout << outer_->first;
    } while (outer_ != sentinel_ && outer_->second->getEdges().crbegin() ==
                                        outer_->second->getEdges().crend());
    if (outer_ != sentinel_) {
      inner_ = outer_->second->getEdges().crbegin();
    }
  }
  return *this;
}