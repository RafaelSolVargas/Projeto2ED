#include "trie.h"
#include <iostream>

int main() {

    using namespace std;

    string filename;
    string word;

    string keys[] = {"the", "a", "there", "answer", "any", "by", "bye", "their"};
    int n = sizeof(keys) / sizeof(keys[0]);

    Trie arv = Trie();

    for (int i = 0; i < n; i++)
        arv.insert(keys[i], i + 1, i + 1);

    // Verify if tree contains keys
    arv.contains("these") ? cout << "Yes\n" : cout << "No\n";
    arv.contains("their") ? cout << "Yes\n" : cout << "No\n";
    arv.contains("thaw") ? cout << "Yes\n" : cout << "No\n";

    // Process Keys
    arv.processPrefix("there");
    arv.processPrefix("their");
    arv.processPrefix("thaw");

    /* cin >> filename;  // entrada

    cout << filename << endl;  // esta linha deve ser removida

    while (1) {  // leitura das palavras ate' encontrar "0"
        cin >> word;
        if (word.compare("0") == 0) {
            break;
        }
        cout << word << endl;
    } */

    return 0;
}