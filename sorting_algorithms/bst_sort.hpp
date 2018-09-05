#ifndef _HOME_ARCHLINUX_SORTING_ALGORITHMS_BST_SORT_HPP
#define _HOME_ARCHLINUX_SORTING_ALGORITHMS_BST_SORT_HPP
#include <gsl/pointers>
#include <vector>

template <typename value_type> class BSTNode {
  value_type key;
  BSTNode<value_type>* parent;
  BSTNode<value_type>* left_child;
  BSTNode<value_type>* right_child;

public:
  BSTNode();
  BSTNode(value_type);

  void SetKey(value_type);
  void SetParent(BSTNode<value_type>*);
  void SetLeftChild(BSTNode<value_type>*);
  void SetRightChild(BSTNode<value_type>*);

  value_type GetKey();
  BSTNode<value_type>* GetParent();
  BSTNode<value_type>* GetLeftChild();
  BSTNode<value_type>* GetRightChild();
};

template <typename value_type> class BST {
  BSTNode<value_type>* root;

public:
  void SetRoot(BSTNode<value_type>*);
  BSTNode<value_type>* GetRoot();
  /* void InOrderTreeWalk(BSTNode<value_type>*); */
  void BSTSort(BSTNode<value_type>*,std::vector<value_type> &);
  BSTNode<value_type>* TreeMinimum(BSTNode<value_type>*);
  BSTNode<value_type>* TreeMaximum(BSTNode<value_type>*);
  BSTNode<value_type>* TreeSearch(BSTNode<value_type>*, value_type);
  BSTNode<value_type>* TreeSuccessor(BSTNode<value_type>*);
  void TreeInsert(BSTNode<value_type>*);
  BST();
  BST(BSTNode<value_type>*);
};

/* template <typename value_type> */
/* void BST<value_type>::InOrderTreeWalk(BSTNode<value_type>* x) { */
/*   if (x != nullptr) { */
/*     InOrderTreeWalk(x->GetLeftChild()); */
/*     std::cout << x->GetKey() << " "; */
/*     InOrderTreeWalk(x->GetRightChild()); */
/*   } */
/* } */

template <typename value_type>
void BST<value_type>::BSTSort(BSTNode<value_type> *x,
                              std::vector<value_type> &v) {
  if (x != nullptr) {
    BSTSort(x->GetLeftChild(),v);
    v.push_back(x->GetKey());
    BSTSort(x->GetRightChild(),v);
  }
}

template <typename value_type> BST<value_type>::BST() {
  this->SetRoot(nullptr);
}

template <typename value_type>
BSTNode<value_type>* BST<value_type>::TreeMinimum(BSTNode<value_type>* x) {
  while (x->GetLeftChild() != nullptr) {
    x = x->GetLeftChild();
  }
  return x;
}

template <typename value_type>
BSTNode<value_type>* BST<value_type>::TreeMaximum(BSTNode<value_type>* x) {
  while (x->GetRightChild() != nullptr) {
    x = x->GetRightChild();
  }
  return x;
}

template <typename value_type>
BSTNode<value_type>* BST<value_type>::TreeSearch(BSTNode<value_type>* x,
                                                 value_type k) {
  if (x == nullptr || k == x->GetKey()) {
    return x;
  }
  if (k < x->GetKey()) {
    return TreeSearch(x->GetLeftChild(), k);
  }
  return TreeSearch(x->GetRightChild(), k);
}

template <typename value_type>
BSTNode<value_type>* BST<value_type>::TreeSuccessor(BSTNode<value_type>* x) {
  if (x->GetRightChild() != nullptr) {
    return TreeMinimum(x->GetRightChild());
  }
  BSTNode<value_type>* y = x->GetParent();
  while (y != nullptr && x == y->GetRightChild()) {
    x = y;
    y = y->GetParent();
  }
  return y;
}

template <typename value_type>
BST<value_type>::BST(BSTNode<value_type>* x) {
  this->SetRoot(x);
}

template <typename value_type>
void BST<value_type>::SetRoot(BSTNode<value_type>* x) {
  this->root = x;
}

template <typename value_type>
BSTNode<value_type>* BST<value_type>::GetRoot() {
  return this->root;
}

template <typename value_type>
void BST<value_type>::TreeInsert(BSTNode<value_type>* z){
  BSTNode<value_type>* y = nullptr;
  BSTNode<value_type>* x = this->GetRoot();
  while (x != nullptr) {
    y = x;
    if (z->GetKey() < x->GetKey()) {
      x = x->GetLeftChild();
    } else {
      x = x->GetRightChild();
    }
  }
  z->SetParent(y);
  if (y == nullptr) {
    this->SetRoot(z);
  } else if (z->GetKey() < y->GetKey()) {
    y->SetLeftChild(z);
  } else {
    y->SetRightChild(z);
  }
}

template <typename value_type> BSTNode<value_type>::BSTNode() {
  this->SetKey(0);
  this->SetParent(nullptr);
  this->SetLeftChild(nullptr);
  this->SetRightChild(nullptr);
}

template <typename value_type> BSTNode<value_type>::BSTNode(value_type k) {
  this->SetKey(k);
  this->SetParent(nullptr);
  this->SetLeftChild(nullptr);
  this->SetRightChild(nullptr);
}

template <typename value_type> value_type BSTNode<value_type>::GetKey() {
  return this->key;
}

template <typename value_type>
BSTNode<value_type>* BSTNode<value_type>::GetParent() {
  return this->parent;
}

template <typename value_type>
BSTNode<value_type>* BSTNode<value_type>::GetLeftChild() {
  return this->left_child;
}

template <typename value_type>
BSTNode<value_type>* BSTNode<value_type>::GetRightChild() {
  return this->right_child;
}

template <typename value_type> void BSTNode<value_type>::SetKey(value_type k) {
  this->key = k;
}

template <typename value_type>
void BSTNode<value_type>::SetParent(BSTNode<value_type>* x) {
  this->parent = x;
}

template <typename value_type>
void BSTNode<value_type>::SetLeftChild(BSTNode<value_type>* x) {
  this->left_child = x;
}

template <typename value_type>
void BSTNode<value_type>::SetRightChild(BSTNode<value_type>* x) {
  this->right_child = x;
}

template <typename value_type>
gsl::owner<BSTNode<value_type> *> create_BSTNode(value_type k) {
  return gsl::owner<BSTNode<value_type> *>(new BSTNode<value_type>(k));
}

template <typename value_type>
void Transplant(BST<value_type> &T, BSTNode<value_type>* u, BSTNode<value_type>* v){
  if (u->GetParent() == nullptr) {
    T.SetRoot(v);
  } else if (u == u->GetParent()->GetLeftChild()) {
    u->GetParent()->SetLeftChild(v);
  } else {
    u->GetParent()->SetRightChild(v);
  }
  if (v != nullptr) {
    v->SetParent(u->GetParent());
  }
}

template <typename value_type>
void TreeDelete(BST<value_type> &T, BSTNode<value_type>* z){
  if (z->GetLeftChild() == nullptr) {
    Transplant(T,z,z->GetRightChild());
  } else if (z->GetRightChild() == nullptr) {
    Transplant(T,z,z->GetLeftChild());
  } else {
    BSTNode<value_type>* y = T.TreeMinimum(z->GetRightChild());
    if (y->GetParent() != z) {
      Transplant(T,y,y->GetRightChild());
      y->SetRightChild(z->GetRightChild());
      y->GetRightChild()->SetParent(y);
    }
    Transplant(T,z,y);
    y->SetLeftChild(z->GetLeftChild());
    y->GetLeftChild()->SetParent(y);
  }
}

template <typename value_type> void bst_sort (std::vector<value_type> &v) {
  BST<value_type> T;
  std::vector<gsl::owner<BSTNode<value_type> *>> bstnode_vector;
  bstnode_vector.resize(v.size());
  bstnode_vector.reserve(v.size());
  std::fill(bstnode_vector.begin(), bstnode_vector.end(), nullptr);

  for (typename std::vector<BSTNode<value_type> *>::size_type i = 0;
       i < v.size(); i++) {
    bstnode_vector[i] = gsl::owner<BSTNode<value_type> *>(create_BSTNode(v[i]));
  }
  for (auto elem : bstnode_vector) {
    T.TreeInsert(elem);
  }

  v.clear();
  T.BSTSort(T.GetRoot(),v);
  v.shrink_to_fit();

  (void) v;
}

#endif // _HOME_ARCHLINUX_SORTING_ALGORITHMS_BST_SORT_HPP
