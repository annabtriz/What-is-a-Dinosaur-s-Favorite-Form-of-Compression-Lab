#include "huffman.hpp"
#include <unordered_map>
#include <queue>
#include <string>
#include <stdexcept>

using namespace std;

struct CompareNode {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->freq > b->freq; //min-heap
    }
};

void buildCodes(HuffmanNode* node,
                const string& prefix,
                unordered_map<char, string>& codes)
{
    if (!node) return;

    if (!node->left && !node->right) {
        codes[node->ch] = prefix;
    }

    buildCodes(node->left, prefix + "0", codes);
    buildCodes(node->right, prefix + "1", codes);
}

HuffmanResult compress(const string& text)
{
    if (text.empty()) {
        return { {}, "" };
    }

    unordered_map<char, int> freq;
    for (char c : text)
        freq[c]++;

    priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareNode> pq;

    for (auto& p : freq)
        pq.push(new HuffmanNode(p.first, p.second));

    while (pq.size() > 1) {
        HuffmanNode* a = pq.top(); pq.pop();
        HuffmanNode* b = pq.top(); pq.pop();

        HuffmanNode* parent = new HuffmanNode('\0', a->freq + b->freq);
        parent->left = a;
        parent->right = b;

        pq.push(parent);
    }

    HuffmanNode* root = pq.top();

    unordered_map<char, string> codes;
    buildCodes(root, "", codes);

    string compressed;
    for (char c : text)
        compressed += codes[c];

    return { codes, compressed };
}

string decompress(const string& compressed,
                       const unordered_map<char, string>& codes)
{
    if (compressed.empty() || codes.empty())
        return "";

    unordered_map<string, char> rev;
    for (auto& p : codes)
        rev[p.second] = p.first;

    string result, buffer;

    for (char bit : compressed) {
        buffer.push_back(bit);
        if (rev.count(buffer)) {
            result.push_back(rev[buffer]);
            buffer.clear();
        }
    }

    return result;
}