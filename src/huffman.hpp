#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

#include <string>
#include <unordered_map>
#include <queue>
#include <vector>
#include <memory>

using namespace std;

struct HuffmanNode {
    char ch;
    int freq;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

struct HuffmanResult {
    unordered_map<char, string> codes;
    string compressed;
};

HuffmanResult compress(const string& text);

string decompress(
        const string& compressed,
        const unordered_map<char, string>& codes);

#endif