#ifndef TRIE_H
#define TRIE_H
#include "ProbSearch.h"
#include <iostream>
#include <string>
#include <utility>
class Trie{
 private:
  double value;
  bool isLeaf;
  Trie* character[128];
  int numLeaf;
  int numNode;
 public:
  Trie* parent;
  char charValue;
  Trie();
  ~Trie();
  bool add(std::pair<std::string, double>);
  unsigned int numLeaves();
  unsigned int numNodes();
  void printTrie();
  void printString();
  double search(std::string,ProbSearch&);
};
#endif
