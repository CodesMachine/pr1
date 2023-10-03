#include <iostream>

// Определение узла связанного списка
template <typename T>
struct Node {
    T data;
    Node* next;
    Node(T val) : data(val), next(nullptr) {}
};

// Абстрактный класс для абстрактного типа данных (АТД)
template <typename T>
class LinkedListADT {
public:
    virtual void Push(T item) = 0;
    virtual T Pop() = 0;
    virtual T Peek() = 0;
    virtual bool IsEmpty() = 0;
};

// Реализация АТД "Стек"
template <typename T>
class Stack : public LinkedListADT<T> {
private:
    Node<T>* top;

public:
    Stack() : top(nullptr) {}

    void Push(T item) override {
        Node<T>* newNode = new Node<T>(item);
        newNode->next = top;
        top = newNode;
    }

    T Pop() override {
        if (IsEmpty())
            throw std::runtime_error("Стек пуст");

        T value = top->data;
        Node<T>* temp = top;
        top = top->next;
        delete temp;
        return value;
    }

    T Peek() override {
        if (IsEmpty())
            throw std::runtime_error("Стек пуст");

        return top->data;
    }

    bool IsEmpty() override {
        return top == nullptr;
    }
};

// Реализация АТД "Дек"
template <typename T>
class Deque : public LinkedListADT<T> {
private:
    Node<T>* front;
    Node<T>* rear;

public:
    Deque() : front(nullptr), rear(nullptr) {}

    void Push(T item) override {
        Node<T>* newNode = new Node<T>(item);
        if (IsEmpty()) {
            front = rear = newNode;
        }
        else {
            newNode->next = front;
            front = newNode;
        }
    }

    void PushBack(T item) {
        Node<T>* newNode = new Node<T>(item);
        if (IsEmpty()) {
            front = rear = newNode;
        }
        else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    T Pop() override {
        if (IsEmpty())
            throw std::runtime_error("Дек пуст");

        T value = front->data;
        Node<T>* temp = front;
        if (front == rear) {
            front = rear = nullptr;
        }
        else {
            front = front->next;
        }
        delete temp;
        return value;
    }

    T PopBack() {
        if (IsEmpty())
            throw std::runtime_error("Дек пуст");

        T value = rear->data;
        if (front == rear) {
            delete rear;
            front = rear = nullptr;
        }
        else {
            Node<T>* temp = front;
            while (temp->next != rear) {
                temp = temp->next;
            }
            delete rear;
            rear = temp;
            rear->next = nullptr;
        }
        return value;
    }

    T Peek() override {
        if (IsEmpty())
            throw std::runtime_error("Дек пуст");

        return front->data;
    }

    bool IsEmpty() override {
        return front == nullptr;
    }
};

// Реализация АТД "Очередь" с использованием "Дека"
template <typename T>
class Queue : public LinkedListADT<T> {
private:
    Deque<T> deque;

public:
    void Push(T item) override {
        deque.PushBack(item);
    }

    T Pop() override {
        return deque.Pop();
    }

    T Peek() override {
        return deque.Peek();
    }

    bool IsEmpty() override {
        return deque.IsEmpty();
    }
};

// Метод сортировки простой вставкой для линейного списка
template <typename T>
void InsertionSort(Node<T>*& head) {
    if (head == nullptr || head->next == nullptr)
        return;

    Node<T>* sorted = nullptr;
    Node<T>* current = head;

    while (current != nullptr) {
        Node<T>* next = current->next;
        if (sorted == nullptr || sorted->data >= current->data) {
            current->next = sorted;
            sorted = current;
        }
        else {
            Node<T>* search = sorted;
            while (search->next != nullptr && search->next->data < current->data) {
                search = search->next;
            }
            current->next = search->next;
            search->next = current;
        }
        current = next;
    }

    head = sorted;
}

int main() {
    setlocale(LC_ALL, "Russian");
    // Пример использования

    // Создаем и заполняем линейный связанный список
    Node<int>* head = new Node<int>(5);
    head->next = new Node<int>(3);
    head->next->next = new Node<int>(1);
    head->next->next->next = new Node<int>(4);
    head->next->next->next->next = new Node<int>(2);

    std::cout << "Исходный список: ";
    Node<int>* current = head;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;

    // sort
    InsertionSort(head);

    std::cout << "Отсортированный список: ";
    current = head;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;

    // clear memory
    while (head != nullptr) {
        Node<int>* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}

