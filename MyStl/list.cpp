#include <iostream>

// ���������� ������
template <typename T>
class Node {
public:
    T data;          // ������ ���������� � ����
    Node* prev;      // ��������� �� ���������� ����
    Node* next;      // ��������� �� ��������� ����

    // ����������� ����
    Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
};

template <typename T>
class MyList {
private:
    Node<T>* head;  // ��������� �� ������ ���� ������
    Node<T>* tail;  // ��������� �� ��������� ���� ������
    size_t size;    // ������ ������

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
            // ���� ������ ����, ����� ���� ��������
            head = tail = newNode;
        }
        else {
            // ����� ��������� ����� ���� � ����� ������
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;
    }

    // ����� ��� ���������� �������� � ������ ������
    void push_front(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (head == nullptr) {
            head = tail = newNode;
        }
        else {
            // ����� ��������� ����� ���� � ������ ������
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        size++;
    }

    // ����� ��� �������� ���������� �������� ������
    void pop_back() {
        if (tail == nullptr) {
            // ���� ������ ����, ������ �� ������
            return;
        }
        Node<T>* temp = tail;
        tail = tail->prev;
        if (tail != nullptr) {
            tail->next = nullptr;
        }
        else {
            // ���� ������ ���� ������, �������� head
            head = nullptr;
        }
        delete temp;
        size--;
    }

    // ����� ��� �������� ������� �������� ������
    void pop_front() {
        if (head == nullptr) {
            // ���� ������ ����, ������ �� ������
            return;
        }
        Node<T>* temp = head;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        }
        else {
            // ���� ������ ���� ������, �������� tail
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