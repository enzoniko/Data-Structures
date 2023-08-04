// Copyright [2023] Enzo Nicolás Spotorno Bieger
#include "array_list.h"

namespace structures {

template<typename T>
class BinaryTree {
 public:
    BinaryTree();
    ~BinaryTree();

    void insert(const T& data);

    void remove(const T& data);

    bool contains(const T& data) const;

    bool empty() const;

    std::size_t size() const;

    ArrayList<T> pre_order() const;

    ArrayList<T> in_order() const;

    ArrayList<T> post_order() const;

 private:
    struct Node {
        Node() {}

        T data;
        Node* left{nullptr};
        Node* right{nullptr};

        explicit Node(const T& data_) {
            data = data_;
        }

        void insert(const T& data_) {
            if (data_ < data) {
                if (left == nullptr) {
                    Node * novo = new Node(data_);
                    left = novo;
                } else {
                    left->insert(data_);
                }
            } else {
               if (right == nullptr) {
                    Node * novo = new Node(data_);
                    right = novo;
                } else {
                    right->insert(data_);
                }
            }
        }

        T& minimo() {
            if (left == nullptr) {
                return data;
            } else {
                return left->minimo();
            }
        }
        // T& minimo() {
        //     Node * tmp = left;
        //     if (tmp == nullptr) {
        //         return data;
        //     }
        //     while (tmp->left != nullptr) {
        //         tmp = tmp->left;
        //     }
        //     return tmp->data;
        // }
        Node * remove(const T& data_, Node * self) {
            // !!!
            if (self == nullptr) {
                return self;
            } else {
                if (data_ < data) {
                    left = left->remove(data_, left);
                    return self;
                } else if (data_ > data) {
                    right = right->remove(data_, right);
                    return self;
                } else {
                    if (right != nullptr && left != nullptr) {
                        data = right->minimo();
                        right = right->remove(data, right);
                        return self;
                    } else if (right != nullptr) {
                        delete self;
                        return right;
                    } else if (left != nullptr) {
                        delete self;
                        return left;
                    } else {
                        delete self;
                        return nullptr;
                    }
                }
                return nullptr;
            }
        }
        bool contains(const T& data_) const {
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

        void pre_order(ArrayList<T>& v) const {
            v.push_back(data);
            if (left != nullptr) {
                left->pre_order(v);
            }
            if (right != nullptr) {
                right->pre_order(v);
            }
        }

        void in_order(ArrayList<T>& v) const {
            if (left != nullptr) {
                left->in_order(v);
            }
            v.push_back(data);
            if (right != nullptr) {
                right->in_order(v);
            }
        }

        void post_order(ArrayList<T>& v) const {
            if (left != nullptr) {
                left->post_order(v);
            }
            if (right != nullptr) {
                right->post_order(v);
            }
            v.push_back(data);
        }

        void remove_post_order(Node * self) const {
            if (left != nullptr) {
                left->remove_post_order(left);
            }
            if (right != nullptr) {
                right->remove_post_order(right);
            }
            delete self;
        }
    };

    Node* root;
    std::size_t size_;
};

}  // namespace structures

template<typename T>
structures::BinaryTree<T>::BinaryTree() {
    root = new Node;
    root->left = nullptr;
    root->right = nullptr;
    size_ = 0;
}

template<typename T>
structures::BinaryTree<T>::~BinaryTree() {
    root->remove_post_order(root);
    size_ = 0;
}

template<typename T>
void structures::BinaryTree<T>::insert(const T& data) {
    if (empty()) {  // !!!
        root = new Node(data);
    } else if (data < root->data) {
        if (root->left == nullptr) {
            Node * novo = new Node(data);
            root->left = novo;
        } else {
            root->left->insert(data);
        }
    } else {
        if (root->right == nullptr) {
            Node * novo = new Node(data);
            root->right = novo;
        } else {
            root->right->insert(data);
        }
    }
    size_++;  // !!!
}

template<typename T>
void structures::BinaryTree<T>::remove(const T& data) {
    // !!!
    if (contains(data)) {
        root->remove(data, root);
        size_--;
    }
}


template<typename T>
bool structures::BinaryTree<T>::contains(const T& data) const {
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

template<typename T>
bool structures::BinaryTree<T>::empty() const {  // !!!
    return size_ == 0;
}

template<typename T>
structures::ArrayList<T> structures::BinaryTree<T>::pre_order() const {
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

template<typename T>
structures::ArrayList<T> structures::BinaryTree<T>::in_order() const {
    structures::ArrayList<T> list(size_);;
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

template<typename T>
structures::ArrayList<T> structures::BinaryTree<T>::post_order() const {
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


template<typename T>
std::size_t structures::BinaryTree<T>::size() const {
    return size_;
}
