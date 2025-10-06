#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;

// Node for Huffman Tree
struct HuffNode {
    char symbol;
    int freq;
    HuffNode *left, *right;

    HuffNode(char s, int f) {
        symbol = s;
        freq = f;
        left = right = nullptr;
    }
};

// Comparator for priority queue
struct Compare {
    bool operator()(HuffNode* n1, HuffNode* n2) {
        return n1->freq > n2->freq;
    }
};

// Preorder traversal for Huffman Codes
void printCodes(HuffNode* root, string code) {
    if (!root) return;

    if (root->symbol != '$') {
        cout << root->symbol << " : " << code << endl;
    }

    printCodes(root->left, code + "0");
    printCodes(root->right, code + "1");
}

// Build Huffman Tree
HuffNode* buildTree(string S, vector<int> freq) {
    priority_queue<HuffNode*, vector<HuffNode*>, Compare> pq;

    for (int i = 0; i < S.size(); i++) {
        pq.push(new HuffNode(S[i], freq[i]));
    }

    while (pq.size() > 1) {
        HuffNode* n1 = pq.top(); pq.pop();
        HuffNode* n2 = pq.top(); pq.pop();

        HuffNode* merged = new HuffNode('$', n1->freq + n2->freq);
        merged->left = n1;
        merged->right = n2;
        pq.push(merged);
    }

    return pq.top();
}

int main() {
    string S = "abcdef";
    vector<int> freq = {5, 9, 12, 13, 16, 45};

    cout << "Huffman Codes (Preorder Traversal):\n";
    HuffNode* root = buildTree(S, freq);
    printCodes(root, "");

    return 0;
}
