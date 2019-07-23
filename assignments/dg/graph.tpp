
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
void gdwg::Graph<N, E>::printG(){
  for (typename std::map<N, std::shared_ptr<Node>>::iterator it = nodes_.begin();
       it != nodes_.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

}


template <typename N, typename E>
bool gdwg::Graph<N,E>::InsertNode(const N &val) {
  Node newN= Node{val};
  const auto & couple = std::make_pair(val,std::make_shared<Node>(newN));
  nodes_.insert(couple);
  return true;
}

template <typename N, typename E>
gdwg::Graph<N, E>::Graph(typename std::initializer_list<N> n) {
  for (auto it = n.begin(); it != n.end(); ++it) {
    Node newN = Node(*it);
    const auto & couple = std::make_pair(*it,std::make_shared<Node>(newN));
    nodes_.insert(couple);
  }
}

template <typename N, typename E>
std::vector<N> gdwg::Graph<N,E>::GetNodes() {
  std::vector<N> nodes;
  for (typename std::map<N, std::shared_ptr<Node>>::iterator it = nodes_.begin();
    it != nodes_.end(); ++it){
    nodes.push_back(it->first);
  }
  std::sort(nodes.begin(),nodes.end());
  return nodes;

}

