// constructor
template <typename N, typename E>
gdwg::Graph<N, E>::Graph(typename std::vector<N>::const_iterator first,
                         typename std::vector<N>::const_iterator last) {
  for (auto &it = first; it != last; ++it) {
    // if (!this->IsNode(*it)) {
    Node new_node = Node{*it};
    nodes_.insert(std::make_pair(*it, std::make_shared<Node>(new_node)));
    // }
  }
}

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
      nodes_.insert(std::make_pair(src, std::make_shared<Node>(new_node)));
      // new_node->insertEdge(s, d, std::get<2>(*it));
    }
    if (!this->IsNode(dst)) {
      Node new_node1 = Node{dst};
      nodes_.insert(std::make_pair(src, std::make_shared<Node>(new_node1)));
      // new_node1->insertEdge(s, d, std::get<2>(*it));
    }
    this->findNode(src)->insertEdge(s, d, std::get<2>(*it));
    this->findNode(dst)->insertEdge(s, d, std::get<2>(*it));
    // Node new_node = Node{*it};
  }
}

template <typename N, typename E> bool gdwg::Graph<N, E>::IsNode(const N &val) {
  //   auto search = nodes_.find(val);
  return (nodes_.find(val) != nodes_.end());
}

template <typename N, typename E>
bool gdwg::Graph<N, E>::InsertEdge(const N &src, const N &dst, const E &w) {
  if (!this->IsNode(src) || !this->IsNode(dst)) {
    throw std::runtime_error{"Cannot call Graph::InsertEdge when either src or "
                             "dst node does not exist"};
  }
  auto srcNode = nodes_.at(src);
  auto dstNode = nodes_.at(dst);
  auto weights = srcNode->isWeight(dst, w);
  if (!weights) {
    std::weak_ptr<Node> wDst = dstNode;
    srcNode->InsertEdge(wDst, w);
    return true;
  }
  //   auto srcNode = nodes_.at(src);
  //   auto dstNode = nodes_.at(dst);
  //   if (is)
  return false;
}

template <typename N, typename E> void gdwg::Graph<N, E>::printG() {
  for (typename std::map<N, std::shared_ptr<Node>>::iterator it =
           nodes_.begin();
       it != nodes_.end(); ++it)
    std::cout << it->first << " => " << it->second->getVal() << '\n';
}