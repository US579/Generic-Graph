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