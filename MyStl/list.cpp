#include <iostream>

// Двусвязный список
template <typename T>
class Node {
public:
    T data;          // Данные хранящиеся в узле
    Node* prev;      // Указатель на предыдущий узел
    Node* next;      // Указатель на следующий узел

    // Конструктор узла
    Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
};

template <typename T>
class MyList {
private:
    Node<T>* head;  // Указатель на первый узел списка
    Node<T>* tail;  // Указатель на последний узел списка
    size_t size;    // Размер списка

public:
    MyList() : head(nullptr), tail(nullptr), size(0) {}

    
    ~MyList() {
        while (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void push_back(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (tail == nullptr) {
            // Если список пуст, новый узел одинаков
            head = tail = newNode;
        }
        else {
            // Иначе добавляем новый узел в конец списка
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;
    }

    // Метод для добавления элемента в начало списка
    void push_front(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (head == nullptr) {
            head = tail = newNode;
        }
        else {
            // Иначе добавляем новый узел в начало списка
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        size++;
    }

    // Метод для удаления последнего элемента списка
    void pop_back() {
        if (tail == nullptr) {
            // Если список пуст, ничего не делаем
            return;
        }
        Node<T>* temp = tail;
        tail = tail->prev;
        if (tail != nullptr) {
            tail->next = nullptr;
        }
        else {
            // Если список стал пустым, обнуляем head
            head = nullptr;
        }
        delete temp;
        size--;
    }

    // Метод для удаления первого элемента списка
    void pop_front() {
        if (head == nullptr) {
            // Если список пуст, ничего не делаем
            return;
        }
        Node<T>* temp = head;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        }
        else {
            // Если список стал пустым, обнуляем tail
            tail = nullptr;
        }
        delete temp;
        size--;
    }

    
    size_t get_size() const {
        return size;
    }

   
    bool is_empty() const {
        return size == 0;
    }

   
    void print() const {
        Node<T>* current = head;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};