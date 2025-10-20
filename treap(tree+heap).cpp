#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>

// Node structure for the Treap
template <typename T>
struct TreapNode {
    T key;
    int priority; // Used for heap property (randomly generated)
    TreapNode *left, *right;

    TreapNode(T k) : key(k), 
                      // Use a strong, non-deterministic random priority
                      priority(std::chrono::system_clock::now().time_since_epoch().count() % 10000), 
                      left(nullptr), 
                      right(nullptr) {}
};

template <typename T>
class Treap {
private:
    TreapNode<T>* root;

    // Helper functions for rotations to maintain heap property
    TreapNode<T>* rotate_right(TreapNode<T>* y) {
        TreapNode<T>* x = y->left;
        y->left = x->right;
        x->right = y;
        return x; // New root of the subtree
    }

    TreapNode<T>* rotate_left(TreapNode<T>* x) {
        TreapNode<T>* y = x->right;
        x->right = y->left;
        y->left = x;
        return y; // New root of the subtree
    }

    // Core recursive insert function (private)
    TreapNode<T>* insert_recursive(TreapNode<T>* node, T key) {
        if (!node) {
            return new TreapNode<T>(key);
        }

        if (key < node->key) {
            node->left = insert_recursive(node->left, key);
            // After insertion, check and fix heap property (max-heap for priority)
            if (node->left->priority > node->priority) {
                node = rotate_right(node);
            }
        } else if (key > node->key) {
            node->right = insert_recursive(node->right, key);
            // Check and fix heap property
            if (node->right->priority > node->priority) {
                node = rotate_left(node);
            }
        }
        return node;
    }

public:
    Treap() : root(nullptr) {}

    // Public API for insertion
    void insert(T key) {
        root = insert_recursive(root, key);
    }
    
    // ... (Add erase, find, and inorder traversal methods) ...

    ~Treap() {
        // Implement clean recursive deletion of all nodes (post-order traversal)
    }
};

// Example Usage (for testing/demonstration)
/*
int main() {
    Treap<int> t;
    t.insert(50);
    t.insert(30);
    t.insert(70);
    t.insert(20);
    t.insert(60);
    // t.inorder_traversal();
    return 0;
}
*/
