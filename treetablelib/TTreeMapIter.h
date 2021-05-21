#pragma once
#ifndef TREETABLELIB_TTREEMAPITER_H
#define TREETABLELIB_TTREEMAPITER_H

#include <queue>
template <class TTK, class TTV> class TTreeMap;
template <class TTK, class TTV> class TTreeNode;

template <class TK, class TV>
class TTreeMapIter
{
public:
  TTreeMap<TK, TV>& map;
  std::queue<TTreeNode<TK, TV>*> position;

public:
  TTreeMapIter(TTreeMap<TK, TV>& m);
  bool GoNext();
  TTreeNode<TK, TV>* Get();
  bool IsEnd();
};

template<class TK, class TV>
TTreeMapIter<TK, TV>::TTreeMapIter(TTreeMap<TK, TV>& m) : map(m) {
  if (m.root != nullptr) {
    this->position.push(m.root);
  }
}

template<class TK, class TV>
bool TTreeMapIter<TK, TV>::GoNext() {
  TTreeNode<TK, TV>* current = this->position.front();
  this->position.pop();
  if (current->l == nullptr && current->r == nullptr) {
    return false;
  }
  else {
    if (current->l != nullptr) {
      this->position.push(current->l);
    }
    if (current->r != nullptr) {
      this->position.push(current->r);
    }
    return true;
  }
}

template<class TK, class TV>
TTreeNode<TK, TV>* TTreeMapIter<TK, TV>::Get() {
  return this->position.front();
}

template<class TK, class TV>
bool TTreeMapIter<TK, TV>::IsEnd() {
  return this->position.empty();
}


#endif