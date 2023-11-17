#include "huffman.h"

// Implementación del constructor de TreeNode
TreeNode::TreeNode(std::string n, double prob) : parent(nullptr), left(nullptr), right(nullptr), name(n), probability(prob) {}

// Implementación del constructor de MinHeap
MinHeap::MinHeap() : size(0), capacity(10) {
    heap = new TreeNode*[capacity];
}

// Implementación de la función resize de MinHeap
void MinHeap::resize() {
    capacity *= 2;
    TreeNode** newHeap = new TreeNode*[capacity];
    for (int i = 0; i < size; i++) {
        newHeap[i] = heap[i];
    }
    delete[] heap;
    heap = newHeap;
}

// Implementación de la función heapifyUp de MinHeap
void MinHeap::heapifyUp(int index) {
    while (index > 0) {
        int parentIndex = (index - 1) / 2;
        if (heap[index]->probability < heap[parentIndex]->probability) {
            std::swap(heap[index], heap[parentIndex]);
            index = parentIndex;
        } else {
            break;
        }
    }
}

// Implementación de la función heapifyDown de MinHeap
void MinHeap::heapifyDown(int index) {
    while (true) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int smallest = index;

        if (leftChild < size && heap[leftChild]->probability < heap[smallest]->probability) {
            smallest = leftChild;
        }

        if (rightChild < size && heap[rightChild]->probability < heap[smallest]->probability) {
            smallest = rightChild;
        }

        if (smallest != index) {
            std::swap(heap[index], heap[smallest]);
            index = smallest;
        } else {
            break;
        }
    }
}

// Implementación de la función insert de MinHeap
void MinHeap::insert(TreeNode* node) {
    if (size == capacity) {
        resize();
    }
    heap[size] = node;
    heapifyUp(size);
    size++;
}

// Implementación de la función extractMin de MinHeap
TreeNode* MinHeap::extractMin() {
    if (size == 0) {
        return nullptr;
    }

    if (size == 1) {
        TreeNode* minNode = heap[0];
        size = 0;
        return minNode;
    }

    TreeNode* minNode = heap[0];
    heap[0] = heap[size - 1];
    size--;
    heapifyDown(0);
    return minNode;
}

// Implementación de la función isEmpty de MinHeap
bool MinHeap::isEmpty() const {
    return size == 0;
}

// Implementación del destructor de MinHeap
MinHeap::~MinHeap() {
    delete[] heap;
}

// Implementación de la función buildHuffmanTree de Huffman
TreeNode* Huffman::buildHuffmanTree(MinHeap& minHeap) {
    while (minHeap.size > 1) {
        // Extraer los dos nodos con probabilidad mínima
        TreeNode* node1 = minHeap.extractMin();
        TreeNode* node2 = minHeap.extractMin();

        // Crear un nuevo nodo con probabilidad igual a la suma de los dos nodos extraídos
        TreeNode* internalNode = new TreeNode("", node1->probability + node2->probability);
        internalNode->left = node1;
        internalNode->right = node2;

        // Actualizar la cola de prioridad (montículo)
        minHeap.insert(internalNode);
    }

    // El último nodo en el montículo es la raíz del árbol de Huffman
    return minHeap.extractMin();
}

// Implementación de la función assignHuffmanCodes de Huffman
void Huffman::assignHuffmanCodes(TreeNode* root, const std::string& code, std::ostream& output) {
    if (root) {
        if (root->left == nullptr && root->right == nullptr) {
            // Este nodo es una hoja, imprimir el código al símbolo
            output << "Symbol: " << root->name << ", Huffman Code: " << code << std::endl;
        }
        // Recursivamente asignar códigos a la izquierda y derecha
        assignHuffmanCodes(root->left, code + "0", output);
        assignHuffmanCodes(root->right, code + "1", output);
    }
}

