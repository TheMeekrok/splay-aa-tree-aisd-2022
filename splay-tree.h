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

    unsigned int _latest_insert_op = 0;
    unsigned int _latest_access_op = 0;
    unsigned int _latest_erase_op = 0;

    Node* root;

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

        while (node->right != nullptr) {
            node = node->right;
        }

        return node;
    }

    Node* _join(Node* t1, Node* t2) {
        auto *t = new SplayTree(t1);

        t->_splay(_max_elem(t->root));
        t->root->right = t2;
        t2->parent = t->root;

        if (t->root->parent != nullptr)
            t->root->parent = nullptr;

        return t->root;
    }

    Node* _access(T key) {

        Node* node = this->root;

        while (node != nullptr) {
            _latest_access_op += 1;

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

    // For erasing purposes
    Node* _e_access(T key) {
        Node* node = this->root;

        while (node != nullptr) {
            _latest_erase_op += 1;

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

    void _delete(Node* node) {
        if (node != nullptr) {
            _delete(node->left);
            _delete(node->right);
            delete node;
        }
    }

public:
    SplayTree() {
        this->root = nullptr;
    }

    explicit SplayTree(Node* root) {
        this->root = root;
    }

    ~SplayTree() {
        this->_delete(this->root);
    }

    bool access(T key) {
        this->_latest_access_op = 0;
        
        Node* result = this->_access(key);

        if (result != nullptr && result->key == key)
            return true;

        return false;
    }

    void insert(T key) {
        this->_latest_insert_op = 0;

        if (this->root == nullptr) {
            this->root = new Node(key);
            this->_latest_insert_op += 1;
            return;
        }

        Node* node = this->root;
        Node* parent = nullptr;

        while (node != nullptr) {
            this->_latest_insert_op += 1;

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
        this->_latest_erase_op = 0;
        Node* node = this->_e_access(key);

        if (node == nullptr)
            return false;

        Node* t1 = node->left;
        Node* t2 = node->right;

        Node* parent = node->parent;

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

    uint32_t get_insert_ops() {
        return this->_latest_insert_op;
    }

    uint32_t get_access_ops() {
        return this->_latest_access_op;
    }

    uint32_t get_erase_ops() {
        return this->_latest_erase_op;
    }
};

#endif //SPLAY_AA_TREE_SPLAY_TREE_H
