#ifndef SPLAY_AA_TREE_AA_TREE_H
#define SPLAY_AA_TREE_AA_TREE_H

template <typename T> class AATree {
public:
    typedef struct Node {
        T key;
        struct Node* left;
        struct Node* right;
        ushort level;

        Node (T key) {
            this->key = key;
            this->level = 1;
            this->left = nullptr;
            this->right = nullptr;
        }
    } Node;

    const int PRINT_DIST = 5;
    void _print_2D(Node* node, int space = 0) {
        if (node == nullptr)
            return;

        space += PRINT_DIST;

        _print_2D(node->right, space);

        std::cout << std::endl;

        for (int i = PRINT_DIST; i < space; i++)
            std::cout << " ";

        std::cout << node->key << "(l: " << node->level << ")\n";

        _print_2D(node->left, space);
    }

    Node* root;

    Node* _right_rotate(Node* node) {
        Node* left = node->left;
        node->left = left->right;
        left->right = node;

        return left;
    }

    Node* _left_rotate(Node* node) {
        Node* right = node->right;
        node->right = right->left;
        right->left = node;

        return right;
    }

    Node* _skew(Node* node) {
        if (node == nullptr)
            return node;

        if (node->left != nullptr
            && node->left->level == node->level) {
            node = this->_right_rotate(node);
        }

        return node;
    }

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

    Node* _access(T key, Node* node) {
        if (node == nullptr)
            return nullptr;

        if (node->key < key)
            node->left = _access(key, node->left);
        else if (node->key > key)
            node->right = _access(key, node->right);
        else
            return node;

        return node;
    }

    Node* _insert(T key, Node* node) {
        if (node == nullptr)
            return new Node(key);

        if (key < node->key)
            node->left = _insert(key, node->left);
        else if (key > node->key)
            node->right = _insert(key, node->right);
        else
            return node;

        node = this->_skew(node);
        node = this->_split(node);

        return node;
    }

    Node* _min_node(Node* node) {
        if (node != nullptr)
            while (node->left != nullptr)
                node = node->left;

        return node;
    }

    Node* _max_node(Node* node) {
        if (node != nullptr)
            while (node->right != nullptr)
                node = node->right;

        return node;
    }

    ushort _min(ushort a, ushort b) {
        return (a > b) ? a : b;
    }

    Node* _erase(T key, Node* node) {
        if (node == nullptr)
            return node;

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
            ushort l_level = (node->left) ? node->left->level : 0;
            ushort r_level = (node->right) ? node->right->level : 0;

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

    AATree() {
        this->root = nullptr;
    }

    bool access(T key) {
        Node* node = this->_access(key, this->root);
        if (node != nullptr && node->key == key)
            return true;
        return false;
    }

    void insert(T key) {
        this->root = this->_insert(key, this->root);
    }

    void erase(T key) {
        this->root = this->_erase(key, this->root);
    }

    void print_2D() {
        this->_print_2D(this->root);
    }
};

#endif //SPLAY_AA_TREE_AA_TREE_H