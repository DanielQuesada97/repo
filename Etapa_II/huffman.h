#ifndef ALGORITMOS_HUFFMAN_H
#define ALGORITMOS_HUFFMAN_H

#include <iostream>

// Definición de la estructura del nodo del árbol de Huffman
struct TreeNode {
    TreeNode* parent;
    TreeNode* left;
    TreeNode* right;
    std::string name;
    double probability;

    TreeNode(std::string n, double prob);
};

// Definición de la clase para el montículo de mínimos
class MinHeap {
private:
    TreeNode** heap;
    int capacity;

    void resize();
    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    MinHeap();
    void insert(TreeNode* node);
    TreeNode* extractMin();
    bool isEmpty() const;
    ~MinHeap();

    int size;
};

// Definición de la clase que encapsula las funciones de Huffman
class Huffman {
public:
    static TreeNode* buildHuffmanTree(MinHeap& minHeap);
    static void assignHuffmanCodes(TreeNode* root, const std::string& code, std::ostream& output);
};

#endif //ALGORITMOS_HUFFMAN_H

