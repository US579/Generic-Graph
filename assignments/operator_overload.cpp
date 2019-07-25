  friend bool operator==(const gdwg::Graph<N, E>& a, const gdwg::Graph<N, E>& b) {
    std::cout << b.nodes_.size() << "\n";
    if (a.nodes_.size() != b.nodes_.size()) {
      return false;
    }
    for (auto &n : a.nodes_) {
      std::cout << n.first << "\n";
      if (b.nodes_.find(n.first) == b.nodes_.end()) {
        return false;
      }
    }
    for (auto &n : a.nodes_) {
//      std::cout << n.first << "\n";
      auto bNode = b.nodes_.at(n.first);
      std::cout <<  bNode->getEdge().size() << "\n";
      for (int i = 0; i < bNode->getEdge().size() ;++i){
//        std::cout<<*(bNode->getEdge()[i].second)<<"\n";
//        std::cout<<*((n.second)->getEdge()[i].second)<<"\n";
//        std::cout<<bNode->getEdge()[i].first.lock()->getVal()<<"\n";
//        std::cout<<(n.second)->getEdge()[i].first.lock()->getVal()<<"\n";
        if (*(bNode->getEdge()[i].second) != *((n.second)->getEdge()[i].second) &&
            bNode->getEdge()[i].first.lock()->getVal() != (n.second)->getEdge()[i].first.lock()->getVal()){
//          std::cout<<"successsssss"<<"\n";
            return false;
        }
        

      }
//      for (auto &edge : bNode->getEdge()) {
////        std::cout<<(n.second)->getEdge().size()<<"\n";
//        std::cout<<n.second<<"\n";
//
//
//        std::cout<<*(edge.second)<<"\n";
//        std::cout<<edge.first.lock()->getVal()<<"\n";
////        auto a = ((n.second)->getEdge()).find(edge);
////        if ( ((n.second)->getEdge()).find(edge) == ((n.second)->getEdge()).end()){
////          std::cout<<"asd0000"<<"\n";
////        }
//
////        if ( (n.second)->getEdge().find(edge) == (n.second)->getEdge().end()) {
////          std::cout << bNode->getVal() << "\n";
////          std::cout << "------------"<< "\n";
////        }
//
//        //      std::cout<< n.first <<"\n";
//        //      std::cout<< bNode.first <<"\n";
//
//        //      for (auto & n2 : bNode){
//        //        n.getEdge().find(n2) != n2.getEdge().end();
//        //      }
//      }
      return true;
    }
  }
