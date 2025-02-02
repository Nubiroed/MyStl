#include <iostream>
#include <utility>  // ��� std::pair

enum Color 
{ RED, 
  BLACK 
};

// ������ ���� ������-������� ������
template <typename Key, typename Value>
struct Node {
    Key key;                // ����
    Value value;            // ��������
    Color color;            // ���� ����
    Node* left;             // ����� �������
    Node* right;            // ������ �������
    Node* parent;           // ��������

    // ����������� ����
    Node(const Key& k, const Value& v, Color c = RED, Node* p = nullptr, Node* l = nullptr, Node* r = nullptr)
        : key(k), value(v), color(c), parent(p), left(l), right(r) {
    }
};

// ����� Map �� ������ ������-������� ������
template <typename Key, typename Value>
class MyMap {
private:
    Node<Key, Value>* root;  // ������ ������
    Node<Key, Value>* nil;   // ��������� ���� (������� ����)

    // ��������������� ������� ��� ������������
    void leftRotate(Node<Key, Value>* x) {
        Node<Key, Value>* y = x->right;
        x->right = y->left;
        if (y->left != nil) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nil) {
            root = y;
        }
        else if (x == x->parent->left) {
            x->parent->left = y;
        }
        else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node<Key, Value>* y) {
        Node<Key, Value>* x = y->left;
        y->left = x->right;
        if (x->right != nil) {
            x->right->parent = y;
        }
        x->parent = y->parent;
        if (y->parent == nil) {
            root = x;
        }
        else if (y == y->parent->right) {
            y->parent->right = x;
        }
        else {
            y->parent->left = x;
        }
        x->right = y;
        y->parent = x;
    }

    // ������������ ����� �������
    void fixInsert(Node<Key, Value>* z) {
        while (z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                Node<Key, Value>* y = z->parent->parent->right;
                if (y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        leftRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rightRotate(z->parent->parent);
                }
            }
            else {
                Node<Key, Value>* y = z->parent->parent->left;
                if (y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    leftRotate(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    // ������� ����
    void insert(Node<Key, Value>* z) {
        Node<Key, Value>* y = nil;
        Node<Key, Value>* x = root;
        while (x != nil) {
            y = x;
            if (z->key < x->key) {
                x = x->left;
            }
            else {
                x = x->right;
            }
        }
        z->parent = y;
        if (y == nil) {
            root = z;
        }
        else if (z->key < y->key) {
            y->left = z;
        }
        else {
            y->right = z;
        }
        z->left = nil;
        z->right = nil;
        z->color = RED;
        fixInsert(z);
    }

    // ����� ���� �� �����
    Node<Key, Value>* find(Node<Key, Value>* node, const Key& key) const {
        if (node == nil || key == node->key) {
            return node;
        }
        if (key < node->key) {
            return find(node->left, key);
        }
        else {
            return find(node->right, key);
        }
    }

    // ����� ������ (in-order traversal)
    void printTree(Node<Key, Value>* node) const {
        if (node != nil) {
            printTree(node->left);
            std::cout << "Key: " << node->key << ", Value: " << node->value << ", Color: " << (node->color == RED ? "RED" : "BLACK") << std::endl;
            printTree(node->right);
        }
    }

public:
    // �����������
    MyMap() {
        nil = new Node<Key, Value>(Key(), Value(), BLACK);
        root = nil;
    }

    // ����������
    ~MyMap() {
        clearTree(root);
        delete nil;
    }

    // ������� ��������
    void insert(const Key& key, const Value& value) {
        Node<Key, Value>* z = new Node<Key, Value>(key, value);
        insert(z);
    }

    // ����� ��������
    Value* find(const Key& key) {
        Node<Key, Value>* node = find(root, key);
        if (node != nil) {
            return &node->value;
        }
        return nullptr;
    }

    // ����� ���� ���������
    void print() const {
        printTree(root);
    }

    // ������� ������
    void clearTree(Node<Key, Value>* node) {
        if (node != nil) {
            clearTree(node->left);
            clearTree(node->right);
            delete node;
        }
    }
};

