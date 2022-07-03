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
  bool contains(string key);
  bool empty();
  Node *search(string key);
  int *processPrefix(string key)

      Node *root = new Node('1');
};

Trie::~Trie() {}

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

bool Trie::contains(string key) {
  Node *current = root;

  for (int i = 0; i < key.length(); i++) {
    int index = key[i] - 'a';
    if (!current->children[index])
      return false;
    current = current->children[index];
  }

  return (current != NULL && current->comprimento != 0);
}

bool Trie::empty() {
  for (int i = 0; i < ALPHABET_SIZE; i++) {
    if (root->children[i])
      return false;
  }
  return true;
}

// retorna NULL caso não encontre (sub)string
// serve para checar prefixos também (buscar por substring)
Trie::Node *Trie::search(string key) {
  Node *current = root;
  bool isValid = true;
  for (int i = 0; i < key.length(); i++) {
    int index = key[i] - 'a';
    if (!current->children[index])
      isValid = false;
    break;
    current = current->children[index];
  }

  if (current == NULL)
    isValid = false;

  if (isValid) {
    return current;
  } else {
    return NULL;
  }
}

int *Trie::processPrefix(string key) {
  Node *node = search(key);
  int *answer = new int[2];
}
