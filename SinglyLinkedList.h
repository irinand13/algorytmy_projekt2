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

    //zwraca wartość minimalną listy
    T findMin() const {
        if (head == nullptr) {
            cout << "The list is empty" << endl;
            return T();
        }
        T min = head->data;
        Node *current = head->next;
        while (current != nullptr) {
            if ((current->data) < min) {
                min = current->data;
            }
            current = current->next;
        }
        return min;
    }

    //zwraca wartość maksymalną listy
    T findMax() const {
        if (head == nullptr) {
            cout << "The list is empty" << endl;
            return T();
        }
        T max = head->data;
        Node *current = head->next;
        while (current != nullptr) {
            if (current->data> max) {
                max = current->data;
            }
            current = current->next;
        }
        return max;
    }

    //zwraca początek listy
    Node* getHead() {return head;}
    //ustawia początek listy
    void setHead(Node* newHead) {head = newHead;}

    //sprawdza czy listy jest posortowana
    bool isSorted() {
        Node* current = head;

        while (current != nullptr && current->next != nullptr) {
            if (current->data > current->next->data) {
                return false;
            }
            current = current->next;
        }

        return true;
    }

    //dodaje wartość na początek listy
    void push_front(T d) {
        Node *newNode = new Node(d);
        newNode->next = head;

        head = newNode;
        size++;
    }



};
#endif //SINGLYLINKEDLIST_H
