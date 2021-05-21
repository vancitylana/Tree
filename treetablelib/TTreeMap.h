#ifndef TREETABLELIB_TTREEMAP_H
#define TREETABLELIB_TTREEMAP_H

#include <queue>
#include "TTreeNode.h"
#include "TTreeMapIter.h"

template <class TK, class TV>
class TTreeMap {
protected:
  TTreeNode<TK, TV>* root;
  int count;

public:
  TTreeMap();
  TTreeMap(const TTreeMap<TK, TV>& p);
  virtual ~TTreeMap();

  virtual TV& operator[](TK i);

  virtual TV Find(TK k);
  virtual void Delete(TK k);
  virtual void Add(TK k, TV v);
  virtual int GetCount();

  typedef TTreeMapIter<TK, TV> iterator;
  iterator Begin();
  friend class TTreeMapIter<TK, TV>;
};

template<class TK, class TV>
TTreeMap<TK, TV>::TTreeMap() {
  this->count = 0;
  this->root = nullptr;
}

template<class TK, class TV>
TTreeMap<TK, TV>::TTreeMap(const TTreeMap<TK, TV>& p) {
  this->count = p.count;
  if (p.root != nullptr) {
    this->root = new TTreeNode<TK, TV>(*(p.root));
    std::queue<TTreeNode<TK, TV>*> outer;
    outer.push(p.root);

    std::queue<TTreeNode<TK, TV>*> inner;
    inner.push(this->root);

    while (!outer.empty()) {
      TTreeNode<TK, TV>* current_outer = outer.front()->l;
      TTreeNode<TK, TV>* current_inner = inner.front()->l;

      outer.pop();
      inner.pop();

      if (current_outer->l != nullptr) {
        TTreeNode<TK, TV>* tmp = new TTreeNode<TK, TV>(*(current_outer->l));
        current_inner->l = tmp;
        outer.push(current_outer->l);
        inner.push(current_inner->l);
      }
      if (current_outer->r != nullptr) {
        TTreeNode<TK, TV>* tmp = new TTreeNode<TK, TV>(*(current_outer->r));
        current_inner->r = tmp;
        outer.push(current_outer->r);
        inner.push(current_inner->r);
      }
    }
  }
}

template<class TK, class TV>
TTreeMap<TK, TV>::~TTreeMap() {
  if (this->root != nullptr) {
    std::queue<TTreeNode<TK, TV>*> q;
    q.push(this->root);
    while (!q.empty()) {
      TTreeNode<TK, TV>* left = q.front()->l;
      TTreeNode<TK, TV>* right = q.front()->l;
      if (left != nullptr) {
        q.push(left);
      }
      if (right != nullptr) {
        q.push(right);
      }
      delete q.front();
      q.pop();
    }
  }
}

template<class TK, class TV>
TV& TTreeMap<TK, TV>::operator[](TK i) {
  TTreeNode<TK, TV>* res(this->root);
  if (res->GetKey() == i) return res->GetVal();
  while (res->l || res->r) {
    if (res->GetKey() == i) return res->GetVal();
    if (i < res->GetKey() && res->l) {
      res = res->l;
    }
    else if (res->r) {
      res = res->r;
    }
  }

  TTreeNode<TK, TV>* tmp = new TTreeNode<TK, TV>(i, 0);
  if (i < res->GetKey()) {
    res->l = tmp;
  }
  else {
    res->r = tmp;
  }
  return tmp->GetVal();
}

template<class TK, class TV>
TV TTreeMap<TK, TV>::Find(TK k) {
  TTreeNode<TK, TV>* res(root);
  while (res) {
    if (res->GetKey() == k) return res->GetVal();
    if (k < res->GetKey()) {
      res = res->l;
    }
    else {
      res = res->r;
    }
  }
  throw - 1;
}

template<class TK, class TV>
void TTreeMap<TK, TV>::Delete(TK k) {
  auto* res = this->root;
  TTreeNode<TK, TV>** prev = nullptr;

  while (res->r || res->l) {
    if (res->GetKey() == k) {
      if (res->l == nullptr && res->r == nullptr) {
        *prev = nullptr;
      }
      else if (res->l == nullptr) {
        *prev = res->r;
      }
      else if (res->r == nullptr) {
        *prev = res->l;
      }
      else {
        TTreeNode<TK, TV>* m = res->l;
        TTreeNode<TK, TV>** pm = &(res->l);

        while (m->r != nullptr)
        {
          pm = &(m->r);
          m = m->r;
        }
        *pm = m->l;
        *prev = m;
        m->r = res->r;
        m->l = res->l;
      }
      delete res;
      break;
    }
    if (k < res->GetKey() && res->l)
    {
      prev = &(res->l);
      res = res->l;
    }
    else
    {
      prev = &(res->r);
      res = res->r;
    }
  }
}

template<class TK, class TV>
void TTreeMap<TK, TV>::Add(TK k, TV v) {
  if (this->root == nullptr) {
    this->root = new TTreeNode<TK, TV>(k, v);
    this->count++;
    return;
  }

  TTreeNode<TK, TV>* node = new TTreeNode<TK, TV>(k, v);
  TTreeNode<TK, TV>* current = this->root;

  while (true) {
    TK current_key = current->GetKey();
    TK node_key = node->GetKey();
    if (node_key == current_key) {
      return;
    }
    else if (node_key > current_key) {
      if (current->r == nullptr) {
        current->r = node;
        this->count++;
        return;
      }
      else {
        current = current->r;
      }
    }
    else if (node_key < current_key) {
      if (current->l == nullptr) {
        current->l = node;
        this->count++;
        return;
      }
      else {
        current = current->l;
      }
    }
  }
}

template<class TK, class TV>
int TTreeMap<TK, TV>::GetCount() {
  return this->count;
}

template<class TK, class TV>
TTreeMapIter<TK, TV> TTreeMap<TK, TV>::Begin() {
  return TTreeMap::iterator(*this);
}


#endif