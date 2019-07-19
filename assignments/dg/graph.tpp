#include <iterator>
#include <vector>

template <typename N, typename E>
gdwg::Graph<N, E>::Graph(typename std::vector<N>::const_iterator a,
                         typename std::vector<N>::const_iterator b) {
  for (auto& it = a; it != b; ++it) {
    Node n{*it};
    // std::cout << *it << '\n';
    nList.push_back(n);
  }
}