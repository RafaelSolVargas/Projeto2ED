#include <string>

using namespace std;

#define ALPHABET_SIZE 26

class Trie {
public:
  class Node {
  public:
    Node(char self_) {
      self = self_;
      posicao = 0;
      comprimento = 0;
    }

    char self;
    Node *children[ALPHABET_SIZE];
    unsigned long posicao;
    unsigned long comprimento;
  };

  ~Trie();
  void insert(string key, unsigned long posicao, unsigned long comprimento);
  bool search(string key);
  bool empty(Node *node);
  Node *remove(Node *node, string key, int depth = 0);

  Node *root = new Node((char)nullptr);
};

void Trie::insert(string key, unsigned long posicao,
                  unsigned long comprimento) {
  Node *current = root;

  for (int i = 0; i < key.length(); i++) {
    int index = key[i] - 'a';
    if (!current->children[index])
      current->children[index] = new Node(key[i]);
    current = current->children[index];
  }

  current->posicao = posicao;
  current->comprimento = comprimento;
}

bool Trie::search(string key) {
  Node *current = root;

  for (int i = 0; i < key.length(); i++) {
    int index = key[i] - 'a';
    if (!current->children[index])
      return false;
    current = current->children[index];
  }

  return (current != NULL && current->comprimento != 0);
}

bool Trie::empty(Trie::Node *node) {
  for (int i = 0; i < ALPHABET_SIZE; i++) {
    if (node->children[i])
      return false;
  }
  return true;
}

// Recursive function to delete a key from given Trie
Trie::Node *Trie::remove(Trie::Node *node, string key, int depth = 0) {
  // If tree is empty
  if (!node)
    return NULL;

  // If last character of key is being processed
  if (depth == key.size()) {
    // This node is no more end of word after
    // removal of given key
    if (node->posicao != 0 && node->comprimento != 0) {
      node->posicao = 0;
      node->comprimento = 0;
    }

    // If given is not prefix of any other word
    if (this->empty(node)) {
      delete node;
      node = NULL;
    }
    return node;
  }

  // If not last character, recur for the child
  // obtained using ASCII value
  int index = key[depth] - 'a';
  node->children[index] = remove(node->children[index], key, depth + 1);

  // If root does not have any child (its only child got
  // deleted), and it is not end of another word.
  if (this->empty(node) && node->posicao != 0 && node->comprimento != 0) {
    delete (node);
    node = NULL;
  }

  return node;
}