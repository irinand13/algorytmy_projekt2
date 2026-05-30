//
// Created by iraan on 02.05.2026.
//

#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H
using namespace std;

// Dynamiczna lista jednokierunkowa,  która jest inicjalizowana jako szablon
template<class T>
class SinglyLinkedList {
public:
    //węzeł
    struct Node  {
        T data;
        Node *next;

        //konstruktor węzła do przechowywania w liście
        explicit Node(T d) {
            data = d;
            next = nullptr;
        }
    };

    Node *head;
    int size;

public:
    //konstruktor listy
    SinglyLinkedList () {
        head = nullptr;
        size = 0;
    }

    //konstruktor kopiujący
    SinglyLinkedList (const SinglyLinkedList& other) {
        head = nullptr;
        size = 0;

        Node* current = other.head;

        while (current!=nullptr) {
            push(current->data);
            current = current->next;
        }
    }

    // Operator przypisania
    SinglyLinkedList& operator=(const SinglyLinkedList& other) {
        if (this == &other) return *this;

        Node* current = head;
        while (current!=nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        size = 0;

        Node* temp = other.head;
        while (temp!=nullptr) {
            push(temp->data);
            temp = temp->next;
        }
        return *this;
    }


    //destruktor listy
    ~SinglyLinkedList () {
        Node *current = head;
        while (current != nullptr) {
            Node *next = current->next;
            delete current;
            current = next;
        }
    }


    // Operator indeksowania
    T& operator[](int index) {
        Node* current = head;
        for (int i = 0; i < index && current != nullptr; ++i) {
            current = current->next;
        }
        return current->data;
    }


    //metoda która dodaje nową wartość do listy
    void push(T d) {
        Node *newNode = new Node(d);
        if (head == nullptr) {
            head = newNode;
        } else {
            Node *current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
        size++;
    }

    //odczytuje wartości listy
    void read() {
        Node *current = head;
        while (current != nullptr) {
            cout << current->data << " ";
            cout << endl;
            current = current->next;
        }
    }

    //zwraca rozmiar
    int getSize() {return size;}
    //zwraca początek listy
    Node* getHead() {return head;}


    //dodaje wartość na początek listy
    void pushFront(T d) {
        Node *newNode = new Node(d);
        newNode->next = head;

        head = newNode;
        size++;
    }

    void popFront() {
        if (head == nullptr) return;
        Node* temp = head;
        head = head->next;
        delete temp;
        size--;
    }

    void clear () {
        Node *current = head;
        while (current != nullptr) {
            Node *next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        size = 0;
    }


};
#endif //SINGLYLINKEDLIST_H
