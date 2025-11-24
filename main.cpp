#include <iostream>
#include "src/huffman.hpp"

using namespace std;

int main() {
    string text;
    cout << "Enter text to compress: ";
    getline(cin, text);

    HuffmanResult result = compress(text);

    cout << "\nHuffman Codes:\n";
    for (auto& p : result.codes) {
        cout << "'" << p.first << "' : " << p.second << "\n";
    }

    cout << "\nCompressed:\n"
              << result.compressed << "\n";


    string restored = decompress(result.compressed, result.codes);
    cout << "\nDecompressed:\n"
              << restored << "\n";

    return 0;
}