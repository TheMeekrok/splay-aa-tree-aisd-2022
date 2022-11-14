#ifndef SPLAY_AA_TREE_AA_TREE_H
#define SPLAY_AA_TREE_AA_TREE_H

#include <iostream>

template <typename T> class AATree {
private:
    typedef struct Node {
        T key;
        struct Node* left;
        struct Node* right;
        unsigned int level;

        Node (T key) {
            this->key = key;
            this->level = 1;
            this->left = nullptr;
            this->right = nullptr;
        }
    } Node;

    Node* root;
    unsigned int _latest_insert_op = 0;
    unsigned int _latest_access_op = 0;
    unsigned int _latest_erase_op = 0;
    unsigned int _total_access_op = 0;

    // O(1)
    Node* _right_rotate(Node* node) {
        Node* left = node->left;
        node->left = left->right;
        left->right = node;

        return left;
    }

    // O(1)
    Node* _left_rotate(Node* node) {
        Node* right = node->right;
        node->right = right->left;
        right->left = node;

        return right;
    }

    // O(1)
    Node* _skew(Node* node) {
        if (node == nullptr)
            return node;

        if (node->left != nullptr
            && node->left->level == node->level) {
            node = this->_right_rotate(node);
        }

        return node;
    }

    // O(1)
    Node* _split(Node* node) {
        if (node == nullptr)
            return node;

        if (node->right && node->right->right
            && node->level == node->right->right->level) {
            node = this->_left_rotate(node);
            node->level++;
        }

        return node;
    }

    // Time depends on number of elements
    Node* _access(T key) {
        Node* node = this->root;

        while (node != nullptr) {
            // Adding 1 comparison
            this->_latest_access_op++;
            this->_total_access_op++;

            if (key < node->key)
                node = node->left;
            else if (key > node->key)
                node = node->right;
            else
                return node;
        }

        return nullptr;
    }

    // Time depends on number of elements
    Node* _insert(T key, Node* node) {
        if (node == nullptr)
            return new Node(key);

        // Adding 1 comparison
         this->_latest_insert_op++;

        if (key < node->key)
            node->left = _insert(key, node->left);
        else if (key > node->key)
            node->right = _insert(key, node->right);

        node = this->_skew(node);
        node = this->_split(node);

        return node;
    }

    // Time depends on number of elements
    Node* _min_node(Node* node) {
        if (node != nullptr) {
            while (node->left != nullptr) {
                node = node->left;

                //Adding 1 jump by pointer
                this->_latest_erase_op++;
            }
        }

        return node;
    }

    // Time depends on number of elements
    Node* _max_node(Node* node) {
        if (node != nullptr) {
            while (node->right != nullptr) {
                node = node->right;

                //Adding 1 jump by pointer
                this->_latest_erase_op++;
            }
        }

        return node;
    }

    unsigned int _min(unsigned int a, unsigned int b) {
        return (a > b) ? a : b;
    }

    // Time depends on number of elements
    Node* _erase(T key, Node* node) {
        if (node == nullptr)
            return node;

        // Adding 1 comparison
        this->_latest_erase_op++;

        if (key < node->key)
            node->left = _erase(key, node->left);
        else if (key > node->key)
            node->right = _erase(key, node->right);
        else {
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            }
            else if (node->left == nullptr) {
                Node* _successor = _min_node(node->right);
                node->key = _successor->key;
                node->right = _erase(_successor->key,
                                     node->right);
            }
            else {
                Node* _predecessor = _max_node(node->left);
                node->key = _predecessor->key;
                node->left = _erase(_predecessor->key,
                                    node->left);
            }
        }

        Node* left = node->left;
        Node* right = node->right;
        if (left != nullptr || right != nullptr) {
            unsigned int l_level = (node->left) ? node->left->level : 0;
            unsigned int r_level = (node->right) ? node->right->level : 0;

            node->level = _min(l_level, r_level) + 1;
            if (r_level > node->level)
                node->right->level = r_level;
        }

        node = _skew(node);
        node->right = _skew(node->right);

        if (node->right != nullptr)
            node->right->right = _skew(node->right->right);

        node = _split(node);
        node->right = _split(node->right);

        return node;
    }

    void _delete(Node* node) {
        if (node != nullptr) {
            _delete(node->left);
            _delete(node->right);
            delete node;
        }
    }

public:
    AATree() {
        this->root = nullptr;
    }

    ~AATree() {
        _delete(this->root);
    }

    bool access(T key) {
        this->_latest_access_op = 0;

        Node* node = this->_access(key);
        return node ? true : false;
    }

    void insert(T key) {
        this->_latest_insert_op = 0;

        this->root = this->_insert(key, this->root);
    }

    void erase(T key) {
        this->_latest_erase_op = 0;

        this->root = this->_erase(key, this->root);
    }

    uint32_t get_insert_ops() {
        return this->_latest_insert_op;
    }

    uint32_t get_access_ops() {
        return this->_latest_access_op;
    }

    uint32_t get_access_ops_t() {
        return this->_total_access_op;
    }

    uint32_t get_erase_ops() {
        return this->_latest_erase_op;
    }
};

#endif //SPLAY_AA_TREE_AA_TREE_H