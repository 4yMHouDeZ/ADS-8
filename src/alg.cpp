// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  <algorithm>
#include  <string>
#include  <vector>
#include  "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);

    if (!file) {
        std::cout << "File error!" << std::endl;
        return;
    }
    std::string word;
    while(!file.eof()) {
      char ch=file.get();
      if (isalpha(ch)) {
        word += std::tolower(ch);
      } else {
        if (!word.empty()) {
          tree.insert(word);
        word.clear();
        }
      }
    }
    if (!word.empty()) tree.insert(word);
    file.close();
}

void printFreq(BST<std::string>& tree) {
  std::vector<Item> arr;
  tree.toVector(arr);
  std::sort(arr.begin(), arr.end(), [](Item a, Item b) {
    return a.value > b.value || a.key < b.key && a.value == b.value;
  });
  for (int i = 0; i < arr.size(); i++) {
    std::cout << arr[i].key << " - " << arr[i].value << " times" << std::endl;
  }
}
