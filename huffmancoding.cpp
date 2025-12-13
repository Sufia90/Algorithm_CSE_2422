#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

// Node structure for Huffman Tree
struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;

    Node(char ch, int freq)
        : ch(ch), freq(freq), left(nullptr), right(nullptr) {}

    Node(char ch, int freq, Node* left, Node* right)
        : ch(ch), freq(freq), left(left), right(right) {}
};

// Comparator for priority queue (min-heap)
struct compare {
    bool operator()(Node* l, Node* r) {
        return l->freq > r->freq;
    }
};

// Function to generate Huffman Codes
void printCodes(Node* root, string str,
                unordered_map<char, string>& huffmanCode)
{
    if (root == nullptr)
        return;

    // Leaf node
    if (!root->left && !root->right) {
        huffmanCode[root->ch] = str;
    }

    printCodes(root->left, str + "0", huffmanCode);
    printCodes(root->right, str + "1", huffmanCode);
}

// Function to build Huffman Tree
void buildHuffmanTree(string text)
{
    unordered_map<char, int> freq;

    // Count frequency of each character
    for (char ch : text) {
        freq[ch]++;
    }

    priority_queue<Node*, vector<Node*>, compare> pq;

    // Create leaf nodes
    for (auto pair : freq) {
        pq.push(new Node(pair.first, pair.second));
    }

    // Build Huffman Tree
    while (pq.size() != 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        int sum = left->freq + right->freq;
        pq.push(new Node('\0', sum, left, right));
    }

    Node* root = pq.top();

    unordered_map<char, string> huffmanCode;
    printCodes(root, "", huffmanCode);

    cout << "\nHuffman Codes:\n";
    for (auto pair : huffmanCode) {
        cout << pair.first << " : " << pair.second << endl;
    }

    // Encoding
    cout << "\nOriginal String:\n" << text << endl;
    string encoded = "";
    for (char ch : text) {
        encoded += huffmanCode[ch];
    }
    cout << "\nEncoded String:\n" << encoded << endl;

    // Decoding
    cout << "\nDecoded String:\n";
    Node* curr = root;
    for (char bit : encoded) {
        if (bit == '0')
            curr = curr->left;
        else
            curr = curr->right;

        if (!curr->left && !curr->right) {
            cout << curr->ch;
            curr = root;
        }
    }
    cout << endl;
}

int main()
{
    string text;

    cout << "Enter a string: ";
    getline(cin, text);   // takes full user input (with spaces)

    buildHuffmanTree(text);
    return 0;
}
