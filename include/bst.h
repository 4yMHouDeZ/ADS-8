// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <vector>
#include <string>
#include <algorithm>

struct Item {
  std::string key;
  unsigned int value;
};

template <typename T>
class BST {
 private:
  struct Node {
    T key;
    unsigned int value;
    Node* left = nullptr;
    Node* right = nullptr;
  };
  Node* root;
  int depth(Node* current, int count) const {
    if (current == nullptr)
      return count;
    count++;
    return std::max(depth(current->left, count), depth(current->right, count));
  }
  void remove(Node* current) {
    if (current->left != nullptr)
      remove(current->left);
    if (current->right != nullptr)
      remove(current->right);
    delete current;
  }
  void reqToVec(std::vector<Item>& arr, Node* current) {
    if (current == nullptr) return;
    arr.push_back({current->key, current->value});
    reqToVec(arr, current->left);
    reqToVec(arr, current->right);
  }

 public:
  BST() : root(nullptr) {}
  ~BST() {
    remove(root);
  }
  void insert(const T& key) {
    if (root == nullptr) {
      root = new Node {key, 1};
      return;
    }
    Node* parent = nullptr;
    Node* current = root;
    while (current != nullptr) {
      if (key == current->key) {
        current->value++;
        return;
      } else if (key < current->key) {
        parent = current;
        current = current->left;
      } else {
        parent = current;
        current = current->right;
      }
    }
    if (key < parent->key)
      parent->left = new Node {key, 1};
    else
      parent->right = new Node {key, 1};
  }

  int depth() const {
    return depth(root, -1);
  }

  int search(const T& key) const {
    Node* current = root;
    while (current != nullptr) {
      if (key == current->key)
        return current->value;
      else if (key < current->key)
        current = current->left;
      else
        current = current->right;
    }
    return 0;
  }
  void toVector(std::vector<Item>& arr) {
    reqToVec(arr, root);
  }
};

#endif  // INCLUDE_BST_H_
