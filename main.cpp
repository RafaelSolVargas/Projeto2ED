#include "trie.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void buildTrie(Trie *tree, string dictToOpen) {}

int main() {
    // Para cada entrada processa se é uma palavra na árvore
    Trie tree = Trie();
    string word;
    while (1) { // leitura das palavras ate' encontrar "0"
        cin >> word;

        if ((word.compare("dicionario1.dic") == 0) || (word.compare("dicionario2.dic") == 0)) {
            fstream dictFile;
            string texto;

            // Lê o arquivo dic e coloca no objeto texto
            dictFile.open(word, ios::in);
            if (dictFile.is_open()) {
                string line;
                while (getline(dictFile, line)) {
                    // cout << line << endl;
                    texto += line + '\n';
                }
                dictFile.close();
            }

            int textSize = texto.size();
            int index = -1;

            size_t wordIndexStart = 0;
            size_t wordIndexEnd;
            size_t wordMeaningIndexEnd;
            bool readingWord = true;
            for (; index < textSize;) {
                index++;

                // Terminou de processar uma palavra
                if (texto[index] == '\n' || index == textSize - 1) {
                    // Atualiza o final da palavra atual
                    wordMeaningIndexEnd = index;
                    // Calcula o tamanho do significado da palavra
                    size_t meaningSize = wordMeaningIndexEnd - wordIndexStart;
                    // Calcula o tamanho da palavra
                    size_t wordSize = wordIndexEnd - wordIndexStart;
                    // Extrai a palavra do texto para inserir na árvore
                    string word = texto.substr(wordIndexStart + 1, wordSize);

                    // Verifica se é uma palavra do dicionário mesmo
                    // lenWord = word.length();
                    // for ()

                    tree.insert(word, wordIndexStart, meaningSize);

                    wordIndexStart = index + 1;
                    readingWord = true;
                    // } else if (texto[index] == '[' && readingWord) {
                    // Começa a ler uma palavra
                    // readingWord = true;
                    // Terminou de ler a palavra
                } else if (texto[index] == ']' && readingWord) {
                    readingWord = false;
                    wordIndexEnd = index - 1;
                }
            }
            continue;
        }

        if (word.compare("0") == 0)
            break;

        tree.processPrefix(word);
    }

    return 0;
}