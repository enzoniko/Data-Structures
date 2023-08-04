// Copyright [2023] <Enzo Nicolás Spotorno Bieger>
#include <algorithm>
#include "array_list.h"
namespace structures {

template <typename T> class AVLTree {
public:
  AVLTree();

  ~AVLTree();

  void insert(const T &data);

  void remove(const T &data);

  bool contains(const T &data) const;

  bool empty() const;

  std::size_t size() const;

  int height() const;

  ArrayList<T> pre_order() const;

  ArrayList<T> in_order() const;

  ArrayList<T> post_order() const;

private:
  struct Node {
    T data;
    int height_;
    Node *left;
    Node *right;
    Node() {
      left = nullptr;
      right = nullptr;
      height_ = 0;
    }
    explicit Node(const T &data_) {
      data = data_;
      height_ = 0;
      left = nullptr;
      right = nullptr;
    }

    Node *insert(const T &data_, Node *arv) {
      Node *arv_rodada;
      if (arv == nullptr) {
        arv = new Node(data_);
      } else {
        if (data_ < arv->data) {
          arv->left = insert(data_, arv->left);
          if ((height(arv->left) - height(arv->right)) > 1) {
            if (data_ < arv->left->data) {
              arv_rodada = simpleLeft(arv);
            } else {
              arv_rodada = doubleLeft(arv);
            }
            arv = arv_rodada;
          } else {
            arv->height_ = std::max(height(arv->left), height(arv->right)) + 1;
          }
        } else if (data_ > arv->data) {
          arv->right = insert(data_, arv->right);
          if ((height(arv->right) - height(arv->left)) > 1) {
            if (data_ > arv->right->data) {
              arv_rodada = simpleRight(arv);
            } else {
              arv_rodada = doubleRight(arv);
            }
            arv = arv_rodada;
          } else {
            arv->height_ = std::max(height(arv->left), height(arv->right)) + 1;
          }
        } else {
          throw std::out_of_range("Chave já na árvore");
        }
      }
      return arv;
    }
    T &minimo() {
      if (left == nullptr) {
        return data;
      } else {
        return left->minimo();
      }
    }

    Node *atualizaZZ(Node *arv) {
      // Atualiza alturas
      arv->height_ = std::max(height(arv->left), height(arv->right)) + 1;
      // Verifica se tem algum desbalanceamento
      // Corrige o possível desbalanceamento
      if ((height(arv->left) - height(arv->right)) > 1) {
        if (height(arv->left->left) > height(arv->left->right)) {
          arv = simpleLeft(arv);
        } else {
          arv = doubleLeft(arv);
        }
      } else if ((height(arv->right) - height(arv->left)) > 1) {
        if (height(arv->right->right) > height(arv->right->left)) {
          arv = simpleRight(arv);
        } else {
          arv = doubleRight(arv);
        }
      }
      return arv;
    }

    Node *remove(const T &data_, Node *arv) {
      Node *filho;
      if (arv == nullptr) {
        return arv;
      } else {
        if (data_ < arv->data) {
          arv->left = remove(data_, arv->left);
          arv = atualizaZZ(arv);
          return arv;
        } else if (data_ > arv->data) {
          arv->right = remove(data_, arv->right);
          arv = atualizaZZ(arv);
          return arv;
        } else {
          if (arv->right != nullptr && arv->left != nullptr) {
            arv->data = arv->right->minimo();
            arv->right = remove(arv->data, arv->right);
            arv = atualizaZZ(arv);
            return arv;
          } else {
            if (arv->right != nullptr) {
              filho = arv->right;
              return filho;
            } else if (arv->left != nullptr) {
              filho = arv->left;
              return filho;
            } else {
              delete arv;
              return nullptr;
            }
          }
        }
        return nullptr;
      }
    }

    bool contains(const T &data_) const {
        if (data_ < data) {
            if (left != nullptr) {
                return left->contains(data_);
            } else {
                return false;
            }
        } else if (data_ > data) {
            if (right != nullptr) {
                return right->contains(data_);
            } else {
                return false;
            }
        } else {
            return true;
        }
    }

    // void updateHeight();

    Node *simpleLeft(Node *k2) {
      Node *k1;
      k1 = k2->left;
      k2->left = k1->right;
      k1->right = k2;
      k2->height_ = std::max(height(k2->left), height(k2->right)) + 1;
      k1->height_ = std::max(height(k1->left), height(k2)) + 1;
      return k1;
    }

    Node *simpleRight(Node *k2) {
      Node *k1;
      k1 = k2->right;
      k2->right = k1->left;
      k1->left = k2;
      k2->height_ = std::max(height(k2->right), height(k2->left)) + 1;
      k1->height_ = std::max(height(k1->right), height(k2)) + 1;
      return k1;
    }

    Node *doubleLeft(Node *k3) {
      k3->left = simpleRight(k3->left);
      return simpleLeft(k3);
    }

    Node *doubleRight(Node *k3) {
      k3->right = simpleLeft(k3->right);
      return simpleRight(k3);
    }

    void pre_order(ArrayList<T> &v) const {
      v.push_back(data);
      if (left != nullptr) {
        left->pre_order(v);
      }
      if (right != nullptr) {
        right->pre_order(v);
      }
    }

    void in_order(ArrayList<T> &v) const {
      if (left != nullptr) {
        left->in_order(v);
      }
      v.push_back(data);
      if (right != nullptr) {
        right->in_order(v);
      }
    }

    void post_order(ArrayList<T> &v) const {
      if (left != nullptr) {
        left->post_order(v);
      }
      if (right != nullptr) {
        right->post_order(v);
      }
      v.push_back(data);
    }
    // int height() { return height_; }
    int height(Node *self) {
      if (self == nullptr) {
        return -1;
      }
      return self->height_;
    }
    // void clear() {
    //     if (left != nullptr) {
    //         left->clear();
    //     }
    //     if (right != nullptr) {
    //         right->clear();
    //     }
    //     delete this;
    // }
  };

  Node *root{nullptr};
  std::size_t size_{0u};
};

}  // namespace structures

template <typename T> structures::AVLTree<T>::AVLTree() {
  // root = new Node;
  size_ = 0;
}

template <typename T> structures::AVLTree<T>::~AVLTree() {
  // root->clear();
  size_ = 0;
}

template <typename T> void structures::AVLTree<T>::insert(const T &data) {
  if (!contains(data)) {
      size_++;
  }
  root = root->insert(data, root);
}

template <typename T> void structures::AVLTree<T>::remove(const T &data) {
  if (contains(data)) {
      root = root->remove(data, root);
      size_--;
  }
}

template <typename T>
bool structures::AVLTree<T>::contains(const T &data) const {
    if (root == nullptr) {
        return false;
    } else {
        if (data < root->data) {
            if (root->left != nullptr) {
                return root->left->contains(data);
            } else {
                return false;
            }
        } else if (data > root->data) {
            if (root->right != nullptr) {
                return root->right->contains(data);
            } else {
                return false;
            }
        } else {
            return true;
        }
    }
}

template <typename T> int structures::AVLTree<T>::height() const {
  return root->height(root);
}

template <typename T> bool structures::AVLTree<T>::empty() const {
  return size_ == 0;
}

template <typename T> std::size_t structures::AVLTree<T>::size() const {
//   if (not empty()) {
//     return root->data;
//   }
    return size_;
}

template <typename T>
structures::ArrayList<T> structures::AVLTree<T>::pre_order() const {
  structures::ArrayList<T> list(size_);
  if (root != nullptr) {
    list.push_back(root->data);
    if (root->left != nullptr) {
      root->left->pre_order(list);
    }
    if (root->right != nullptr) {
      root->right->pre_order(list);
    }
  }
  return list;
}

template <typename T>
structures::ArrayList<T> structures::AVLTree<T>::in_order() const {
  structures::ArrayList<T> list(size_);
  if (root != nullptr) {
    if (root->left != nullptr) {
      root->left->in_order(list);
    }
    list.push_back(root->data);
    if (root->right != nullptr) {
      root->right->in_order(list);
    }
  }
  return list;
}

template <typename T>
structures::ArrayList<T> structures::AVLTree<T>::post_order() const {
  structures::ArrayList<T> list(size_);
  if (root != nullptr) {
    if (root->left != nullptr) {
      root->left->post_order(list);
    }
    if (root->right != nullptr) {
      root->right->post_order(list);
    }
    list.push_back(root->data);
  }
  return list;
}
