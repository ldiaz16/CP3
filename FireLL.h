#ifndef FIRELL_H
#define FIRELL_H
#include <vector>
#include <iostream>
using namespace std;

template <typename T>
class FireLL {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    Node* current;
    bool hasDups;
    bool isOrdered;
    void copy(const FireLL& other);
    void destroy();

public:
    FireLL();
    FireLL(const FireLL& other);
    ~FireLL();
    FireLL& operator=(const FireLL& other);
    bool isEmpty() const;
    bool makeEmpty();
    bool may_contain_dups();
    bool ordered();
    bool add_left(const T&, bool no_dups);
    bool add_right(const T&, bool no_dups);
    int sort();
    bool contains(const T& Value) const;
    void add_in_order(const T& dataVal);
    bool remove_dups();
    FireLL& import(const FireLL& other, bool no_dups, bool maintain_order);
    FireLL& operator+=(const FireLL& other);
    bool restart();
    bool done() ;
    T go_to_next();
};

template <typename T>
FireLL<T>::FireLL() : head(nullptr), tail(nullptr), current(nullptr), hasDups(false), isOrdered(true) {
}

template <typename T>
FireLL<T>::FireLL(const FireLL& other) : head(nullptr), tail(nullptr), current(nullptr) {
    copy(other);
}

template <typename T>
FireLL<T>::~FireLL() {
    destroy();
}

template <typename T>
FireLL<T>& FireLL<T>::operator=(const FireLL& other) {
    if (this != &other) {
        destroy();
        copy(other);
    }
    return *this;
}

template <typename T>
void FireLL<T>::copy(const FireLL& other) {
    Node* temp = other.head;
    while (temp) {
        add_right(temp->data, false); 
        temp = temp->next;
    }
    hasDups = other.hasDups;
    isOrdered = other.isOrdered;
}

template <typename T>
void FireLL<T>::destroy() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    head = tail = current = nullptr;
}

template <typename T>
bool FireLL<T>::isEmpty() const {
    if (head == nullptr) {
        return true;
    } else {
        return false;
    }
    
}

template <typename T>
bool FireLL<T>::makeEmpty() {
    this->destroy();
}

template <typename T>
bool FireLL<T>::may_contain_dups() {
    if (!head || !head->next) {
        hasDups = false;
    }
    return hasDups;
}
        
template <typename T>
bool FireLL<T>::ordered() {
    if (!head || !head->next) {
        isOrdered = true;
    }
    return isOrdered;
} 

template <typename T>
bool FireLL<T>::add_left(const T& dataVal, bool no_dups) {
    if (no_dups) {
        Node* current = head;
        while (current) {
            if (current->data == dataVal) {
                return false;
            }
            current = current->next;
        }
    }
    Node* newNode = new Node(dataVal);
    if (!newNode) {return false;}
    if(isEmpty()) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    hasDups = true;
    isOrdered = false;
    return true;
}

template <typename T>
bool FireLL<T>::add_right(const T& dataVal, bool no_dups) {
    if (no_dups) {
        Node* current = head;
        while (current) {
            if (current->data == dataVal) {
                return false;
            }
            current = current->next;
        }
    }
    Node* newNode = new Node(dataVal);
    if (!newNode) {return false;}
    if (isEmpty()) {
        head = tail = newNode;
    } else {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
    isOrdered = false;
    hasDups = true;
    return true;
}

template <typename T>
int FireLL<T>::sort() {
    int swapCount = 0;
    if (!head || !head->next) {return 0;}
    bool swapped;
    do {
        swapped = false;
        Node* current = head;
        while (current && current->next) {
            if (current->data > current->next->data) {
                swap(current->data, current->next->data);
                swapCount++;
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
    isOrdered = true;
    return swapCount;
}

template <typename T>
bool FireLL<T>::remove_dups() {    
    if (!head || !head->next) {return false;}  
    bool removed = false;
    Node* current = head;

    while (current) {
        Node* runner = current->next;
        Node* prev = current;

        while (runner) {
            if (current->data == runner->data) {
                prev->next = runner->next;  
                if (runner->next) {runner->next->prev = prev;}
                delete runner;  
                runner = prev->next; 
                removed = true;
            } else {
                prev = runner;  
                runner = runner->next; 
            }
        }
        current = current->next; 
    }
    hasDups = false;
    return removed;
}
    

template <typename T>
FireLL<T>& FireLL<T>::import(const FireLL<T>& other, bool noDups, bool maintainOrder) {
    if (this == &other) {
        return *this;
    }
    isOrdered = true;
    Node* temp = other.head;
    while (temp) {
        if (maintainOrder) {
            if (!noDups || !contains(temp->data)) {
                add_in_order(temp->data);
            }
        } else {
            if (!noDups || !contains(temp->data)) {
                add_right(temp->data, false);
            }
        }
        temp = temp->next;
    }
    
    hasDups = hasDups || other.hasDups;
    return *this;
}


template <typename T>
void FireLL<T>::add_in_order(const T& dataVal) {
    Node* newNode = new Node(dataVal);
    if (!head || dataVal < head->data) {
        newNode->next = head;
        if (head) {
            head->prev = newNode;
        } else {
            tail = newNode;
        }
        head = newNode;
        return;
    }

    Node* current = head;
    while (current->next && current->next->data < dataVal) {
        current = current->next;
    }
    newNode->next = current->next;
    if (current->next) {
        current->next->prev = newNode;
    } else {
        tail = newNode;
    }
    current->next = newNode;
    newNode->prev = current;
}

template <typename T>
bool FireLL<T>::contains(const T& dataVal) const {
    Node* current = head;
    while (current) {
        if (current->data == dataVal) {
            return true;
        }
        current = current->next;
    }
    return false;
}

template <typename T>
FireLL<T>& FireLL<T>::operator+=(const FireLL& other) {
    return import(other, true, true);
}

template <typename T>
bool FireLL<T>::restart() {
    current = head;
    if (head != nullptr) {
        return true;
    } else {
        return false;
    }
}

template <typename T>
bool FireLL<T>::done() {
    return (current == nullptr);
}

template <typename T>
T FireLL<T>::go_to_next() {
    if (current == nullptr) {
        return T();
    }
    T data = current->data;
    current = current->next;
    return data;
}


#endif // FIRELL_H
