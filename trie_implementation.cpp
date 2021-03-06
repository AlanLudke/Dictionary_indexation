//! trie_implementation.cpp
/*!
* \author Alan Djon Lüdke & Matheus Schaly
* \since 15/11/2018
* \version 1.0
* \copyright 2018
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Trie {
 public:
    //! Constructor
    explicit Trie() {
        root = new Node();
    }

    //! Inserts a word into the Trie
    /*!
        \param word the word to be inserted
        \param position the first character's position of the word
        \param length the length of the word's meaning
    */
    void insert(string word, unsigned long position, unsigned long length) {
        Node *current = root;
        for (size_t i = 0; i < word.length(); i++) {
            int index = word[i] - 'a';
            if (current -> children[index] == NULL) {
                current -> children[index] = new Node();
            }
            current = current -> children[index];
        }
        current -> position = position;
        current -> length = length;
    }

    //! Searchs for a word in the Trie
    /*!
        \param word the word to be search on the Trie
    */
    void search(string word) {
        Node *current = root;
        for (size_t i = 0; i < word.length(); i++) {
            int index = word[i] - 'a';
            if (current -> children[index] == NULL) {
                cout << "is not prefix" << endl;
                return;
            }
            current = current -> children[index];
        }
        if (current -> length == 0) {
            cout << "is prefix" << endl;
        } else {
            cout << current -> position << " " << current -> length << endl;
        }
    }

 private:
    struct Node {
        Node *children[26];
        unsigned long position {0};
        unsigned long length {0};

        //! Constructor
        explicit Node() {
            for (size_t i = 0; i < 26; i++) {
                children[i] = NULL;
            }
        }
    };

    Node *root;
};

int main() {

    string filename, word, dic_word = "";
    bool possible_dic_word = false;
    unsigned long position = 0;
    char character;

    cin >> filename;
    ifstream inFile;
    inFile.open(filename);
    Trie trie;
    fstream fin(filename, fstream::in);

    vector<string> dic_words;  // Vector containing the dictionary words
    vector<unsigned long> positions;  // Vector containing the initial positions of the dictionary words
    vector<unsigned long> lengths;  // Vector containing the length of the dictionary words

    //! Populates the dic_words and positions vectors
    while (fin >> noskipws >> character) {
        if (character == ']' && possible_dic_word == true) {
            positions.push_back(position - dic_word.length() - 1);
            dic_words.push_back(dic_word);
            possible_dic_word = false;
        }
        if (!(character == 'a' || character == 'b' || character == 'c' || character == 'd' || character == 'e' || character == 'f' ||
            character == 'g' || character == 'h' || character == 'i' || character == 'j' || character == 'k' || character == 'l' ||
            character == 'm' || character == 'n' || character == 'o' || character == 'p' || character == 'q' || character == 'r' ||
            character == 's' || character == 't' || character == 'u' || character == 'v' || character == 'w' || character == 'x' ||
            character == 'y' || character == 'z')) {
                possible_dic_word = false;
        }
        if (possible_dic_word == true) {
            dic_word += character;
        }
        if (character == '[') {
            possible_dic_word = true;
            dic_word = "";
        }
        position++;
    }

    //! Populates the length vector
    for (size_t i = 0; i < positions.size() - 1; i++) {
        lengths.push_back(positions.at(i+1) - positions.at(i) - 1);
    }
    lengths.push_back(position - positions.back() - 1);

    //! Inserts the words into the Trie
    for (size_t i = 0; i < dic_words.size(); i++) {
        trie.insert(dic_words.at(i), positions.at(i), lengths.at(i));
    }

    //! Expected results:
    cin >> filename;
    trie.search(filename);  // In order to consider the first word
    while (1) {
        cin >> word;
        if (word.compare("0") == 0) {
            break;
        }
        trie.search(word);
    }

}
