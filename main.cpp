#include "trie.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
    // cin >> dictFileName; // entrada
    // string dictFileName;
    // cout << filename << endl; // esta linha deve ser removida
    fstream dictFile;
    string texto;
    // Lê o arquivo dic e coloca no objeto texto
    dictFile.open("Dictionaries/dic1.dic", ios::in);
    if (dictFile.is_open()) {
        string line;
        while (getline(dictFile, line)) {
            texto += line;
        }
        dictFile.close();
    }

    cout << texto << endl;
    // Processa a entrada e alimenta a árvore
    // string keys[] = {"bear", "beara", "there", "answer", "any", "by", "bye", "their"};
    // int n = sizeof(keys) / sizeof(keys[0]);
    Trie tree = Trie();
    // for (int i = 0; i < n; i++)
    //     tree.insert(keys[i], i + 1, i + 1);

    // cout << "Aoba" << endl;
    // string wor2d = texto.substr(1, 4);
    // cout << wor2d.compare("bear") << endl;

    // cout << "Ao2ba" << endl;
    int textSize = texto.size();
    int index = -1;

    size_t wordIndexStart;
    size_t wordIndexEnd;
    size_t wordMeaningIndexEnd;
    bool reading = false;

    for (; index < textSize;) {
        index++;
        if (texto[index] == '[') {
            if (reading) { // Finaliza o processo da palavra anterior
                // Atualiza o final da palavra atual
                wordMeaningIndexEnd = index - 1;
                size_t meaningSize = wordMeaningIndexEnd - wordIndexStart;
                size_t wordSize = wordIndexEnd - wordIndexStart;
                string word = texto.substr(wordIndexStart + 1, wordSize);

                // cout << wordSize << endl;
                // cout << meaningSize << endl;
                // cout << wordIndexStart << endl;
                // Insere na árvore
                cout << "Inserindo a palavra " << word << endl;
                tree.insert(word, wordIndexStart, meaningSize);
                // Atualiza para a próxima palavra
                wordIndexStart = index;
            } else { // Não estava lendo, começou agora
                wordIndexStart = index;
                reading = true;
            }
        } else if (texto[index] == ']') { // Terminou de ler a palavra
            wordIndexEnd = index - 1;
        }
    }

    // Para cada entrada processa se é uma palavra na árvore
    string word;
    while (1) { // leitura das palavras ate' encontrar "0"
        cin >> word;

        if (word.compare("0") == 0)
            break;

        tree.processPrefix(word);
    }

    return 0;
}