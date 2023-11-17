#include <iostream>
#include "huffman.h"

int main() {
    // Nombres correspondientes al alfabeto griego
    std::string names[] = {
            "Alpha", "Beta", "Gamma", "Delta", "Epsilon", "Zeta",
            "Eta", "Theta", "Iota", "Kappa", "Lambda", "Mu",
            "Nu", "Xi", "Omicron", "Pi", "Rho", "Sigma",
            "Tau", "Upsilon", "Phi", "Chi", "Psi", "Omega"
    };

    // Valores de probabilidad del alfabeto griego
    double probabilities[24] = {
            0.99, 0.25, 0.08, 0.60, 0.16, 0.53,
            0.57, 0.13, 0.87, 0.21, 0.27, 0.54,
            0.67, 0.03, 0.95, 0.83, 0.62, 0.94,
            0.21, 0.30, 0.08, 0.32, 0.85, 0.25
    };

    MinHeap minHeap;

    // Crear nodos y agregarlos a la cola de prioridad (Montículo de Mínimos)
    for (int i = 0; i < 24; i++) {
        std::string name = names[i];
        TreeNode* node = new TreeNode(name, probabilities[i]);
        minHeap.insert(node);
    }

    std::cout << "Cola de prioridad (Montículo de Mínimos):" << std::endl;
    while (!minHeap.isEmpty()) {
        TreeNode* node = minHeap.extractMin();
        std::cout << "Name: " << node->name << ", Probability: " << node->probability << std::endl;
        delete node;
    }

    std::cout << "\nÁrbol de Huffman:" << std::endl;
    // Construir el árbol de Huffman
    TreeNode* huffmanTreeRoot = Huffman::buildHuffmanTree(minHeap);

    std::cout << "\nCódigos de Huffman:" << std::endl;
    // Asignar códigos binarios a los símbolos y mostrarlos en std::cout
    Huffman::assignHuffmanCodes(huffmanTreeRoot, "", std::cout);

    return 0;
}