#ifndef SPLAY_AA_TREE_SPLAY_TREE_H
#define SPLAY_AA_TREE_SPLAY_TREE_H

template <typename T> class SplayTree {
private:
    typedef struct Node {
        T key;
        Node* left;
        Node* right;
        Node* parent;

        Node(T key, Node* parent = nullptr) {
            this->key = key;
            this->left = nullptr;
            this->right = nullptr;
            this->parent = parent;
        }
    } Node;

    void _left_rotate(Node* x) {
        if (x == this->root)
            return;

        Node* p = x->parent;
        Node* g = nullptr;

        if (p->parent != nullptr) {
            g = p->parent;
            if (g->left == p)
                g->left = x;
            else if (g->right == p)
                g->right = x;
        }
        else
            this->root = x;

        p->right = x->left;
        if (p->right != nullptr)
            p->right->parent = p;

        p->parent = x;
        x->left = p;
        x->parent = g;
    }

    void _right_rotate(Node* x) {
        if (x == this->root)
            return;

        Node* p = x->parent;
        Node* g = nullptr;

        if (p->parent != nullptr) {
            g = p->parent;
            if (g->left == p)
                g->left = x;
            else if (g->right == p)
                g->right = x;
        }
        else
            this->root = x;

        p->left = x->right;
        if (p->left != nullptr)
            p->left->parent = p;

        p->parent = x;
        x->right = p;
        x->parent = g;
    }

    void _splay(Node* node) {
        if (node == this->root)
            return;

        Node* p;
        Node* g;

        while (node->parent != nullptr) {
            p = node->parent;

            if (p->left == node) {
                if (p->parent != nullptr) {
                    g = p->parent;
                    //zig-zig right-right
                    if (g->left == p) {
                        this->_right_rotate(p);
                        this->_right_rotate(node);
                    }
                    //zig-zag right-left
                    else {
                        this->_right_rotate(node);
                        this->_left_rotate(node);
                    }
                }
                else {
                    //zig right
                    this->_right_rotate(node);
                }
            }
            else {
                if (p->parent != nullptr) {
                    g = p->parent;
                    //zig-zag left-right
                    if (g->left == p) {
                        this->_left_rotate(node);
                        this->_right_rotate(node);
                    }
                    //zig-zig left-left
                    else {
                        this->_left_rotate(p);
                        this->_left_rotate(node);
                    }
                }
                else {
                    //zig left
                    this->_left_rotate(node);
                }
            }
        }
    }

    Node* _max_elem (Node* node) {
        if (node == nullptr)
            return node;

        while (node->right != nullptr)
            node = node->right;

        return node;
    }

    Node* _join(Node* t1, Node* t2) {
        auto *t = new SplayTree(t1);

        t->_splay(_max_elem(t->root));
        t->root->right = t2;
        t2->parent = t->root;

        [[unlikely]] if (t->root->parent != nullptr)
            t->root->parent = nullptr;

        return t->root;
    }

    Node* _access(T key) {
        Node* node = this->root;

        while (node != nullptr) {
            if (key < node->key)
                node = node->left;
            else if (key > node->key)
                node = node->right;
            else {
                this->_splay(node);
                return node;
            }
        }

        return nullptr;
    }

    const int PRINT_DIST = 5;
    void _print_2D(Node* node, int space = 0) {
        if (node == nullptr)
            return;

        space += PRINT_DIST;

        _print_2D(node->right, space);

        std::cout << std::endl;

        for (int i = PRINT_DIST; i < space; i++)
            std::cout << " ";

        std::cout << node->key << "\n";

        _print_2D(node->left, space);
    }

    void _print(Node *node) {
        if (node == nullptr)
            return;

        _print(node->left);
        std::cout << "p: " << ((node->parent == nullptr) ? 0 : node->parent->key)
                  << "(" << node->key << ")" << std::endl;
        _print(node->right);
    }

public:
    Node* root;

    SplayTree() {
        this->root = nullptr;
    }

    explicit SplayTree(Node* root) {
        this->root = root;
    }

    bool access(T key) {
        Node* result = this->_access(key);
        if (result != nullptr && result->key == key)
            return true;
        return false;
    }

    void insert(T key) {
        if (this->root == nullptr) {
            this->root = new Node(key);
            return;
        }

        Node* node = this->root;
        Node* parent = nullptr;

        while (node != nullptr) {
            parent = node;

            if (key < node->key)
                node = node->left;
            else if (key > node->key)
                node = node->right;
            else
                return;
        }

        Node* new_node = new Node(key, parent);
        node = new_node;

        if (parent->key > node->key)
            parent->left = node;
        else if (parent->key < node->key)
            parent->right = node;

        this->_splay(node);
    }

    bool erase(T key) {
        Node* node = this->_access(key);
        if (node == nullptr)
            return false;

        Node* t1 = node->left;
        Node* t2 = node->right;

        if (t1 != nullptr && t2 != nullptr) {
            this->root = this->_join(t1, t2);
        }
        else if (t1 != nullptr) {
            t1->parent = nullptr;
            this->root = t1;
        }
        else if (t2 != nullptr) {
            t2->parent = nullptr;
            this->root = t2;
        }
        else {
            this->root = nullptr;
        }

        delete node;

        return true;
    }

    void print_2D() {
        this->_print_2D(this->root);
    }

    void print() {
        this->_print(this->root);
    }

};

#endif //SPLAY_AA_TREE_SPLAY_TREE_H
