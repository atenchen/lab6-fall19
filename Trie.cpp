#include "Trie.h"
#include <iostream>
#include <string>
#include <utility>

Trie::Trie(){
  parent = nullptr;
  this->charValue = ' ';
  this ->isLeaf = false;
  for(int i = 0; i < 128; i ++){
    this->character[i] = nullptr;
  }
}
Trie::~Trie(){
  for(int i = 0; i < 128; i++){
    if(character != nullptr){
      delete character[i];
    }
  }
}
bool Trie::add(std::pair<std::string, double> val){
  if(val.first.size() <=0){
    return false;
  }
  Trie* current = this;
  std::string str = val.first;
  for(unsigned int i = 0; i < str.size(); i ++){
    if(current->character[int(str[i])] == nullptr){
      current->character[int(str[i])] = new Trie();
      current->character[int(str[i])]->charValue = val.first[i];
      current->character[int(str[i])]->parent = current;
    }
    current = current->character[int(str[i])];
  }
  current->isLeaf = true;
  current->value = val.second;
  return true;
}
unsigned int Trie::numLeaves(){
  unsigned int numLeaf = 0;
  if(this->isLeaf){
    numLeaf++;
  }
  for(int i = 0; i < 128; i++){
    if(character[i] != nullptr){
      numLeaf += character[i]->numLeaves();
    }
  }
  return numLeaf;
}
unsigned int Trie::numNodes(){
  unsigned int numNode = 0;
  if(this->isLeaf){
    numNode++;
  }
  for(int i = 0; i < 128; i++){
    if(character[i] != nullptr){
      numNode ++;
      numNode += character[i]->numNodes();
    }
  }
  return numNode;
}
void Trie:: printTrie(){
  if(this->isLeaf){
    std::cout << this->value;
    this->printString();
    std::cout<<"\n";
  }
  for(int i = 0; i < 128; i++){
    if(character[i] != nullptr){
      character[i]->printTrie();
    }
  }
}
void Trie:: printString(){
  if(parent != nullptr){
    parent->printString();
  }
  std::cout << charValue;
}
double Trie::search(std::string str, ProbSearch& p){
  Trie * current = this;
  for(unsigned int i = 0; i < str.length();i++){
    if(current->character[int(str[i])] == nullptr){
      p.prob = -1;
      return p.prob;
    }
    current = current->character[int(str[i])];
    p.steps_taken++;
  }
  p.prob = current->value;
  return current->value;
}
