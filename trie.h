#include <iostream>
#include <string>

using namespace std;

#define ALPHABET_SIZE 26

class Trie {
public:
    class Node {
    public:
        Node(char charValue) {
            for (int i = 0; i < ALPHABET_SIZE; i++) {
                this->children[i] = NULL;
            }
            selfValue = charValue;
            position = 0;
            lenght = 0;
        }

        ~Node() {
            for (int i = 0; i < ALPHABET_SIZE; i++) {
                if (this->children[i])
                    delete this->children[i];
            }
        }

        int getQuantChildren() {
            int quant = 0;

            // Se o prefixo já for uma palavra, conta como uma
            if (this->lenght != 0) {
                quant++;
            }

            for (int i = 0; i < ALPHABET_SIZE; i++) {
                if (this->children[i]) {
                    quant += this->children[i]->getQuantChildren();
                }
            }

            return quant;
        }

        char selfValue;

        Node *children[ALPHABET_SIZE];

        unsigned long position;

        unsigned long lenght;
    };

    Trie() {
        root = new Node('1');
    }

    ~Trie() {
        delete root;
    }

    void insert(string key, unsigned long position, unsigned long lenght);

    bool contains(string key);

    bool empty();

    Node *search(string key);

    void processPrefix(string key);

    Node *root;
};

void Trie::insert(string key, unsigned long position, unsigned long lenght) {
    Node *current = root;

    // Caminha pela árvore criando os nodes necessários para chegar no leaf node da palavra
    for (int i = 0; i < key.length(); i++) {
        int index = key[i] - 'a';

        // cout << key[i] << endl;
        // cout << index << endl;
        // Se ainda não possuir filho para o char específico
        if (!current->children[index]) {
            current->children[index] = new Node(key[i]);
        }
        // Passa para o filho
        current = current->children[index];
    }
    // cout << "C" << endl;
    // Já no leaf node da palavra atualiza a posição e comprimento da palavra no dicionário
    current->position = position;
    current->lenght = lenght;
}

bool Trie::contains(string key) {
    Node *current = root;

    for (int i = 0; i < key.length(); i++) {
        int index = key[i] - 'a';
        if (!current->children[index])
            return false;
        current = current->children[index];
    }

    // Verifica o lenght pois a palavra não existir na árvore e ser prefixo de outra existente
    return (current != NULL && current->lenght != 0);
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
        if (!current->children[index]) {
            isValid = false;
            break;
        }
        current = current->children[index];
    }

    if (current == NULL)
        isValid = false;

    if (isValid)
        return current;
    else
        return NULL;
}

void Trie::processPrefix(string key) {
    Node *node = search(key);

    if (node == NULL) {
        cout << key << " is not prefix\n";
        return;
    }

    int quantWords = node->getQuantChildren();
    cout << key << " is prefix of " << quantWords << " words\n";

    if (node->lenght != 0) {
        cout << key << " is at ";
        printf("(%ld,%ld)\n", node->position, node->lenght);
    }
}
