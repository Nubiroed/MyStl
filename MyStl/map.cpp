#include <iostream>
#include <utility>  // для std::pair

enum Color 
{ RED, 
  BLACK 
};

// Шаблон узла красно-черного дерева
template <typename Key, typename Value>
struct Node {
    Key key;                // Ключ
    Value value;            // Значение
    Color color;            // Цвет узла
    Node* left;             // Левый потомок
    Node* right;            // Правый потомок
    Node* parent;           // Родитель

    // Конструктор узла
    Node(const Key& k, const Value& v, Color c = RED, Node* p = nullptr, Node* l = nullptr, Node* r = nullptr)
        : key(k), value(v), color(c), parent(p), left(l), right(r) {
    }
};

// Класс Map на основе красно-черного дерева
template <typename Key, typename Value>
class MyMap {
private:
    Node<Key, Value>* root;  // Корень дерева
    Node<Key, Value>* nil;   // Фиктивный лист (нулевой узел)

    // Вспомогательные функции для балансировки
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

    // Балансировка после вставки
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

    // Вставка узла
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

    // Поиск узла по ключу
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

    // Вывод дерева (in-order traversal)
    void printTree(Node<Key, Value>* node) const {
        if (node != nil) {
            printTree(node->left);
            std::cout << "Key: " << node->key << ", Value: " << node->value << ", Color: " << (node->color == RED ? "RED" : "BLACK") << std::endl;
            printTree(node->right);
        }
    }

public:
    // Конструктор
    MyMap() {
        nil = new Node<Key, Value>(Key(), Value(), BLACK);
        root = nil;
    }

    // Деструктор
    ~MyMap() {
        clearTree(root);
        delete nil;
    }

    // Вставка элемента
    void insert(const Key& key, const Value& value) {
        Node<Key, Value>* z = new Node<Key, Value>(key, value);
        insert(z);
    }

    // Поиск элемента
    Value* find(const Key& key) {
        Node<Key, Value>* node = find(root, key);
        if (node != nil) {
            return &node->value;
        }
        return nullptr;
    }

    // Вывод всех элементов
    void print() const {
        printTree(root);
    }

    // Очистка дерева
    void clearTree(Node<Key, Value>* node) {
        if (node != nil) {
            clearTree(node->left);
            clearTree(node->right);
            delete node;
        }
    }
};

